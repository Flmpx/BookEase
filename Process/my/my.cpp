/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/
#include "my.h"
#include "../../menu/NormalMenu/normalmenu.h"
#include "../../menu/DetailMenu/detailmenu.h"
#include "../../menu/RevealMenu/revealmenu.h"
#include "../../sort/sort.h"
#include "../post/post.h"
#include "../../Process/saveandload/saveandload.h"
#include "../../function/function.h"
#include "../../Process/login/login.h"
#include <easyx.h>
/*

	此文件由于函数比较多, 故函数采用下划线命名法
	比如 my_buy_sold, my_buy_reversed 分别代表我的菜单中的我的购买的已购和预定
	全局不返回任何值
*/





void my_buy_sold_detail(BookList* mainBookList, BookList* nowBooks, Book* book) {
	int circle = 1;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"保存详细书籍信息到文件"};
		int input_num = detailBookMenu(200, 90, 1, selections, 90, 30, "返回", 20, "选择操作", 10, "已购书籍详情", book, 10);
		switch (input_num) {
			case 0: circle = 0; break;
			case 1:
				printBookInfoToFile(book, "soldbookinfo");
			break;
		}

	} while (circle);
}

void my_buy_sold(BookList* mainBookList, UserInfo* onlineUser, BookCmpCondition* bookCond) {
	int circle = 1;

	BookList nowBooks = getSimilarBookListInAllBookList(mainBookList, bookCond);
	do {
		circle = 1;
		int input_num;
		char selections[][101] = {"按价格升序", "按价格降序", "按购买时间升序", "按购买时间降序"};
		Book* book = revealMenu(&input_num, 200, 90, 4, selections, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有的已购书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_buy_sold_detail(mainBookList, &nowBooks, book);
			break;

		case 0:
			circle = 0;
			break;
		case 1:
			sortBookList(&nowBooks, sort_price_up);
			break;

		case 2:
			sortBookList(&nowBooks, sort_price_down);
			break;

		case 3:
			sortBookList(&nowBooks, sort_sold_date_up);
			break;

		case 4:
			sortBookList(&nowBooks, sort_sold_date_down);
			break;

		}

	} while (circle);

	freeBookList(&nowBooks);
}


void my_buy_reserved_detail(BookList* mainBookList, BookList* nowBooks, Book* book) {
	int circle = 1;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"取消预定", "保存详细书籍信息到文件"};
		int input_num = detailBookMenu(200, 90, 2, selections, 90, 30, "返回", 20, "选择操作", 10, "已预定的书籍详情", book, 10);
		switch (input_num) {
			case 0: circle = 0; break;
			case 1: 
				if (MessageBox(GetHWnd(), "确定要取消预定", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
					book->status = ON_SALE;
					book->reserver = NULL;
					book->reserverId = Invalid_Num;
					book->reserveTime = Invalid_Num;


					delNodeByIdInBookList(nowBooks, book->id);

					saveBookListToFile(mainBookList, "Data/bookinfo.txt");

					MessageBox(GetHWnd(), "已取消预定", "提示", MB_OK | MB_ICONINFORMATION);
					circle = 0;
				}
			break;
			case 2:
				printBookInfoToFile(book, "reservedbookinfo");
			break;

		}

	} while (circle);
}


void my_buy_reserved(BookList* mainBookList, UserInfo* onlineUser, BookCmpCondition* bookCond) {
	int circle = 1;

	BookList nowBooks = getSimilarBookListInAllBookList(mainBookList, bookCond);
	do {
		circle = 1;
		int input_num;
		char selections[][101] = {"按价格升序", "按价格降序", "按预定时间升序", "按预定时间降序"};
		Book* book = revealMenu(&input_num, 200, 90, 4, selections, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有的已预定书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_buy_reserved_detail(mainBookList, &nowBooks, book);
			break;

		case 0:
			circle = 0;
			break;
		case 1:
			sortBookList(&nowBooks, sort_price_up);
			break;

		case 2:
			sortBookList(&nowBooks, sort_price_down);
			break;

		case 3:
			sortBookList(&nowBooks, sort_reserved_date_up);
			break;

		case 4:
			sortBookList(&nowBooks, sort_reserved_date_up);
			break;


		}

	} while (circle);

	freeBookList(&nowBooks);
}





