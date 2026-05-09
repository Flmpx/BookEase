#ifndef REVEALMENU_H
#define REVEALMENU_H
#include "../../base.h"
#include "../../Lists/BookList/booklist.h"

extern Book* revealMenu(int* res, int selectW, int selectH, int selectNum,char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInsrtru, int dictionW, int dictionH, const char* booksTips, BookList* bookList, int grapInSeleAndBooks, int row, int col);
#endif
