#ifndef BORROW_H
#define BORROW_H

#include "common.h"
#include "book.h"

// 全局借阅链表和提醒队列
extern BorrowNode *borrowHead;
extern ReminderQueue remindQueue;

// 借阅管理功能
void InitBorrowList(BorrowNode **head);

int BorrowBook(BorrowNode **head, int userId, int bookId, char borrowDate[], char dueDate[]);
int ReturnBook(BorrowNode **head, int userId, int bookId);

void QueryUserBorrow(BorrowNode *head, int userId);
void QueryAllBorrow(BorrowNode *head);

// 提醒队列操作
void InitReminderQueue(ReminderQueue *Q);
int EnQueue(ReminderQueue *Q, BorrowNode *node);
BorrowNode* DeQueue(ReminderQueue *Q);
void LoadRemindData(BorrowNode *head, ReminderQueue *Q);
void ShowRemindInfo(ReminderQueue *Q);

#endif
