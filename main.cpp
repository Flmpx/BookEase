#include <easyx.h>
#include <stdio.h>
#include "base.h"
#include "menu/LoginMenu/loginmenu.h"
#include "Lists/BookList/booklist.h"
#include "Lists/UserList/userlist.h"
#include "menu/RevealMenu/revealmenu.h"
#include "menu/NormalMenu/normalmenu.h"
#include "menu/DetailMenu/detailmenu.h"
#include "Process/saveandload/saveandload.h"
#include "Process/login/login.h"

int main() {

	/*创建窗口*/
	initgraph(1250, 640);
	setbkcolor(RGB(34, 166, 242));
	cleardevice();
	settextstyle(20, 0, "宋体");

	UserList mainUserList;

	mainUserList = loadUserListFromFile("Data/userinfo.txt");

	BookList mainBookList;
	mainBookList = loadBookListFromFile("Data/bookinfo.txt", &mainUserList);


	UserInfo* onlineUser = NULL;

	

	int circle;
	do {
		circle = 1;
		cleardevice();
		int input_num = loginMenu(200, 90, 400);
		switch (input_num) {
			case 0:
				registerFunc(&mainUserList);
			break;

			case 1:
				onlineUser = loginFunc(&mainUserList);
				if (onlineUser) {
					circle = 0;
				}
			break;
		}

	} while (circle);
	

	




	saveBookListToFile(&mainBookList, "Data/bookinfo.txt");
	saveUserListToFile(&mainUserList, "Data/userinfo.txt");


	deepFreeBookList(&mainBookList);
	deepFreeUserList(&mainUserList);


	return 0;
}
