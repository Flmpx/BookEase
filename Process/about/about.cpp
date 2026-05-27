#include "../../base.h"
#include "../../menu/DetailMenu/detailmenu.h"
#include "../../menu/NormalMenu/normalmenu.h"
#include "../../Lists/BookList/booklist.h"
#include "../../Lists/UserList/userlist.h"
#include <easyx.h>


void about_statistics(UserList* mainUserList, BookList* mainBookList, UserInfo* onlineUser) {
	int circle = 1;
	do {
		 circle = 1;
		 cleardevice();
		 char selections[][101] = {"后期添加"};

		 int input_num = detailStatisticsMenu(200, 90, 0, selections, 90, 30, "返回", 20, "选择操作", 10, "统计信息", mainBookList, mainUserList, 10);

		 switch (input_num) {
			 case 0: circle = 0; break;

		 }

	} while (circle);
}


void about(UserList* mainUserList, BookList* mainBookList, UserInfo* onlineUser) {
	int circle = 1;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"统计信息"};

		int input_num = normalMenu(200, 90, 1, selections, 90, 30, "返回", 20, "选择内容", 10);
		switch (input_num) {
			case 0: circle = 0; break;

			case 1: 
				about_statistics(mainUserList, mainBookList, onlineUser);

			break;
		}

	} while (circle);
}
