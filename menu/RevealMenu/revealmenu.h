#ifndef REVEALMENU_H
#define REVEALMENU_H
#include "../../base.h"
#include "../../Lists/BookList/booklist.h"




/// @brief 显示书籍的菜单函数
/// @param res 返回值, 如果为-1即代表返回了书籍信息指针(若不是, 返回指针为空), 如果为0代表点击了返回键, 如果>=1, 代表点击了选项, 1-->第一个, 以此类推
/// @param selectW 选项宽度
/// @param selectH 选项高度
/// @param selectNum 选项数目
/// @param selections 选项内容
/// @param backW 返回键宽度
/// @param backH 返回键高度
/// @param back 返回键内容
/// @param instruH 引导信息高度(宽度与选项一致)
/// @param instruction 引导信息内容
/// @param grapInbcAndInsrtru 返回键和引导信息的间距
/// @param dictionW 方向键宽度
/// @param dictionH 方向键高度
/// @param booksTips 书籍提示信息
/// @param bookList 书籍链表
/// @param grapInSeleAndBooks 选项和书籍信息之间的间距 
/// @param row 显示的书籍行数
/// @param col 显示的书籍列数
/// @return 如果*res为-1, 会返回书籍信息指针, 否则NULL
extern Book* revealMenu(int* res, int selectW, int selectH, int selectNum,char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInsrtru, int dictionW, int dictionH, const char* booksTips, BookList* bookList, int grapInSeleAndBooks, int row, int col);

#endif
