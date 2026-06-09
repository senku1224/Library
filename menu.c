#include "menu.h"
#include <stdio.h>

void mainMenu(User users[], int *userCount)
{
    int choice;
    while(1)
    {
        clearScreen();
        printf("==== 图书馆管理系统 ====\n");
        printf("1. 登录\n2. 注册\n3. 退出\n");
        printf("请选择: ");
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                login(users, *userCount);
                if(currentUser.id != 0)
                {
                    if(currentUser.role == ADMIN)
                        adminMenu(users,*userCount);
                    else if(currentUser.role == STUDENT)
                        studentMenu();
                    else
                        teacherMenu();
                }
                break;
            case 2:
                registerUser(users, userCount);
                pauseScreen();
                break;
            case 3:
                return;
            default:
                printf("无效选项\n");
                pauseScreen();
        }
    }
}

void adminMenu(User users[], int userCount)
{
    int choice;
    while(1)
    {
        clearScreen();
        printf("==== 管理员菜单 ====\n");
        printf("1. 图书管理\n2. 用户管理\n3. 借阅管理\n4. 统计分析\n5. 查看日志\n6. 返回主菜单\n");
        printf("请选择: ");
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                addBook();
                deleteBook();
                updateBook();
                searchBook();
                showAllBooks();
                pauseScreen();
                break;
            case 2:
                deleteUser(users, &userCount);
                showUsers(users,userCount);
                changePassword(&currentUser);
                pauseScreen();
                break;
            case 3:
                QueryAllBorrow(borrowHead);
                ShowRemindInfo(&remindQueue);
                pauseScreen();
                break;
            case 4:
                statisticsBorrow();
                rankBook();
                statisticsCategory();
                statisticsUser();
                pauseScreen();
                break;
            case 5:
                showLogs(&logStack);
                pauseScreen();
                break;
            case 6:
                return;
            default:
                printf("无效选项\n");
                pauseScreen();
        }
    }
}

void studentMenu()
{
    int choice;
    while(1)
    {
        clearScreen();
        printf("==== 学生菜单 ====\n");
        printf("1. 查询图书\n2. 借书\n3. 还书\n4. 我的借阅\n5. 到期提醒\n6. 修改密码\n7. 返回\n");
        printf("请选择: ");
        scanf("%d",&choice);
        getchar();

        switch(choice)
        {
            case 1:
                searchBook(); pauseScreen(); break;
            case 2:
                {
                    int bookId;
                    char bDate[20], dDate[20];
                    printf("输入图书ID: ");
                    scanf("%d",&bookId);
                    getCurrentDate(bDate);
                    strcpy(dDate,"2026-06-20"); // 示例应还日期，可用计算函数替换
                    BorrowBook(&borrowHead,currentUser.id,bookId,bDate,dDate);
                    pauseScreen();
                }
                break;
            case 3:
                {
                    int bookId;
                    printf("输入归还图书ID: ");
                    scanf("%d",&bookId);
                    ReturnBook(&borrowHead,currentUser.id,bookId);
                    pauseScreen();
                }
                break;
            case 4:
                QueryUserBorrow(borrowHead,currentUser.id);
                pauseScreen();
                break;
            case 5:
                ShowRemindInfo(&remindQueue);
                pauseScreen();
                break;
            case 6:
                changePassword(&currentUser);
                pauseScreen();
                break;
            case 7:
                return;
            default:
                printf("无效选项\n");
                pauseScreen();
        }
    }
}

void teacherMenu()
{
    int choice;
    while(1)
    {
        clearScreen();
        printf("==== 教师菜单 ====\n");
        printf("1. 查询图书\n2. 借书\n3. 还书\n4. 我的借阅\n5. 到期提醒\n6. 修改密码\n7. 返回\n");
        printf("请选择: ");
        scanf("%d",&choice);
        getchar();

        switch(choice)
        {
            case 1:
                searchBook(); pauseScreen(); break;
            case 2:
                {
                    int bookId;
                    char bDate[20], dDate[20];
                    printf("输入图书ID: ");
                    scanf("%d",&bookId);
                    getCurrentDate(bDate);
                    strcpy(dDate,"2026-06-20"); // 示例应还日期
                    BorrowBook(&borrowHead,currentUser.id,bookId,bDate,dDate);
                    pauseScreen();
                }
                break;
            case 3:
                {
                    int bookId;
                    printf("输入归还图书ID: ");
                    scanf("%d",&bookId);
                    ReturnBook(&borrowHead,currentUser.id,bookId);
                    pauseScreen();
                }
                break;
            case 4:
                QueryUserBorrow(borrowHead,currentUser.id);
                pauseScreen();
                break;
            case 5:
                ShowRemindInfo(&remindQueue);
                pauseScreen();
                break;
            case 6:
                changePassword(&currentUser);
                pauseScreen();
                break;
            case 7:
                return;
            default:
                printf("无效选项\n");
                pauseScreen();
        }
    }
}