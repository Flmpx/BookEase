#include "../../base.h"
#include "../../Lists/BookList/booklist.h"
#include "../../Lists/UserList/userlist.h"
#include "../../menu/NormalMenu/normalmenu.h"
#include "search.h"
#include <easyx.h>

#include <time.h>
#include <string.h>
#include <stdio.h>



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
			do {
				circle_in = 1;
				if (InputBox(temp, maxLen, InputBoxInfo, InputBoxTip, temp, 0, 0, false)) {
					if (temp[0] != '\0') {
						strcpy(Str, temp);
						circle_in = 0;
					} else {
						MessageBox(GetHWnd(), "输入不能为空", "提示", MB_OK);
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
				do {
					circle_in = 1;
					if (InputBox(temp, 1000, InputBoxInfo, InputBoxTip, temp, 0, 0, false)) {
						if (sscanf(temp, "%lld", &temp_id) == 1 && temp_id > Invalid_Num) {
							*id = temp_id;
							circle_in = 0;
						} else {
							MessageBox(GetHWnd(), "输入有误", "提示", MB_OK);
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

				circle_in = 1;
				do {
					circle_in = 1;
					if (InputBox(temp, 1000, "输入一个代表价格的小数", "输入价格上限", temp, 0, 0, false)) {
						if (sscanf(temp, "%lf", &price) == 1 && price > -EPS) {
							if (price < searchBook->downPrice - EPS) {
								MessageBox(GetHWnd(), "价格上限不能小于价格下限", "提示", MB_OK);
								circle_in = 1;
							} else {
								searchBook->upPrice = price;
								circle_in = 0;
							}
						} else {
							MessageBox(GetHWnd(), "价格输入有误", "提示", MB_OK);
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
					if (InputBox(temp, 1000, "输入一个代表价格的小数", "输入价格下限", temp, 0, 0, false)) {
						if (sscanf(temp, "%lf", &price) == 1 && price > -EPS) {
							if (price > searchBook->upPrice + EPS) {
								MessageBox(GetHWnd(), "价格下限不能小于价格上限", "提示", MB_OK);
								circle_in = 1;
							} else {
								searchBook->downPrice = price;
								circle_in = 0;
							}
						} else {
							MessageBox(GetHWnd(), "价格输入有误", "提示", MB_OK);
							circle_in = 1;
						}
					} else {
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

	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"开始检索", "重置所有条件", "卖者用户名", "卖者学号", "书籍id", "书名", "ISBN", "书籍作者", "价格区间", "时间区间"};
		

		/* 如果有条件, 则打印出条件, 下同理*/
		if (searchBook.seller.name[0] != '\0') {
			sprintf(selections[2], "卖者学号: %s", searchBook.seller.name);
		}

		if (searchBook.seller.id != Invalid_Num) {
			sprintf(selections[3], "卖者学号: %lld", searchBook.seller.id);

		}

		if (searchBook.id != Invalid_Num) {
			sprintf(selections[4], "书籍id: %lld", searchBook.id);
		}



		sprintf(selections[8], "价格区间: %g - %g", searchBook.downPrice, searchBook.upPrice);



		struct tm upTime = *localtime(&(searchBook.upTime));
		struct tm downTime = *localtime(&(searchBook.downTime));
		sprintf(selections[9], "时间区间: %04d年%02d月%02d日 - %04d年%02d月%02d日",	downTime.tm_year + 1900, downTime.tm_mon + 1, downTime.tm_mday,
																					upTime.tm_year + 1900, upTime.tm_mon + 1, upTime.tm_mday);
		

		int input_num = normalMenu(400, 60, 10, selections, 80, 30, "退出检索", 20, "修改筛选条件", 10);
		switch (input_num) {
			case 0:
				circle = 0;
			break;

			case 1:

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


			break;


			case 7:

			break;

			case 8:

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
