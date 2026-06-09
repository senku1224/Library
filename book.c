#include "book.h"
#include <stdio.h>
#include <string.h>



/*=========================
  添加图书
=========================*/
void addBook()
{
    if(bookCount >= MAX_BOOKS)
    {
        printf("图书已满，无法添加。\n");
        return;
    }

    Book b;
    b.id = bookCount + 1;

    printf("请输入书名: ");
    scanf("%s", b.name);
    printf("请输入作者: ");
    scanf("%s", b.author);
    printf("请输入分类: ");
    scanf("%s", b.category);
    printf("请输入馆藏总数: ");
    scanf("%d", &b.total);

    b.remain = b.total;
    b.borrowCount = 0;

    books[bookCount] = b;
    bookCount++;

    printf("添加成功，图书ID: %d\n", b.id);

    char logMsg[100];
    sprintf(logMsg,"管理员添加图书: %s", b.name);
    pushLog(&logStack, logMsg);
}

/*=========================
  删除图书
=========================*/
void deleteBook()
{
    int id;
    printf("请输入要删除的图书ID: ");
    scanf("%d",&id);

    int found = 0;
    for(int i=0;i<bookCount;i++)
    {
        if(books[i].id == id)
        {
            found = 1;
            for(int j=i;j<bookCount-1;j++)
                books[j] = books[j+1];
            bookCount--;
            printf("删除成功！\n");

            char logMsg[100];
            sprintf(logMsg,"管理员删除图书ID: %d", id);
            pushLog(&logStack, logMsg);
            break;
        }
    }
    if(!found)
        printf("未找到图书ID %d\n", id);
}

/*=========================
  修改图书
=========================*/
void updateBook()
{
    int id;
    printf("请输入要修改的图书ID: ");
    scanf("%d",&id);

    for(int i=0;i<bookCount;i++)
    {
        if(books[i].id == id)
        {
            printf("请输入新的书名: ");
            scanf("%s", books[i].name);
            printf("请输入新的作者: ");
            scanf("%s", books[i].author);
            printf("请输入新的分类: ");
            scanf("%s", books[i].category);
            printf("请输入新的馆藏总数: ");
            scanf("%d", &books[i].total);

            books[i].remain = books[i].total - books[i].borrowCount;

            printf("修改成功！\n");

            char logMsg[100];
            sprintf(logMsg,"管理员修改图书ID: %d", id);
            pushLog(&logStack, logMsg);
            return;
        }
    }
    printf("未找到图书ID %d\n", id);
}

/*=========================
  查询图书（按书名关键字）
=========================*/
void searchBook()
{
    char key[50];
    printf("请输入书名关键字: ");
    scanf("%s", key);

    int found = 0;
    printf("ID\t书名\t作者\t分类\t总数\t剩余\t借阅次数\n");

    for(int i=0;i<bookCount;i++)
    {
        if(strstr(books[i].name,key) != NULL)
        {
            printf("%d\t%s\t%s\t%s\t%d\t%d\t%d\n",
                   books[i].id,
                   books[i].name,
                   books[i].author,
                   books[i].category,
                   books[i].total,
                   books[i].remain,
                   books[i].borrowCount);
            found = 1;
        }
    }
    if(!found)
        printf("未找到相关图书。\n");
}

/*=========================
  显示所有图书
=========================*/
void showAllBooks()
{
    if(bookCount == 0)
    {
        printf("当前没有图书。\n");
        return;
    }

    printf("ID\t书名\t作者\t分类\t总数\t剩余\t借阅次数\n");

    for(int i=0;i<bookCount;i++)
    {
        printf("%d\t%s\t%s\t%s\t%d\t%d\t%d\n",
               books[i].id,
               books[i].name,
               books[i].author,
               books[i].category,
               books[i].total,
               books[i].remain,
               books[i].borrowCount);
    }
}
