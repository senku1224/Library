#include "statistics.h"

void statisticsBorrow()
{
    int totalBorrow = 0;
    int remainBooks = 0;
    int borrowedBooks = 0;
    for(int i=0;i<bookCount;i++)
    {
        totalBorrow += books[i].borrowCount;
        remainBooks += books[i].remain;
        borrowedBooks += books[i].total - books[i].remain;
    }
    printf("\n=====借阅统计=====\n");
    printf("累计借阅次数：%d\n", totalBorrow);
    printf("当前借出册数：%d\n", borrowedBooks);
    printf("当前在馆册数：%d\n", remainBooks);
}

void rankBook()
{
    if(bookCount == 0) {
        printf("暂无图书\n");
        return;
    }
    Book temp[MAX_BOOKS];
    for(int i=0;i<bookCount;i++) temp[i] = books[i];

    for(int i=0;i<bookCount-1;i++)
    {
        for(int j=0;j<bookCount-1-i;j++)
        {
            if(temp[j].borrowCount < temp[j+1].borrowCount)
            {
                Book t = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = t;
            }
        }
    }
    printf("\n=====热门图书排行榜=====\n");
    for(int i=0; i<bookCount && i<10; i++)
    {
        printf("%d. %s (%d次)\n", i+1, temp[i].name, temp[i].borrowCount);
    }
}

void statisticsCategory()
{
    CategoryNode *p = categoryHead;
    printf("\n=====图书分类统计=====\n");
    while(p)
    {
        int count = 0;
        for(int i=0; i<bookCount; i++)
        {
            if(strcmp(books[i].category, p->name) == 0) count++;
        }
        printf("%s : %d本\n", p->name, count);
        p = p->next;
    }
}

/* 修改：仅统计在借数量 */
void statisticsUser()
{
    int borrowCounter[MAX_USERS]={0};
    BorrowNode *p = borrowHead;
    while(p)
    {
        if(p->status == 0) // 仅统计在借
        {
            for(int i=0; i<userCount; i++)
            {
                if(users[i].id == p->userId)
                {
                    borrowCounter[i]++;
                }
            }
        }
        p = p->next;
    }
    printf("\n=====用户在借统计=====\n");
    for(int i=0; i<userCount; i++)
    {
        printf("%s : 在借 %d 本\n", users[i].username, borrowCounter[i]);
    }
}
