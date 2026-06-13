#ifndef BOOK_H
#define BOOK_H

#include "common.h"

// 全局图书数组
extern Book books[MAX_BOOKS];
extern int bookCount;

// 图书管理功能
void addBook();
void deleteBook();
void updateBook();
void searchBook();
void showAllBooks();
void suggestBook();


#endif
