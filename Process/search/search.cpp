#include "../../base.h"
#include "../../Lists/BookList/booklist.h"
#include "../../Lists/UserList/userlist.h"
#include "../../menu/NormalMenu/normalmenu.h"
#include "../../function/function.h"
#include "../../menu/RevealMenu/revealmenu.h"
#include "../../menu/DetailMenu/detailmenu.h"
#include "../../Process/saveandload/saveandload.h"
#include "search.h"
#include <easyx.h>

#include <time.h>
#include <string.h>
#include <stdio.h>



int buy(BookList* mainBookList, BookList* nowBooks, Book* book, UserInfo* onlineUser) {
	int circle = 1;
	do {
		cleardevice();
		circle = 1;
		char selections[][101] = {"预定"};
		//int input_num = normalMenu(200, 90, 1, selections, 90, 30, "退出查看", 20, "选择是否预定", 10);
		int input_num = detailBookMenu(200, 90, 1, selections, 90, 30, "退出查看", 20, "选择是否预定", 10, "书籍详情", book, 10);
		switch (input_num) {
			case 0: circle = 0; break;
			case 1:
				if (book->sellerId != onlineUser->id) {
					if (MessageBox(GetHWnd(), "确定要预定吗?", "提示", MB_YESNO) == IDYES) {
						book->reserverId = onlineUser->id;
						book->reserveTime = time(NULL);
						book->reserver = onlineUser;
						book->status = RESERVED;
						/*由于检索页只会展示在售书籍, 故要将已订书籍从链表中删除*/

						delNodeByIdInBookList(nowBooks, book->id);

						saveBookListToFile(mainBookList, "bookinfo.txt");
					
						MessageBox(GetHWnd(), "预定成功!\n你可在我的页查看已订详情\n尝试与卖者联系\n", "提示", MB_OK);

						circle = 0;

					}
				} else {
					/*防止自己预定自己的书籍*/
					MessageBox(GetHWnd(), "不可以自己预定自己的书哦", "提示", MB_OK);
					circle = 1;
				}

			break;
		}
		
	} while (circle);
	return 1;
}



int revealSearchDetail(UserList* mainUserList, BookList* mainBookList, UserInfo* onlineUser, BookCmpCondition* bookCmpcond) {
	int circle = 1;

	BookList nowBooks = getSimilarBookListInAllBookList(mainBookList, bookCmpcond);
	do {
		circle = 1;
		int input_num;
		Book* book = revealMenu(&input_num, 200, 90, 0, NULL, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
			case -1:
				buy(mainBookList, &nowBooks, book, onlineUser);
			break;

			case 0:
				circle = 0;
			break;


		}

	} while (circle);

	freeBookList(&nowBooks);
	return 1;
}





int selectStr(char* Str, const char* selectionInfo, const char* InputBoxInfo, const char* InputBoxTip, int maxLen) {
	int circle = 1;
	int circle_in = 1;
	char temp[1001] = "";
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"重置筛选信息", "输入的信息"};

		strcpy(selections[1], selectionInfo);

		/*如果不是非法数字, 那么就打印详细信息*/
		if (Str[0] != '\0') {
			sprintf(selections[1], "%s: %s", selectionInfo, Str);
		}

		int input_num = normalMenu(200, 90, 2, selections, 100, 30, "保存并退出", 20, "选择操作", 30);

		switch (input_num) {
		case 0:
			circle = 0;
			break;


		case 1:
			Str[0] = '\0';
			break;

		case 2:
			InputStr(Str, InputBoxInfo, InputBoxInfo, maxLen);

			break;

		}


	} while (circle);
	return 1;
}

int selectId(ll* id, const char* selectionInfo, const char* InputBoxInfo, const char* InputBoxTip) {
	int circle = 1;
	int circle_in = 1;
	char temp[1001] = "";
	ll temp_id;

	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"重置筛选信息", "输入的信息"};

		strcpy(selections[1], selectionInfo);

		/*如果不是非法数字, 那么就打印详细信息*/
		if (*id != Invalid_Num) {
			sprintf(selections[1], "%s: %lld", selectionInfo, *id);
		}

		int input_num = normalMenu(200, 90, 2, selections, 100, 30, "保存并退出", 20, "选择操作", 30);

		switch (input_num) {
			case 0:
				circle = 0;
			break;


			case 1:
				*id = Invalid_Num;
			break;

			case 2:
				InputInter(id, InputBoxInfo, InputBoxTip);
			break;


		}


	} while (circle);

	

	return 1;
}

