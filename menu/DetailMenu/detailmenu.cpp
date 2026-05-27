#include "../../base.h"
#include "../../function/function.h"
#include "../NormalMenu/normalmenu.h"
#include "../../Lists/BookList/booklist.h"
#include "../../Lists/UserList/userlist.h"
#include <easyx.h>
#include "detailmenu.h"
#include "../menu.h"

int detailUserInfoMenu(int selectW, int selectH, int selectNum, char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInstru, const char* infoTips, UserInfo* info, int grapInSeleAndInfo) {
	int screenH = getheight();
	int screenW = getwidth();
	int l, t, w, h;
	l = selectW + grapInSeleAndInfo; t = backH + grapInbcAndInstru;

	style_normal();
	w = screenW - l; h = screenH - t;
	printUserInfo(info, l, t, w, h);

	l = selectW + grapInSeleAndInfo; t = 0;
	w = screenW - l; h = backH + grapInbcAndInstru;

	style_tips();
	getRoundRectleBlock(infoTips, l, t, w, h);

	return normalMenu(selectW, selectH, selectNum, selections, backW, backH, back, instruH, instruction, grapInbcAndInstru);


}


int detailBookMenu(int selectW, int selectH, int selectNum, char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInstru, const char* infoTips, Book* book, int grapInSeleAndBook) {
	int screenH = getheight();
	int screenW = getwidth();
	int l, t, w, h;
	l = selectW + grapInSeleAndBook; t = backH + grapInbcAndInstru;
	w = screenW - l; h = screenH - t;

	style_normal();
	printAllBookInfo(book, l, t, w, h);

	l = selectW + grapInSeleAndBook; t = 0;
	w = screenW - l; h = backH + grapInbcAndInstru;

	style_tips();
	getRoundRectleBlock(infoTips, l, t, w, h);
	

	return normalMenu(selectW, selectH, selectNum, selections, backW, backH, back, instruH, instruction, grapInbcAndInstru);
}

int detailStatisticsMenu(int selectW, int selectH, int selectNum, char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInstru, const char* infoTips, BookList* mainBookList, UserList* mainUserList, int grapInSeleAndStatistics) {
	int screenH = getheight();
	int screenW = getwidth();
	int l, t, w, h;
	l = selectW + grapInSeleAndStatistics; t = backH + grapInbcAndInstru;
	w = screenW - l; h = screenH - t;

	style_normal();
	printStatistics(mainUserList, mainBookList, l, t, w, h);

	l = selectW + grapInSeleAndStatistics; t = 0;
	w = screenW - l; h = backH + grapInbcAndInstru;

	style_tips();
	getRoundRectleBlock(infoTips, l, t, w, h);

	return normalMenu(selectW, selectH, selectNum, selections, backW, backH, back, instruH, instruction, grapInbcAndInstru);
}

