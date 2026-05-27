#include "my.h"
#include "../../menu/NormalMenu/normalmenu.h"
#include "../../menu/DetailMenu/detailmenu.h"
#include "../../menu/RevealMenu/revealmenu.h"
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
		char selections[][101] = {"没有"};
		int input_num = detailBookMenu(200, 90, 0, selections, 90, 30, "返回", 20, "选择操作", 10, "预定书籍详情", book, 10);
		switch (input_num) {
			case 0: circle = 0; break;

		}

	} while (circle);
}

void my_buy_sold(BookList* mainBookList, UserInfo* onlineUser, BookCmpCondition* bookCond) {
	int circle = 1;

	BookList nowBooks = getSimilarBookListInAllBookList(mainBookList, bookCond);
	do {
		circle = 1;
		int input_num;
		Book* book = revealMenu(&input_num, 200, 90, 0, NULL, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_buy_sold_detail(mainBookList, &nowBooks, book);
			break;

		case 0:
			circle = 0;
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
		char selections[][101] = {"取消预定"};
		int input_num = detailBookMenu(200, 90, 1, selections, 90, 30, "返回", 20, "选择操作", 10, "预定书籍详情", book, 10);
		switch (input_num) {
			case 0: circle = 0; break;
			case 1: 
				if (MessageBox(GetHWnd(), "确定要取消预定", "提示", MB_YESNO) == IDYES) {
					book->status = ON_SALE;
					book->reserver = NULL;
					book->reserverId = Invalid_Num;
					book->reserveTime = Invalid_Num;
					delNodeByIdInBookList(nowBooks, book->id);

					saveBookListToFile(mainBookList, "bookinfo.txt");

					MessageBox(GetHWnd(), "已取消预定", "提示", MB_OK);
					circle = 0;
				}
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
		Book* book = revealMenu(&input_num, 200, 90, 0, NULL, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_buy_reserved_detail(mainBookList, &nowBooks, book);
			break;

		case 0:
			circle = 0;
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
		char selections[][101] = {"下架书籍"};
		int input_num = detailBookMenu(200, 90, 1, selections, 90, 30, "返回", 20, "选择操作", 10, "在售书籍详情", book, 10);
		switch (input_num) {
		case 0: circle = 0; break;
		case 1: 
			if (MessageBox(GetHWnd(), "确定要下架书籍吗?", "提示", MB_YESNO) == IDYES && authenUserInfo(onlineUser)) {
				book->status = REMOVED;
				book->publishTime = Invalid_Num;

				delNodeByIdInBookList(nowBooks, book->id);

				saveBookListToFile(mainBookList, "bookinfo.txt");

				MessageBox(GetHWnd(), "已下架书籍\n可以在下架页找到当前书籍", "提示", MB_OK);
				circle = 0;
			}
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
		Book* book = revealMenu(&input_num, 200, 90, 0, NULL, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_post_onsale_detail(mainBookList, &nowBooks, book, onlineUser);
			break;

		case 0:
			circle = 0;
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
		char selections[][101] = {"转为已售"};
		int input_num = detailBookMenu(200, 90, 1, selections, 90, 30, "返回", 20, "选择操作", 10, "已被预定书籍详情", book, 10);
		switch (input_num) {
			case 0: circle = 0; break;
			case 1:
				if (MessageBox(GetHWnd(), "确定预定方已收到你那本陪伴你诸多岁月的书了吗?", "提示", MB_YESNO) == IDYES) {
					book->status = SOLD;

					book->buyer = book->reserver;
					book->buyerId = book->reserverId;
					book->buyTime = time(NULL);

					delNodeByIdInBookList(nowBooks, book->id);

					saveBookListToFile(mainBookList, "bookinfo.txt");

					MessageBox(GetHWnd(), "书籍已找到新的落脚点", "提示", MB_OK);
					circle = 0;
				}


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
		Book* book = revealMenu(&input_num, 200, 90, 0, NULL, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_post_reserved_detail(mainBookList, &nowBooks, book);
			break;

		case 0:
			circle = 0;
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
		char selections[][101] = {"仅可查看"};
		int input_num = detailBookMenu(200, 90, 0, selections, 90, 30, "返回", 20, "不可操作", 10, "已购书籍详情", book, 10);
		switch (input_num) {
			case 0: circle = 0; break;
		}

	} while (circle);
}

void my_post_sold(BookList* mainBookList, UserInfo* onlineUser, BookCmpCondition* bookCond) {
	int circle = 1;

	BookList nowBooks = getSimilarBookListInAllBookList(mainBookList, bookCond);
	do {
		circle = 1;
		int input_num;
		Book* book = revealMenu(&input_num, 200, 90, 0, NULL, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_post_sold_detail(mainBookList, &nowBooks, book);
			break;

		case 0:
			circle = 0;
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
		char selections[][101] = {"重新上架", "修改书籍信息"};
		int input_num = detailBookMenu(200, 90, 2, selections, 90, 30, "返回", 20, "选择操作", 10, "已下架书籍详情", book, 10);
		switch (input_num) {
		case 0: circle = 0; break;
		case 1:
			if (MessageBox(GetHWnd(), "确定要要重新上架吗?", "提示", MB_YESNO) == IDYES) {
				book->status = ON_SALE;

				
				book->publishTime = time(NULL);

				delNodeByIdInBookList(nowBooks, book->id);

				saveBookListToFile(mainBookList, "bookinfo.txt");

				MessageBox(GetHWnd(), "重新上架成功", "提示", MB_OK);
				circle = 0;
			}
		break;
		case 2:
			changeBookInfo(mainBookList, book);
			
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
		Book* book = revealMenu(&input_num, 200, 90, 0, NULL, 90, 30, "返回", 20, "选择排序方式", 10, 40, 40, "当前找到的所有书籍", &nowBooks, 10, 3, 2);
		switch (input_num) {
		case -1:
			my_post_removed_detail(mainBookList, &nowBooks, book);
			break;

		case 0:
			circle = 0;
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





void my_info_changekey(UserList* mainUserInfo, UserInfo* onlineUser) {
	if (!authenUserInfo(onlineUser)) {
		return;
	}
	char temp_key[1001] = "";
	if (InputStr(temp_key, "输入新密码", "提示", 1000)) {
		generateSalt(onlineUser->salt, 12);
		generateHashKey(temp_key, onlineUser->salt, onlineUser->hashKey);
		saveUserListToFile(mainUserInfo, "userinfo.txt");
		MessageBox(GetHWnd(), "密码修改成功", "提示", MB_OK);

	}
}

void my_info_changeinfo(UserList* mainUserInfo, UserInfo* onlineUser) {
	UserInfo* temp_user = (UserInfo*)malloc(sizeof(UserInfo));
	memcpy(temp_user, onlineUser, sizeof(UserInfo));

	int circle = 1;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"保存修改", "修改用户名", "修改电话", "修改QQ号", "修改微信号"};
		int input_num = detailUserInfoMenu(200, 90, 4, selections, 90, 30, "保存并退出", 20, "选择修改的信息", 10, "你的信息", onlineUser, 10);
		switch (input_num) {
		case 0:
			if (MessageBox(GetHWnd(), "确认退出修改吗? 修改不会保存", "提示", MB_YESNO) == IDYES) {
				circle = 0;
			}
			break;

		case 1:
			memcpy(onlineUser, temp_user, sizeof(UserInfo));
			saveUserListToFile(mainUserInfo, "userinfo.txt");
			MessageBox(GetHWnd(), "修改保存成功", "提示", MB_OK);
			circle = 0;
				
			break;
			case 2:
				InputStr(temp_user->name, "输入用户名\n\"一个好的名字能让别人更快的记住你\"", "输入", USERNAME_MAX_LEN - 3);

			break;

			case 3:
				InputInter(&(temp_user->tel), "输入电话", "输入");
			break;
			
			case 4:
				InputInter(&(temp_user->QQ), "输入QQ号", "输入");
			break;

			case 5:
				InputStr(temp_user->WeChat, "输入微信号", "输入", WECHAR_MAX_LEN - 1);

			break;
		}

	} while(circle);
	free(temp_user);
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
				my_info_changeinfo(mainUserInfo, onlineUser);
				
			break;

			case 2:
				my_info_changekey(mainUserInfo, onlineUser);
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





