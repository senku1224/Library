#include "fileManager.h"

/* 用户文件 - 加载 */
void loadUsers(User users[], int *userCount)
{
    FILE *fp = fopen("users.txt","r");
    if(fp == NULL)
    {
        *userCount = 0;
        return;
    }
    *userCount = 0;
    while(fscanf(fp, "%d %s %s %d",
                 &users[*userCount].id,
                 users[*userCount].username,
                 users[*userCount].password,
                 &users[*userCount].role) == 4)
    {
        (*userCount)++;
    }
    fclose(fp);
}

/* 用户文件 - 保存 */
void saveUsers(User users[], int userCount)
{
    FILE *fp = fopen("users.txt","w");
    if(fp == NULL) return;
    for(int i=0;i<userCount;i++)
    {
        fprintf(fp, "%d %s %s %d\n",
                users[i].id, users[i].username, users[i].password, users[i].role);
    }
    fclose(fp);
}

/* 图书文件 - 加载 */
void loadBooks(Book books[], int *bookCount)
{
    FILE *fp = fopen("books.txt","r");
    if(fp == NULL)
    {
        *bookCount = 0;
        return;
    }
    *bookCount = 0;
    while(fscanf(fp, "%d %s %s %s %d %d %d",
                 &books[*bookCount].id,
                 books[*bookCount].name,
                 books[*bookCount].author,
                 books[*bookCount].category,
                 &books[*bookCount].total,
                 &books[*bookCount].remain,
                 &books[*bookCount].borrowCount) == 7)
    {
        (*bookCount)++;
    }
    fclose(fp);
}

/* 图书文件 - 保存 */
void saveBooks(Book books[], int bookCount)
{
    FILE *fp = fopen("books.txt","w");
    if(fp == NULL) return;
    for(int i=0;i<bookCount;i++)
    {
        fprintf(fp, "%d %s %s %s %d %d %d\n",
                books[i].id, books[i].name, books[i].author,
                books[i].category, books[i].total, books[i].remain, books[i].borrowCount);
    }
    fclose(fp);
}

/* 分类文件 - 加载 */
void loadCategories(CategoryNode **head)
{
    FILE *fp = fopen("category.txt","r");
    if(fp == NULL)
    {
        *head = NULL;
        return;
    }
    *head = NULL;
    char buf[50];
    while(fscanf(fp,"%s",buf) == 1)
    {
        CategoryNode *node = (CategoryNode*)malloc(sizeof(CategoryNode));
        strcpy(node->name, buf);
        node->next = *head;
        *head = node;
    }
    fclose(fp);
}

/* 分类文件 - 保存 */
void saveCategories(CategoryNode *head)
{
    FILE *fp = fopen("category.txt","w");
    if(fp == NULL) return;
    CategoryNode *p = head;
    while(p)
    {
        fprintf(fp, "%s\n", p->name);
        p = p->next;
    }
    fclose(fp);
}

/* 借阅记录 - 加载（兼容旧格式） */
void loadBorrowRecords(BorrowNode **head) {
    FILE *fp = fopen("borrow.txt", "r");
    if (fp == NULL) {
        *head = NULL;
        return;
    }
    *head = NULL;
    char line[256];

    // 逐行读取，避免跨行列错位
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // 去掉换行符
        if (strlen(line) == 0) continue;   // 跳过空行

        BorrowNode *node = (BorrowNode*)malloc(sizeof(BorrowNode));
        // 默认值：在借、无归还日期
        node->status = 0;
        strcpy(node->returnDate, "-");
        node->prev = NULL;
        node->next = NULL;

        // 拆分字段：兼容4字段（旧格式）和6字段（新格式）
        int res = sscanf(line, "%d %d %s %s %d %s",
                        &node->userId, &node->bookId,
                        node->borrowDate, node->dueDate,
                        &node->status, node->returnDate);

        if (res >= 4) {
            // 头插法插入链表
            node->next = *head;
            if (*head != NULL) {
                (*head)->prev = node;
            }
            *head = node;
        } else {
            free(node); // 格式错误，丢弃
        }
    }
    fclose(fp);
}

/* 借阅记录 - 保存（含状态和归还日期） */
void saveBorrowRecords(BorrowNode *head) {
    FILE *fp = fopen("borrow.txt", "w");
    if (fp == NULL) return;
    BorrowNode *p = head;
    while (p) {
        fprintf(fp, "%d %d %s %s %d %s\n",
                p->userId, p->bookId,
                p->borrowDate, p->dueDate,
                p->status, p->returnDate);
        p = p->next;
    }
    fclose(fp);
}
