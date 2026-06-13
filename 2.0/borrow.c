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
        getchar();
        return -1;
    }

    // 学生借书数量限制
    if (currentUser.role == 0) { // 学生
        int borrowed = countUserBorrowed(*head, userId);
        if (borrowed >= 10) {
            printf("学生最多只能借阅10本书，当前已借%d本！\n", borrowed);
            return -1;
        }
    }

    // 差异化应还日期（学生30天/老师90天）
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    int days = (currentUser.role == 0) ? 30 : 90; // 学生30天，老师90天
    now->tm_mday += days;
    mktime(now); // 自动处理月份/年份进位
    strftime(dueDate, 20, "%Y-%m-%d", now);

    BorrowNode *node = (BorrowNode*)malloc(sizeof(BorrowNode));
    node->userId = userId;
    node->bookId = bookId;
    strcpy(node->borrowDate, borrowDate);
    strcpy(node->dueDate, dueDate);

    // 新增：初始化状态和归还日期
    node->status = 0;
    strcpy(node->returnDate, "");


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
    getchar();
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
        // 只匹配在借记录
        if(p->userId == userId && p->bookId == bookId && p->status == 0)
        {
            // 恢复图书剩余数量
            for(int i=0;i<bookCount;i++)
            {
                if(books[i].id == bookId)
                {
                    books[i].remain++;
                    break;
                }
            }
            // 从提醒队列中标记移除
            for(int i=remindQueue.front; i != remindQueue.rear; i = (i+1)%MAX_QUEUE)
            {
                if(remindQueue.data[i] == p)
                {
                    remindQueue.data[i] = NULL;
                    break;
                }
            }
            // 标记为已归还，记录归还日期
            char curDate[20];
            getCurrentDate(curDate);
            strcpy(p->returnDate, curDate);
            p->status = 1;

            char logMsg[100];
            sprintf(logMsg,"用户 %d 归还图书 %d", userId, bookId);
            pushLog(&logStack, logMsg);
            printf("还书成功！\n");
            getchar();
            return 0;
        }
        p = p->next;
    }
    printf("未找到对应在借记录\n");
    return -1;
}

/*=========================
  查询个人借阅
=========================*/
/* 查询个人在借图书 - 原我的借阅，仅显示在借 */
void QueryUserBorrow(BorrowNode *head, int userId) {
    BorrowNode *p = head;
    int found = 0;

    while (p) {
        if (p->userId == userId && p->status == 0) {
            found = 1;
            break;
        }
        p = p->next;
    }

    if (!found) {
        printf("暂无在借图书\n");
        return;
    }

    printf("%-8s%-16s%-16s%-8s\n",
           "图书ID", "借阅日期", "应还日期", "状态");

    p = head;
    while (p) {
        if (p->userId == userId && p->status == 0) {
            printf("%-8d%-16s%-16s%-8s\n",
                   p->bookId, p->borrowDate, p->dueDate, "在借");
        }
        p = p->next;
    }
}

/* 新增：查询个人全部借阅历史 */
void QueryUserBorrowHistory(BorrowNode *head, int userId) {
    BorrowNode *p = head;
    int found = 0;

    // 第一步：先遍历判断是否有匹配记录
    while (p) {
        if (p->userId == userId) {
            found = 1;
            break;
        }
        p = p->next;
    }

    // 无记录直接返回，不打印表头
    if (!found) {
        printf("暂无借阅记录\n");
        return;
    }

    // 有记录才打印表头，固定列宽左对齐
    printf("%-8s%-16s%-16s%-16s%-8s\n",
           "图书ID", "借阅日期", "应还日期", "归还日期", "状态");

    // 输出数据
    p = head;
    while (p) {
        if (p->userId == userId) {
            char returnDateStr[20];
            strcpy(returnDateStr, p->status == 0 ? "-" : p->returnDate);
            char statusStr[10];
            strcpy(statusStr, p->status == 0 ? "在借" : "已归还");

            printf("%-8d%-16s%-16s%-16s%-8s\n",
                   p->bookId, p->borrowDate, p->dueDate,
                   returnDateStr, statusStr);
        }
        p = p->next;
    }
}

/*=========================
  查询所有借阅
=========================*/
void QueryAllBorrow(BorrowNode *head) {
    if (!head) {
        printf("暂无借阅记录\n");
        return;
    }
    // 固定列宽左对齐
    printf("%-8s%-8s%-16s%-16s%-8s\n",
           "用户ID", "图书ID", "借阅日期", "应还日期", "状态");
    BorrowNode *p = head;
    while (p) {
        char statusStr[10];
        strcpy(statusStr, p->status == 0 ? "在借" : "已归还");
        printf("%-8d%-8d%-16s%-16s%-8s\n",
               p->userId, p->bookId,
               p->borrowDate, p->dueDate,
               statusStr);
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
        if(p->status == 0) EnQueue(Q,p);
        p = p->next;
    }
}

void ShowRemindInfo(ReminderQueue *Q) {
    if (Q->front == Q->rear) {
        printf("暂无3天内到期的图书\n");
        return;
    }

    char curDate[20];
    getCurrentDate(curDate);
    int found = 0;

    // 第一步：先遍历判断是否有符合条件的记录
    int i = Q->front;
    while (i != Q->rear) {
        BorrowNode *p = Q->data[i];
        if (p != NULL && p->status == 0) {
            int days = getDaysDiff(curDate, p->dueDate);
            if (days <= 3) {
                found = 1;
                break;
            }
        }
        i = (i + 1) % MAX_QUEUE;
    }

    // 无符合条件记录，直接返回，不打印表头
    if (!found) {
        printf("暂无3天内到期的图书\n");
        return;
    }

    // 有记录才打印表头
    printf("%-8s%-8s%-16s%-8s\n",
           "用户ID", "图书ID", "应还日期", "状态");

    // 输出数据
    i = Q->front;
    while (i != Q->rear) {
        BorrowNode *p = Q->data[i];
        if (p != NULL && p->status == 0) {
            int days = getDaysDiff(curDate, p->dueDate);
            if (days <= 3) {
                char statusStr[20];
                if (days < 0)
                    sprintf(statusStr, "已逾期%d天", -days);
                else if (days == 0)
                    strcpy(statusStr, "今日到期");
                else
                    sprintf(statusStr, "剩余%d天", days);

                printf("%-8d%-8d%-16s%-8s\n",
                       p->userId, p->bookId, p->dueDate, statusStr);
            }
        }
        i = (i + 1) % MAX_QUEUE;
    }
}

/* 统计用户在借数量 - 仅统计在借 */
int countUserBorrowed(BorrowNode* head, int userId) {
    int count = 0;
    BorrowNode* p = head;
    while (p != NULL) {
        if (p->userId == userId && p->status == 0) {
            count++;
        }
        p = p->next;
    }
    return count;
}