int selectPrice(BookCmpCondition* searchBook) {
	int circle = 1;
	int circle_in = 1;
	char temp[1001] = "";

	do {
		circle = 1;
		cleardevice();

		char selections[][101] = {"重置筛选信息", "价格上限", "价格下限"};

		/*
		
			显示价格区间
		*/
		sprintf(selections[1], "价格上限:%g", searchBook->upPrice);
		sprintf(selections[2], "价格下限:%g", searchBook->downPrice);
		double price;
		int input_num = normalMenu(200, 90, 3, selections, 100, 30, "保存并退出", 20, "选择操作", 30);

		switch (input_num) {
			case 0:
				circle = 0;
			break;

				

			case 1:
				searchBook->upPrice = searchBook->downPrice = Invalid_FloatNum;
			
			break;
			

			case 2:
				
				do {
					circle_in = 0;
					price = searchBook->upPrice;

					InputFloat(&price, "输入一个代表价格的小数", "输入价格上限");

					if (price < searchBook->downPrice - EPS) {
						MessageBox(GetHWnd(), "价格上限不能小于价格下限", "提示", MB_OK);
						circle_in = 1;
					} else {
						searchBook->upPrice = price;
						circle_in = 0;
					}
				} while (circle_in);

			break;
			
			
			case 3:
				do {
					circle_in = 0;
					price = searchBook->downPrice;

					InputFloat(&price, "输入一个代表价格的小数", "输入价格下限");

					if (price > searchBook->upPrice + EPS) {
						MessageBox(GetHWnd(), "价格下限不能小于价格上限", "提示", MB_OK);
						circle_in = 1;
					} else {
						searchBook->downPrice = price;
						circle_in = 0;
					}
				} while (circle_in);
			break;
		}
		

	} while (circle);

	return 0;
}

int selectTime(BookCmpCondition* searchBook) {
	int circle = 1;
	int circle_in = 1;
	char temp[1001] = "";

	do {
		struct tm upTime = *localtime(&(searchBook->upTime));
		struct tm downTime = *localtime(&(searchBook->downTime));
		circle = 1;
		cleardevice();
		char selections[][101] = {"重置筛选信息", "时间上限", "时间下限"};

		/*  
			显示时间区间
		*/
		sprintf(selections[1], "时间上限:%04d年%02d月%02d日", upTime.tm_year + 1900, upTime.tm_mon + 1, upTime.tm_mday);
		sprintf(selections[2], "时间下限:%04d年%02d月%02d日", downTime.tm_year + 1900, downTime.tm_mon + 1, downTime.tm_mday);
		
		time_t time;
		
		int input_num = normalMenu(200, 90, 3, selections, 100, 30, "保存并退出", 20, "选择操作", 30);
		switch (input_num) {
			case 0:
				circle = 0;
			break;

			case 1:
				searchBook->upTime = searchBook->downTime = Invalid_Num;
				circle = 1;
			break;

			case 2:
				circle_in = 1;
				do {
					circle_in = 1;
					if (InputBox(temp, 1000, "按照\"年 月 日\"的格式输入\n例如: 2026 5 25", "输入发布时间上限", temp, 0, 0, false)) {
						

						if (sscanf(temp, "%d %d %d", &(upTime.tm_year), &(upTime.tm_mon), &(upTime.tm_mday)) == 3 && upTime.tm_year < 3000 && upTime.tm_year >= 1970) {
							upTime.tm_year -= 1900;
							upTime.tm_mon -= 1;
							time_t time = mktime(&upTime);
							if (time < searchBook->downTime) {
								MessageBox(GetHWnd(), "时间上限不能小于时间下限", "提示", MB_OK);
								circle_in = 1;
							} else {
								searchBook->upTime = time;
								circle_in = 0;
							}
						} else {
							MessageBox(GetHWnd(), "时间输入有误", "提示", MB_OK);
							circle_in = 1;
						}
					} else {
						circle_in = 0;
					}

				} while (circle_in);


			break;


			case 3:
				circle_in = 1;
				do {
					circle_in = 1;
					if (InputBox(temp, 1000, "按照\"年 月 日\"的格式输入\n例如: 2026 5 20", "输入发布时间下限", temp, 0, 0, false)) {


						if (sscanf(temp, "%d %d %d", &(downTime.tm_year), &(downTime.tm_mon), &(downTime.tm_mday)) == 3 && downTime.tm_year < 3000 && downTime.tm_year >= 1970) {
							downTime.tm_year -= 1900;
							downTime.tm_mon -= 1;
							time_t time = mktime(&downTime);
							if (time > searchBook->upTime) {
								MessageBox(GetHWnd(), "时间下限不能大于时间上限", "提示", MB_OK);
								circle_in = 1;
							} else {
								searchBook->downTime = time;
								circle_in = 0;
							}
						} else {
							MessageBox(GetHWnd(), "时间输入有误", "提示", MB_OK);
							circle_in = 1;
						}
					} else {
						circle_in = 0;
					}

				} while (circle_in);

			break;
		}

	} while (circle);
	return 1;
}


