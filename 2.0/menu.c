#include "menu.h"
#include <stdio.h>

/* 主菜单 */
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

/* 管理员菜单 */
void adminMenu(User users[], int userCount)
{
    int choice;
    while(1)
    {
        clearScreen();
        printf("==== 管理员主菜单 ====\n");
        printf("1. 图书管理\n2. 用户管理\n3. 借阅管理\n4. 统计分析\n5. 查看日志\n6. 返回主菜单\n");
        printf("请选择: ");
        scanf("%d", &choice);
        getchar();
        switch(choice)
        {
            case 1:
            {
                int bookOpt;
                while(1)
                {
                    clearScreen();
                    printf("==== 图书管理子菜单 ====\n");
                    printf("1. 添加图书\n2. 删除图书\n3. 修改图书\n4. 按关键字查询图书\n5. 查看全部图书\n6. 返回上一级\n");
                    printf("请选择操作: ");
                    scanf("%d", &bookOpt);
                    getchar();
                    switch(bookOpt)
                    {
                        case 1: addBook(); pauseScreen(); break;
                        case 2: deleteBook(); pauseScreen(); break;
                        case 3: updateBook(); pauseScreen(); break;
                        case 4: searchBook(); pauseScreen(); break;
                        case 5: showAllBooks(); pauseScreen(); break;
                        case 6: goto bookMenuExit;
                        default: printf("无效选项！\n"); pauseScreen();
                    }
                }
                bookMenuExit:
                break;
            }
            case 2:
            {
                int userOpt;
                while(1)
                {
                    clearScreen();
                    printf("==== 用户管理子菜单 ====\n");
                    printf("1. 查看所有用户\n2. 删除用户\n3. 修改个人密码\n4. 修改角色\n5. 返回上一级\n");
                    printf("请选择操作: ");
                    scanf("%d", &userOpt);
                    getchar();
                    switch(userOpt)
                    {
                        case 1: showUsers(users, userCount); pauseScreen(); break;
                        case 2: deleteUser(users, &userCount); pauseScreen(); break;
                        case 3: changePassword(&currentUser); pauseScreen(); break;
                        case 4:
                        {
                            int userId, newRole;
                            printf("请输入要修改角色的用户ID: ");
                            scanf("%d", &userId);
                            int found = 0;
                            for (int i=0; i<userCount; i++) {
                                if (users[i].id == userId) {
                                    found = 1;
                                    printf("请输入新角色(0:学生,1:老师): ");
                                    scanf("%d", &newRole);
                                    if (newRole != 0 && newRole != 1) {
                                        printf("无效角色！只能设置为学生或老师！\n");
                                        getchar();
                                        break;
                                    }
                                    users[i].role = newRole;
                                    if (newRole == 1) users[i].isFirstLogin = 1;
                                    printf("用户角色修改成功！\n");
                                    getchar();
                                    break;
                                }
                            }
                            if (!found) printf("未找到该用户！\n");
                            break;
                        }
                        case 5: goto userMenuExit;
                        default: printf("无效选项！\n"); pauseScreen();
                    }
                }
                userMenuExit:
                break;
            }
            case 3:
            {
                int borrowOpt;
                while(1)
                {
                    clearScreen();
                    printf("==== 借阅管理子菜单 ====\n");
                    printf("1. 查看全部借阅记录\n2. 查看到期提醒\n3. 返回上一级\n");
                    printf("请选择操作: ");
                    scanf("%d", &borrowOpt);
                    getchar();
                    switch(borrowOpt)
                    {
                        case 1: QueryAllBorrow(borrowHead); pauseScreen(); break;
                        case 2: ShowRemindInfo(&remindQueue); pauseScreen(); break;
                        case 3: goto borrowMenuExit;
                        default: printf("无效选项！\n"); pauseScreen();
                    }
                }
                borrowMenuExit:
                break;
            }
            case 4:
            {
                int statOpt;
                while(1)
                {
                    clearScreen();
                    printf("==== 统计分析子菜单 ====\n");
                    printf("1. 借阅整体统计\n2. 热门图书排行榜\n3. 图书分类统计\n4. 用户借阅统计\n5. 返回上一级\n");
                    printf("请选择统计类型: ");
                    scanf("%d", &statOpt);
                    getchar();
                    switch(statOpt)
                    {
                        case 1: statisticsBorrow(); pauseScreen(); break;
                        case 2: rankBook(); pauseScreen(); break;
                        case 3: statisticsCategory(); pauseScreen(); break;
                        case 4: statisticsUser(); pauseScreen(); break;
                        case 5: goto statMenuExit;
                        default: printf("无效选项！\n"); pauseScreen();
                    }
                }
                statMenuExit:
                break;
            }
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

/* 学生菜单 - 调整选项 */
void studentMenu()
{
    int choice;
    while(1)
    {
        clearScreen();
        printf("==== 学生菜单 ====\n");
        printf("1. 查询图书\n2. 借书\n3. 还书\n4. 在借图书\n5. 我的借阅记录\n6. 到期提醒\n7. 修改密码\n8. 统计分析\n9. 返回\n");
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
                QueryUserBorrowHistory(borrowHead,currentUser.id);
                pauseScreen();
                break;
            case 6:
                ShowRemindInfo(&remindQueue);
                pauseScreen();
                break;
            case 7:
                changePassword(&currentUser);
                pauseScreen();
                break;

            case 8:
            {
                int statOpt;
                while(1)
                {
                    clearScreen();
                    printf("==== 统计分析子菜单 ====\n");
                    printf("1. 借阅整体统计\n2. 热门图书排行榜\n3. 图书分类统计\n4. 用户借阅统计\n5. 返回上一级\n");
                    printf("请选择统计类型: ");
                    scanf("%d", &statOpt);
                    getchar();
                    switch(statOpt)
                    {
                        case 1: statisticsBorrow(); pauseScreen(); break;
                        case 2: rankBook(); pauseScreen(); break;
                        case 3: statisticsCategory(); pauseScreen(); break;
                        case 4: statisticsUser(); pauseScreen(); break;
                        case 5: goto statMenuExit;
                        default: printf("无效选项！\n"); pauseScreen();
                    }
                }
                statMenuExit:
                break;
            }
            case 9:
                return;
            default:
                printf("无效选项\n");
                pauseScreen();
        }
    }
}

/* 教师菜单 - 调整选项 */
void teacherMenu()
{
    int choice;
    while(1)
    {
        clearScreen();
        printf("==== 教师菜单 ====\n");
        printf("1. 查询图书\n2. 借书\n3. 还书\n4. 在借图书\n5. 我的借阅记录\n6. 到期提醒\n7. 修改密码\n8. 建议购书\n9. 统计分析\n10. 返回\n");
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
                QueryUserBorrowHistory(borrowHead,currentUser.id);
                pauseScreen();
                break;
            case 6:
                ShowRemindInfo(&remindQueue);
                pauseScreen();
                break;
            case 7:
                changePassword(&currentUser);
                pauseScreen();
                break;
            case 8:
                suggestBook();
                pauseScreen();
                break;
            case 9:
            {
                int statOpt;
                while(1)
                {
                    clearScreen();
                    printf("==== 统计分析子菜单 ====\n");
                    printf("1. 借阅整体统计\n2. 热门图书排行榜\n3. 图书分类统计\n4. 用户借阅统计\n5. 返回上一级\n");
                    printf("请选择统计类型: ");
                    scanf("%d", &statOpt);
                    getchar();
                    switch(statOpt)
                    {
                        case 1: statisticsBorrow(); pauseScreen(); break;
                        case 2: rankBook(); pauseScreen(); break;
                        case 3: statisticsCategory(); pauseScreen(); break;
                        case 4: statisticsUser(); pauseScreen(); break;
                        case 5: goto statMenuExit;
                        default: printf("无效选项！\n"); pauseScreen();
                    }
                }
                statMenuExit:
                break;
            }
            case 10:
                return;
            default:
                printf("无效选项\n");
                pauseScreen();
        }
    }
}
