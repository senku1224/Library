#include "common.h"


/*=========================
  清屏
=========================*/

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/*=========================
  暂停
=========================*/

void pauseScreen()
{
    printf("\n按回车继续...");
    getchar();
}

/*=========================
  获取日期
=========================*/

void getCurrentDate(char date[])
{
    time_t now = time(NULL);

    struct tm *t =
        localtime(&now);

    sprintf(
        date,
        "%04d-%02d-%02d",
        t->tm_year + 1900,
        t->tm_mon + 1,
        t->tm_mday
    );
}

/*=========================
  管理员判断
=========================*/

int isAdmin(User *user)
{
    if(user == NULL)
    {
        return 0;
    }

    return user->role == ADMIN;
}

/*=========================
  日志栈
=========================*/

void initLogStack(LogStack *stack)
{
    stack->top = -1;
}

void pushLog(
        LogStack *stack,
        char msg[]
)
{
    if(stack->top >= MAX_LOGS - 1)
    {
        return;
    }

    stack->top++;

    strcpy(
        stack->data[stack->top].operation,
        msg
    );
}

void popLog(
        LogStack *stack
)
{
    if(stack->top == -1)
    {
        return;
    }

    stack->top--;
}

void showLogs(
        LogStack *stack
)
{
    if(stack->top == -1)
    {
        printf("暂无日志\n");
        return;
    }

    for(
        int i = stack->top;
        i >= 0;
        i--
    )
    {
        printf(
            "%s\n",
            stack->data[i].operation
        );
    }
}