int search(UserList* mainUserList, BookList* mainBookList, UserInfo* onlineUser) {
	int circle = 1;
	BookCmpCondition searchBook = getEmptyBookCmpCondition();
	searchBook.status = ON_SALE;	//默认检索在售书籍

	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"开始检索", "重置所有条件", "卖者用户名", "卖者学号", "书籍id", "书名", "ISBN", "书籍作者", "价格区间", "时间区间"};
		

		/* 如果有条件, 则打印出条件, 下同理*/
		if (searchBook.seller.name[0] != '\0') {
			sprintf(selections[2], "卖者用户名: %s", searchBook.seller.name);
		}

		if (searchBook.seller.id != Invalid_Num) {
			sprintf(selections[3], "卖者学号: %lld", searchBook.seller.id);

		}

		if (searchBook.id != Invalid_Num) {
			sprintf(selections[4], "书籍id: %lld", searchBook.id);
		}

		if (searchBook.title[0] != '\0') {
			sprintf(selections[5], "书名: %s", searchBook.title);
		}

		if (searchBook.isbn[0] != '\0') {
			sprintf(selections[6], "ISBN: %s", searchBook.isbn);
		}


		if (searchBook.author[0] != '\0') {
			sprintf(selections[7], "书籍作者: %s", searchBook.author);
		}

		sprintf(selections[8], "价格区间: %g - %g", searchBook.downPrice, searchBook.upPrice);



		struct tm upTime = *localtime(&(searchBook.upTime));
		struct tm downTime = *localtime(&(searchBook.downTime));
		sprintf(selections[9], "时间区间: %04d年%02d月%02d日 - %04d年%02d月%02d日",	downTime.tm_year + 1900, downTime.tm_mon + 1, downTime.tm_mday,
																					upTime.tm_year + 1900, upTime.tm_mon + 1, upTime.tm_mday);
		

		int input_num = normalMenu(400, 60, 10, selections, 80, 30, "退出检索", 20, "修改筛选条件", 10);
		switch (input_num) {
			case 0:
				if (MessageBox(GetHWnd(), "退出检索将会丢失所写条件, 确认退出吗?", "提示", MB_YESNO) == IDYES) {
					circle = 0;
				}
			break;
				
			case 1:
				revealSearchDetail(mainUserList, mainBookList, onlineUser, &searchBook);
			break;
				
			case 2:

				if (MessageBox(GetHWnd(), "确定要全部重置吗?", "提示", MB_YESNO) == IDYES) {
					searchBook = getEmptyBookCmpCondition();
				}


			break;



			case 3:
				selectStr(searchBook.seller.name, "卖家用户名", "输入卖家用户名", "输入", USERNAME_MAX_LEN - 3);

			break;

			case 4:
				selectId(&(searchBook.seller.id), "卖家学号", "输入卖家学号", "输入");

			break;

			case 5:

				selectId(&(searchBook.id), "书籍id", "输入书籍id", "输入");

			break;

			case 6:

				selectStr(searchBook.title, "书名", "输入书名, 可以只输入一部分", "输入", BOOK_TITLE_MAX_LEN - 3);
			break;


			case 7:
				selectStr(searchBook.isbn, "ISBN", "输入书籍的ISBN", "输入", ISBN_MAX_LEN - 3);
			break;

			case 8:
				selectStr(searchBook.author, "书籍作者", "输入书籍的作者", "输入", BOOK_AUTHOR_MAX_LEN - 3);
			break;

			/* 选择价格区间*/
			case 9:

				selectPrice(&searchBook); 

			break;

			/* 选择发布时间区间*/
			case 10:
				selectTime(&searchBook);
			break;


		}

	} while (circle);
	return 1;
}
