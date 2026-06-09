#include "fileManager.h"

/*=========================
  用户文件
=========================*/

void loadUsers(
        User users[],
        int *userCount
)
{
    FILE *fp =
        fopen("users.txt","r");

    if(fp == NULL)
    {
        *userCount = 0;
        return;
    }

    *userCount = 0;

    while(
        fscanf(
            fp,
            "%d %s %s %d",
            &users[*userCount].id,
            users[*userCount].username,
            users[*userCount].password,
            &users[*userCount].role
        ) == 4
    )
    {
        (*userCount)++;
    }

    fclose(fp);
}

void saveUsers(
        User users[],
        int userCount
)
{
    FILE *fp =
        fopen("users.txt","w");

    if(fp == NULL)
        return;

    for(
        int i=0;
        i<userCount;
        i++
    )
    {
        fprintf(
            fp,
            "%d %s %s %d\n",
            users[i].id,
            users[i].username,
            users[i].password,
            users[i].role
        );
    }

    fclose(fp);
}

/*=========================
  图书文件
=========================*/

void loadBooks(
        Book books[],
        int *bookCount
)
{
    FILE *fp =
        fopen("books.txt","r");

    if(fp == NULL)
    {
        *bookCount = 0;
        return;
    }

    *bookCount = 0;

    while(
        fscanf(
            fp,
            "%d %s %s %s %d %d %d",
            &books[*bookCount].id,
            books[*bookCount].name,
            books[*bookCount].author,
            books[*bookCount].category,
            &books[*bookCount].total,
            &books[*bookCount].remain,
            &books[*bookCount].borrowCount
        ) == 7
    )
    {
        (*bookCount)++;
    }

    fclose(fp);
}

void saveBooks(
        Book books[],
        int bookCount
)
{
    FILE *fp =
        fopen("books.txt","w");

    if(fp == NULL)
        return;

    for(
        int i=0;
        i<bookCount;
        i++
    )
    {
        fprintf(
            fp,
            "%d %s %s %s %d %d %d\n",
            books[i].id,
            books[i].name,
            books[i].author,
            books[i].category,
            books[i].total,
            books[i].remain,
            books[i].borrowCount
        );
    }

    fclose(fp);
}


/*=========================
  分类文件
=========================*/

void loadCategories(
        CategoryNode **head
)
{
    FILE *fp =
        fopen("category.txt","r");

    if(fp == NULL)
    {
        *head = NULL;
        return;
    }

    *head = NULL;

    char buf[50];

    while(
        fscanf(fp,"%s",buf) == 1
    )
    {
        CategoryNode *node =
            (CategoryNode*)
            malloc(sizeof(CategoryNode));

        strcpy(
            node->name,
            buf
        );

        node->next = *head;

        *head = node;
    }

    fclose(fp);
}

void saveCategories(
        CategoryNode *head
)
{
    FILE *fp =
        fopen("category.txt","w");

    if(fp == NULL)
        return;

    CategoryNode *p = head;

    while(p)
    {
        fprintf(
            fp,
            "%s\n",
            p->name
        );

        p = p->next;
    }

    fclose(fp);
}

void loadBorrowRecords(
        BorrowNode **head
)
{
    FILE *fp =
        fopen("borrow.txt","r");

    if(fp == NULL)
    {
        *head = NULL;
        return;
    }

    *head = NULL;

    while(1)
    {
        BorrowNode *node =
            (BorrowNode*)
            malloc(sizeof(BorrowNode));

        if(
            fscanf(
                fp,
                "%d %d %s %s",
                &node->userId,
                &node->bookId,
                node->borrowDate,
                node->dueDate
            ) != 4
        )
        {
            free(node);
            break;
        }

        node->prev = NULL;
        node->next = *head;

        if(*head)
            (*head)->prev = node;

        *head = node;
    }

    fclose(fp);
}

void saveBorrowRecords(
        BorrowNode *head
)
{
    FILE *fp =
        fopen("borrow.txt","w");

    if(fp == NULL)
        return;

    BorrowNode *p = head;

    while(p)
    {
        fprintf(
            fp,
            "%d %d %s %s\n",
            p->userId,
            p->bookId,
            p->borrowDate,
            p->dueDate
        );

        p = p->next;
    }

    fclose(fp);
}
