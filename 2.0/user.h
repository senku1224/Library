#ifndef USER_H
#define USER_H

#include "common.h"

// 全局用户数组
extern User users[MAX_USERS];
extern int userCount;

// 用户管理功能
void login(User users[], int count);
void registerUser(User users[], int *count);
void deleteUser(User users[], int *count);
void showUsers(User users[], int count);
void changePassword(User *user);




#endif
