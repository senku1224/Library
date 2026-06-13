#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "common.h"

/* 用户数据 */

void loadUsers(
        User users[],
        int *userCount
);

void saveUsers(
        User users[],
        int userCount
);

/* 图书数据 */

void loadBooks(
        Book books[],
        int *bookCount
);

void saveBooks(
        Book books[],
        int bookCount
);

/* 分类数据 */

void loadCategories(
        CategoryNode **head
);

void saveCategories(
        CategoryNode *head
);

/* 借阅数据 */

void loadBorrowRecords(
        BorrowNode **head
);

void saveBorrowRecords(
        BorrowNode *head
);

#endif
