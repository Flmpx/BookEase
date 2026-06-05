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
#include "Process/search/search.h"
#include "Process/post/post.h"
#include "Process/my/my.h"
#include "Process/about/about.h"

ll MaxBookId = 0;


static void mainpage(UserList* mainUserList, BookList* mainBookList, UserInfo* onlineUser) {
	int circle;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"买书", "卖书", "我的", "关于"};	
		//调用普通菜单
		int input_num = normalMenu(200, 90, 4, selections, 80, 30, "退出登录", 20, "选择操作", 30);
		switch (input_num) {
		case 0:	//退出登录
			if (MessageBox(GetHWnd(), "确认退出吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				//确认退出登录
				circle = 0;
			}

			break;
		case 1:
			// 买书(直接进入检索功能)
			search(mainUserList, mainBookList, onlineUser);
			break;
		case 2:
			// 卖书
			post(mainBookList, onlineUser);

			break;
		case 3:
			// 我的
			my(mainBookList, mainUserList, onlineUser);
			break;
		case 4:
			// 关于
			about(mainUserList, mainBookList, onlineUser);
			break;
		}

	} while (circle);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	/*创建窗口*/
	initgraph(1280, 720);
	setbkcolor(RGB(253, 254, 249));
	cleardevice();
	settextstyle(16, 0, "宋体");

	UserList mainUserList;

	mainUserList = loadUserListFromFile("Data/userinfo.txt");

	BookList mainBookList;
	mainBookList = loadBookListFromFile("Data/bookinfo.txt", &mainUserList);


	UserInfo* onlineUser = NULL;




	int circle;
	do {
		circle = 1;
		cleardevice();
		int input_num = loginMenu(200, 90, 400);	//调用登录菜单
		switch (input_num) {
		case 0:
			registerFunc(&mainUserList);	//注册功能函数
			break;

		case 1:
			onlineUser = loginFunc(&mainUserList);	//登录功能函数
			if (onlineUser) {
				//登录成功会返回登录用户指针
				mainpage(&mainUserList, &mainBookList, onlineUser);
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