void my_buy(BookList* mainBookList, UserInfo* onlineUser) {
	int circle = 1;
	BookCmpCondition bookCond = getEmptyBookCmpCondition();
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"已预定", "已购买"};
		int input_num = normalMenu(200, 90, 2, selections, 90, 30, "返回", 20, "选择要查看的内容", 10);
		switch (input_num) {
			case 0: circle = 0; break;
			case 1:
				//写入条件
				bookCond.reserver.id = onlineUser->id;
				bookCond.status = RESERVED;
				my_buy_reserved(mainBookList, onlineUser, &bookCond);
				//删除条件
				bookCond.reserver.id = Invalid_Num;
				bookCond.status = Invalid_BookStatus;

			break;

			case 2:
				//写入条件
				bookCond.buyer.id = onlineUser->id;
				bookCond.status = SOLD;
				my_buy_sold(mainBookList, onlineUser, &bookCond);
				//删除条件
				bookCond.buyer.id = Invalid_Num;
				bookCond.status = Invalid_BookStatus;
			break;
		}
	} while (circle);
}




void my_post_onsale_detail(BookList* mainBookList, BookList* nowBooks, Book* book, UserInfo* onlineUser) {
	int circle = 1;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"下架书籍", "保存详细书籍信息到文件"};
		int input_num = detailBookMenu(200, 90, 2, selections, 90, 30, "返回", 20, "选择操作", 10, "在售书籍详情", book, 10);
		switch (input_num) {
		case 0: circle = 0; break;
		case 1: 
			if (MessageBox(GetHWnd(), "确定要下架书籍吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES && authenUserInfo(onlineUser)) {
				book->status = REMOVED;
				book->publishTime = Invalid_Num;




				delNodeByIdInBookList(nowBooks, book->id);

				saveBookListToFile(mainBookList, "Data/bookinfo.txt");

				MessageBox(GetHWnd(), "已下架书籍\n可以在下架页找到当前书籍", "提示", MB_OK | MB_ICONINFORMATION);
				circle = 0;
			}
			break;

		case 2:
			printBookInfoToFile(book, "onsalebookinfo");
		break;
		}

	} while (circle);
}


void my_post_onsale(BookList* mainBookList, UserInfo* onlineUser, BookCmpCondition* bookCond) {
	int circle = 1;

	BookList nowBooks = getSimilarBookListInAllBookList(mainBookList, bookCond);
	do {
		circle = 1;
		int input_num;
		char selections[][101] = {"按价格升序", "按价格降序", "按发布时间升序", "按发布时间降序"};
		Book* book = revealMenu(&input_num, 200, 90, 4, selections, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有在售的书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_post_onsale_detail(mainBookList, &nowBooks, book, onlineUser);
			break;

		case 0:
			circle = 0;
			break;

		case 1:
			sortBookList(&nowBooks, sort_price_up);
			break;

		case 2:
			sortBookList(&nowBooks, sort_price_down);
			break;

		case 3:
			sortBookList(&nowBooks, sort_publish_date_up);
			break;

		case 4:
			sortBookList(&nowBooks, sort_publish_date_down);
			break;

		}

	} while (circle);

	freeBookList(&nowBooks);
}


void my_post_reserved_detail(BookList* mainBookList, BookList* nowBooks, Book* book) {
	int circle = 1;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"转为已售", "保存详细书籍信息到文件"};
		int input_num = detailBookMenu(200, 90, 2, selections, 90, 30, "返回", 20, "选择操作", 10, "已被预定书籍详情", book, 10);
		switch (input_num) {
			case 0: circle = 0; break;
			case 1:
				if (MessageBox(GetHWnd(), "确定预定方已收到你那本陪伴你诸多岁月的书了吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
					book->status = SOLD;

					book->buyer = book->reserver;
					book->buyerId = book->reserverId;
					book->buyTime = time(NULL);



					delNodeByIdInBookList(nowBooks, book->id);

					saveBookListToFile(mainBookList, "Data/bookinfo.txt");

					MessageBox(GetHWnd(), "书籍已找到新的落脚点", "提示", MB_OK | MB_ICONINFORMATION);
					circle = 0;
				}


			break;

			case 2:
				printBookInfoToFile(book, "reservedbookinfo");
			break;
		}

	} while (circle);
}


