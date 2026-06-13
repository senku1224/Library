#include "common.h"

User users[MAX_USERS];
int userCount = 0;

Book books[MAX_BOOKS];
int bookCount = 0;

BorrowNode *borrowHead = NULL;

CategoryNode *categoryHead = NULL;

ReminderQueue remindQueue;

User currentUser;

LogStack logStack;