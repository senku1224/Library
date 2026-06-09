#include "borrow.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*=========================
  初始化链表
=========================*/
void InitBorrowList(BorrowNode **head)
{
    *head = NULL;
}

/*=========================
  借书操作
=========================*/
int BorrowBook(BorrowNode **head, int userId, int bookId, char borrowDate[], char dueDate[])
{
    // 查找图书
    int index = -1;
    for(int i=0;i<bookCount;i++)
    {
        if(books[i].id == bookId)
        {
            index = i;
            break;
        }
    }
    if(index == -1)
    {
        printf("图书不存在\n");
        return -1;
    }

    if(books[index].remain <= 0)
    {
        printf("库存不足\n");
        return -1;
    }

    BorrowNode *node = (BorrowNode*)malloc(sizeof(BorrowNode));
    node->userId = userId;
    node->bookId = bookId;
    strcpy(node->borrowDate, borrowDate);
    strcpy(node->dueDate, dueDate);

    node->prev = NULL;
    node->next = *head;
    if(*head) (*head)->prev = node;
    *head = node;

    books[index].remain--;
    books[index].borrowCount++;

    // 入队提醒
    EnQueue(&remindQueue, node);

    char logMsg[100];
    sprintf(logMsg, "用户 %d 借阅图书 %d", userId, bookId);
    pushLog(&logStack, logMsg);

    printf("借书成功！\n");
    return 0;
}

/*=========================
  还书操作
=========================*/
int ReturnBook(BorrowNode **head, int userId, int bookId)
{
    BorrowNode *p = *head;
    while(p)
    {
        if(p->userId == userId && p->bookId == bookId)
        {
            if(p->prev) p->prev->next = p->next;
            else *head = p->next;
            if(p->next) p->next->prev = p->prev;

            // 恢复图书剩余数量
            for(int i=0;i<bookCount;i++)
            {
                if(books[i].id == bookId)
                {
                    books[i].remain++;
                    break;
                }
            }

            // 从队列中删除
            for(int i=remindQueue.front; i != remindQueue.rear; i = (i+1)%MAX_QUEUE)
            {
                if(remindQueue.data[i] == p)
                {
                    // 简单标记为空
                    remindQueue.data[i] = NULL;
                    break;
                }
            }

            char logMsg[100];
            sprintf(logMsg,"用户 %d 归还图书 %d", userId, bookId);
            pushLog(&logStack, logMsg);

            free(p);
            printf("还书成功！\n");
            return 0;
        }
        p = p->next;
    }
    printf("未找到借阅记录\n");
    return -1;
}

/*=========================
  查询个人借阅
=========================*/
void QueryUserBorrow(BorrowNode *head, int userId)
{
    BorrowNode *p = head;
    int found = 0;
    while(p)
    {
        if(p->userId == userId)
        {
            printf("图书ID:%d 借阅:%s 应还:%s\n",
                   p->bookId, p->borrowDate, p->dueDate);
            found = 1;
        }
        p = p->next;
    }
    if(!found) printf("暂无借阅记录\n");
}

/*=========================
  查询所有借阅
=========================*/
void QueryAllBorrow(BorrowNode *head)
{
    BorrowNode *p = head;
    if(!p) { printf("暂无借阅记录\n"); return; }

    while(p)
    {
        printf("用户ID:%d 图书ID:%d 借阅:%s 应还:%s\n",
               p->userId, p->bookId, p->borrowDate, p->dueDate);
        p = p->next;
    }
}

/*=========================
  队列操作
=========================*/
void InitReminderQueue(ReminderQueue *Q)
{
    Q->front = Q->rear = 0;
}

int EnQueue(ReminderQueue *Q, BorrowNode *node)
{
    int next = (Q->rear + 1) % MAX_QUEUE;
    if(next == Q->front) return 0; // 队满
    Q->data[Q->rear] = node;
    Q->rear = next;
    return 1;
}

BorrowNode* DeQueue(ReminderQueue *Q)
{
    if(Q->front == Q->rear) return NULL;
    BorrowNode *node = Q->data[Q->front];
    Q->front = (Q->front +1)%MAX_QUEUE;
    return node;
}

void LoadRemindData(BorrowNode *head, ReminderQueue *Q)
{
    InitReminderQueue(Q);
    BorrowNode *p = head;
    while(p)
    {
        EnQueue(Q,p);
        p=p->next;
    }
}

void ShowRemindInfo(ReminderQueue *Q)
{
    if(Q->front == Q->rear) { printf("暂无到期提醒\n"); return; }
    int i = Q->front;
    while(i != Q->rear)
    {
        BorrowNode *p = Q->data[i];
        if(p)
            printf("用户ID:%d 图书ID:%d 应还:%s\n",
                   p->userId, p->bookId, p->dueDate);
        i = (i+1) % MAX_QUEUE;
    }
}
