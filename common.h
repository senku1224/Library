#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*=========================
  系统参数
=========================*/

#define MAX_BOOKS      1000
#define MAX_USERS      500
#define MAX_LOGS       1000
#define MAX_QUEUE      1000

/*=========================
  用户角色
=========================*/

#define STUDENT 0
#define TEACHER 1
#define ADMIN   2

/*=========================
  图书结构体
=========================*/

typedef struct
{
    int id;

    char name[50];
    char author[50];
    char category[30];

    int total;
    int remain;

    int borrowCount;

}Book;

/*=========================
  用户结构体
=========================*/

typedef struct
{
    int id;

    char username[30];
    char password[30];

    int role;

}User;

/*=========================
  借阅双向链表
=========================*/

typedef struct BorrowNode
{
    int userId;
    int bookId;

    char borrowDate[20];
    char dueDate[20];

    struct BorrowNode *prev;
    struct BorrowNode *next;

}BorrowNode;

/*=========================
  分类链表
=========================*/

typedef struct CategoryNode
{
    char name[30];

    struct CategoryNode *next;

}CategoryNode;

/*=========================
  日志栈
=========================*/

typedef struct
{
    char operation[100];

}Log;

typedef struct
{
    Log data[MAX_LOGS];

    int top;

}LogStack;

/*=========================
  提醒队列
=========================*/

typedef struct
{
    BorrowNode *data[MAX_QUEUE];

    int front;
    int rear;

}ReminderQueue;

/*=========================
  全局变量声明
=========================*/

extern User currentUser;

extern LogStack logStack;

/*=========================
  公共函数
=========================*/

void clearScreen();

void pauseScreen();

void getCurrentDate(char date[]);

int isAdmin(User *user);

/*=========================
  日志函数
=========================*/

void initLogStack(LogStack *stack);

void pushLog(
        LogStack *stack,
        char msg[]
);

void popLog(
        LogStack *stack
);

void showLogs(
        LogStack *stack
);

#endif

/* 用户顺序表 */
extern User users[MAX_USERS];
extern int userCount;

/* 图书顺序表 */
extern Book books[MAX_BOOKS];
extern int bookCount;

/* 借阅链表 */
extern BorrowNode *borrowHead;

/* 分类链表 */
extern CategoryNode *categoryHead;

/* 提醒队列 */
extern ReminderQueue remindQueue;