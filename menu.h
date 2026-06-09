#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "user.h"
#include "book.h"
#include "borrow.h"
#include "statistics.h"

// 菜单功能
void mainMenu(User users[], int *userCount);

void adminMenu(User users[], int userCount);
void studentMenu();
void teacherMenu();

#endif