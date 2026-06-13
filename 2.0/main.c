#include "common.h"
#include "menu.h"
#include "fileManager.h"

int main()
{
    // 初始化日志
    initLogStack(&logStack);

    // 加载数据
    loadUsers(users,&userCount);
    loadBooks(books,&bookCount);
    loadCategories(&categoryHead);
    loadBorrowRecords(&borrowHead);

    InitReminderQueue(&remindQueue);
    LoadRemindData(borrowHead,&remindQueue);

    // 如果没有管理员，创建默认管理员
    int hasAdmin = 0;
    for(int i=0;i<userCount;i++)
    {
        if(users[i].role==ADMIN) { hasAdmin=1; break; }
    }
    if(!hasAdmin)
    {
        users[userCount].id = userCount+1;
        strcpy(users[userCount].username,"admin");
        strcpy(users[userCount].password,"admin");
        users[userCount].role=ADMIN;
        userCount++;
    }

    // 启动主菜单
    mainMenu(users,&userCount);

    // 保存数据
    saveUsers(users,userCount);
    saveBooks(books,bookCount);
    saveCategories(categoryHead);
    saveBorrowRecords(borrowHead);

    printf("系统已退出。\n");
    return 0;
}
