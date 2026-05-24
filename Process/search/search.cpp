#include "../../base.h"
#include "../../Lists/BookList/booklist.h"
#include "../../Lists/UserList/userlist.h"
#include "../../menu/NormalMenu/normalmenu.h"
#include "search.h"
#include <easyx.h>

#include <time.h>
#include <string.h>
#include <stdio.h>


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
		sprintf(selections[2], "价格上限:%g", searchBook->downPrice);

		

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
		char selections[][101] = {"开始检索", "卖者用户名", "卖者学号", "书名", "ISBN", "书籍作者", "价格区间", "时间区间"};
		
		struct tm upTime = *localtime(&(searchBook.upTime));
		struct tm downTime = *localtime(&(searchBook.downTime));

		sprintf(selections[7], "时间区间: %04d年%02d月%02d日 - %04d年%02d月%02d日",	downTime.tm_year + 1900, downTime.tm_mon + 1, downTime.tm_mday,
																					upTime.tm_year + 1900, upTime.tm_mon + 1, upTime.tm_mday);


		int input_num = normalMenu(400, 60, 8, selections, 80, 30, "退出检索", 20, "修改筛选条件", 30);
		switch (input_num) {
			case 0:
				circle = 0;
			break;

			case 1:


			break;

			case 2:


			break;

			case 3:


			break;

			case 4:


			break;

			case 5:


			break;

			case 6:


			break;

			case 7:


			break;
			
			case 8:
				selectTime(&searchBook);
			break;


		}

	} while (circle);
	return 1;
}
