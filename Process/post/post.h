#ifndef POST_H
#define POST_H
#include "../../base.h"
#include "../../Lists/BookList/booklist.h"



extern int changeBookInfo(BookList* mainBookList, Book* book);

extern int post(BookList* mainBookList, UserInfo* onlineUser);

#endif
