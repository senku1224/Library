#include "user.h"
#include <stdio.h>
#include <string.h>



/*=========================
  登录
=========================*/
void login(User users[], int count)
{
    char username[30];
    char password[30];

    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入密码: ");
    scanf("%s", password);

    for(int i=0;i<count;i++)
    {
        if(strcmp(users[i].username,username)==0 &&
           strcmp(users[i].password,password)==0)
        {
            currentUser = users[i];

            printf("登录成功，欢迎 %s\n", currentUser.username);

            char logMsg[100];
            sprintf(logMsg,"用户 %s 登录", currentUser.username);
            pushLog(&logStack,logMsg);

            return;
        }
    }

    printf("用户名或密码错误\n");
    currentUser.id = 0;
}

/*=========================
  注册
=========================*/
void registerUser(User users[], int *count)
{
    if(*count >= MAX_USERS)
    {
        printf("用户已满，无法注册。\n");
        return;
    }

    User u;
    u.id = *count + 1;

    printf("请输入用户名: ");
    scanf("%s", u.username);

    printf("请输入密码: ");
    scanf("%s", u.password);

    u.role = STUDENT; // 默认学生

    users[*count] = u;
    (*count)++;

    printf("注册成功，用户ID: %d\n", u.id);

    char logMsg[100];
    sprintf(logMsg,"注册新用户 %s", u.username);
    pushLog(&logStack, logMsg);
}

/*=========================
  删除用户（管理员使用）
=========================*/
void deleteUser(User users[], int *count)
{
    if(!isAdmin(&currentUser))
    {
        printf("权限不足！\n");
        return;
    }

    int id;
    printf("请输入要删除的用户ID: ");
    scanf("%d",&id);

    int found = 0;
    for(int i=0;i<*count;i++)
    {
        if(users[i].id == id)
        {
            found = 1;
            for(int j=i;j<*count-1;j++)
            {
                users[j] = users[j+1];
            }
            (*count)--;
            printf("删除成功！\n");

            char logMsg[100];
            sprintf(logMsg,"管理员删除用户 ID:%d", id);
            pushLog(&logStack, logMsg);
            break;
        }
    }

    if(!found)
        printf("未找到用户ID %d\n", id);
}

/*=========================
  查看用户
=========================*/
void showUsers(User users[], int count)
{
    printf("ID\t用户名\t角色\n");
    for(int i=0;i<count;i++)
    {
        printf("%d\t%s\t%d\n", users[i].id, users[i].username, users[i].role);
    }
}

/*=========================
  修改密码
=========================*/
void changePassword(User *user)
{
    char pwd[30];
    printf("请输入新密码: ");
    scanf("%s", pwd);
    strcpy(user->password, pwd);

    printf("修改成功！\n");

    char logMsg[100];
    sprintf(logMsg,"用户 %s 修改密码", user->username);
    pushLog(&logStack, logMsg);
}