void my_post_reserved(BookList* mainBookList, UserInfo* onlineUser, BookCmpCondition* bookCond) {
	int circle = 1;

	BookList nowBooks = getSimilarBookListInAllBookList(mainBookList, bookCond);
	do {
		circle = 1;
		int input_num;
		char selections[][101] = {"按价格升序", "按价格降序", "按已预定时间升序", "按已预定时间降序"};
		Book* book = revealMenu(&input_num, 200, 90, 4, selections, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有已被预定的书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_post_reserved_detail(mainBookList, &nowBooks, book);
			break;

		case 0:
			circle = 0;
			break;
		case 1:
			sortBookList(&nowBooks, sort_price_up);
			break;

		case 2:
			sortBookList(&nowBooks, sort_price_down);
			break;

		case 3:
			sortBookList(&nowBooks, sort_reserved_date_up);
			break;

		case 4:
			sortBookList(&nowBooks, sort_reserved_date_up);
			break;


		}

	} while (circle);

	freeBookList(&nowBooks);
}




void my_post_sold_detail(BookList* mainBookList, BookList* nowBooks, Book* book) {
	int circle = 1;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"保存详细书籍信息到文件"};
		int input_num = detailBookMenu(200, 90, 1, selections, 90, 30, "返回", 20, "选择操作", 10, "已被购买的书籍详情", book, 10);
		switch (input_num) {
			case 0: circle = 0; break;
			case 1:
				printBookInfoToFile(book, "soldbookinfo");
			break;
		}

	} while (circle);
}





void my_post_sold(BookList* mainBookList, UserInfo* onlineUser, BookCmpCondition* bookCond) {
	int circle = 1;

	BookList nowBooks = getSimilarBookListInAllBookList(mainBookList, bookCond);
	do {
		circle = 1;
		int input_num;
		char selections[][101] = {"按价格升序", "按价格降序", "按已购时间升序", "按已购时间降序"};
		Book* book = revealMenu(&input_num, 200, 90, 4, selections, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有的已被购买的书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_post_sold_detail(mainBookList, &nowBooks, book);
			break;

		case 0:
			circle = 0;
			break;

		case 1:
			sortBookList(&nowBooks, sort_price_up);
			break;

		case 2:
			sortBookList(&nowBooks, sort_price_down);
			break;

		case 3:
			sortBookList(&nowBooks, sort_sold_date_up);
			break;

		case 4:
			sortBookList(&nowBooks, sort_sold_date_up);
			break;

		}

	} while (circle);

	freeBookList(&nowBooks);
}

void my_post_removed_detail(BookList* mainBookList, BookList* nowBooks, Book* book) {
	int circle = 1;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"重新上架", "修改书籍信息", "保存详细书籍信息到文件"};
		int input_num = detailBookMenu(200, 90, 3, selections, 90, 30, "返回", 20, "选择操作", 10, "已下架书籍的详情", book, 10);
		switch (input_num) {
		case 0: circle = 0; break;
		case 1:
			if (MessageBox(GetHWnd(), "确定要要重新上架吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				book->status = ON_SALE;

				
				book->publishTime = time(NULL);



				delNodeByIdInBookList(nowBooks, book->id);

				saveBookListToFile(mainBookList, "Data/bookinfo.txt");

				MessageBox(GetHWnd(), "重新上架成功", "提示", MB_OK | MB_ICONINFORMATION);
				circle = 0;
			}
		break;

		case 2:
			if (changeBookInfo(book)) {
				saveBookListToFile(mainBookList, "Data/bookinfo.txt");
				MessageBox(GetHWnd(), "修改保存成功", "提示", MB_OK | MB_ICONINFORMATION);
			}
			
			break;
		case 3:
			printBookInfoToFile(book, "removedbookinfo");
		break;
		}

	} while (circle);
}

