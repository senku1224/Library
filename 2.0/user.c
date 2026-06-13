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
            while(getchar() != '\n');
            pauseScreen();
            char logMsg[100];
            sprintf(logMsg,"用户 %s 登录", currentUser.username);
            pushLog(&logStack,logMsg);

            return;
        }
    }

    printf("用户名或密码错误\n");
    currentUser.id = 0;
    while(getchar() != '\n');
    pauseScreen();
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
    User u;   // 你的原始变量名：u 不是 newUser
    u.id = *count + 1;
    printf("请输入用户名: ");
    scanf("%s", u.username);

    // 强制规则：默认学生、默认密码123456
    strcpy(u.password, "123456");
    u.role = STUDENT;
    u.isFirstLogin = 1;

    users[*count] = u;
    (*count)++;
    printf("注册成功！默认密码：123456\n");
    char logMsg[100];
    sprintf(logMsg,"注册新用户 %s", u.username);
    pushLog(&logStack, logMsg);
    getchar();
}

/*=========================
  删除用户（管理员使用）
=========================*/
void deleteUser(User users[], int *userCount) {
    int userId;
    printf("请输入要删除的用户ID: ");
    scanf("%d", &userId);
    getchar();
    if(userId == currentUser.id && isAdmin(&currentUser)) {
        printf("不能删除当前登录的管理员！\n");
        return;
    }
    char confirm;
    printf("确定要删除该用户吗？(Y/N): ");
    scanf("%c", &confirm);
    getchar();
    if(confirm == 'Y' || confirm == 'y') { // 修正判断条件
        int found = 0;
        for(int i=0; i<*userCount; i++) {
            if(users[i].id == userId) {
                found = 1;
                for(int j=i; j<*userCount-1; j++) {
                    users[j] = users[j+1];
                }
                (*userCount)--;
                printf("用户删除成功！\n");
                break;
            }
        }
        if(!found) printf("未找到该用户！\n");
    } else {
        printf("已取消删除操作！\n");
    }
}

/*=========================
  查看用户
=========================*/
void showUsers(User users[], int count)
{
    printf("%-6s%-14s%-8s\n","ID","用户名","角色");
    for(int i=0;i<count;i++)
    {
        printf("%-6d%-14s%-8d\n", users[i].id, users[i].username, users[i].role);
    }
}

/*=========================
  修改密码
=========================*/
void changePassword(User *user)
{
    char oldPwd[20], newPwd[20], confirmPwd[20];
    printf("请输入旧密码: ");
    scanf("%s", oldPwd);
    if (strcmp(user->password, oldPwd) != 0) {
        printf("旧密码错误！\n");
        getchar();
        return;
    }
    printf("请输入新密码: ");
    scanf("%s", newPwd);
    printf("请确认新密码: ");
    scanf("%s", confirmPwd);
    if (strcmp(newPwd, confirmPwd) != 0) {
        printf("两次密码不一致！\n");
        getchar();
        return;
    }

    strcpy(user->password, newPwd);
    // 老师修改密码后，清除首次登录标记
    if (user->role == 1) {
        user->isFirstLogin = 0;
    }

    printf("修改成功！\n");

    char logMsg[100];
    sprintf(logMsg,"用户 %s 修改密码", user->username);
    pushLog(&logStack, logMsg);
    getchar();
}