void my_post_removed(BookList* mainBookList, UserInfo* onlineUser, BookCmpCondition* bookCond) {
	int circle = 1;

	BookList nowBooks = getSimilarBookListInAllBookList(mainBookList, bookCond);
	do {
		circle = 1;
		int input_num;
		char selections[][101] = {"按价格升序", "按价格降序"};
		Book* book = revealMenu(&input_num, 200, 90, 2, selections, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有的已下架的书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_post_removed_detail(mainBookList, &nowBooks, book);
			break;

		case 0:
			circle = 0;
			break;
		case 1:
			sortBookList(&nowBooks, sort_price_up);
			break;

		case 2:
			sortBookList(&nowBooks, sort_price_down);
			break;

		}

	} while (circle);

	freeBookList(&nowBooks);
}

void my_post(BookList* mainBookList, UserInfo* onlineUser) {
	int circle = 1;
	BookCmpCondition bookCond = getEmptyBookCmpCondition();
	bookCond.seller.id = onlineUser->id;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"在售卖", "已被预定", "已被购买", "已下架"};
		int input_num = normalMenu(200, 90, 4, selections, 90, 30, "返回", 20, "选择要查看的内容", 10);
		switch (input_num) {

		case 0: circle = 0; break;
		case 1:
			//写入条件
			bookCond.status = ON_SALE;
			my_post_onsale(mainBookList, onlineUser, &bookCond);
			//删除条件
			bookCond.status = Invalid_BookStatus;

			break;

		case 2:
			//写入条件
			bookCond.status = RESERVED;
			my_post_reserved(mainBookList, onlineUser, &bookCond);
			//删除条件
			bookCond.status = Invalid_BookStatus;
			break;
		case 3:
			
			//写入条件
			bookCond.status = SOLD;
			my_post_sold(mainBookList, onlineUser, &bookCond);
			//删除条件
			bookCond.status = Invalid_BookStatus;

			break;

		case 4:

			//写入条件
			bookCond.status = REMOVED;
			
			my_post_removed(mainBookList, onlineUser, &bookCond);

			//删除条件
			bookCond.status = Invalid_BookStatus;
			break;
		}
	} while (circle);
}









void my_info(UserList* mainUserInfo, UserInfo* onlineUser) {
	int circle = 1;
	int circle_in = 1;
	char temp[1001] = "";
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"修改我的信息", "修改密码"};
		int input_num = detailUserInfoMenu(200, 90, 2, selections, 90, 30, "返回", 20, "选择操作", 10, "你的信息", onlineUser, 10);
		switch (input_num) {
			case 0: circle = 0; break;
			case 1: 
				if (changeUserInfo(onlineUser)) {
					saveUserListToFile(mainUserInfo, "Data/userinfo.txt");
					MessageBox(GetHWnd(), "修改保存成功", "提示", MB_OK | MB_ICONINFORMATION);
				}
			break;

			case 2:
				if (changeUserKey(onlineUser)) {
					saveUserListToFile(mainUserInfo, "Data/userinfo.txt");
					MessageBox(GetHWnd(), "密码修改成功", "提示", MB_OK | MB_ICONINFORMATION);

				}
			break;
		}
		

	} while (circle);
}




void my(BookList* mainBookList, UserList* mainUserInfo, UserInfo* onlineUser) {
	int circle = 1;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"我的信息", "我的发布", "我的购买"};
		int input_num = normalMenu(200, 90, 3, selections, 90, 30, "返回", 20, "选择查看的内容", 10);
		switch (input_num) {
			case 0:
				circle = 0;
			break;
				
			case 1:
				my_info(mainUserInfo, onlineUser);
			break;
			
			case 2:
				my_post(mainBookList, onlineUser);
			break;
			
			case 3:
				my_buy(mainBookList, onlineUser);
			break;


		}

	} while (circle);
}





