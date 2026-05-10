#include <easyx.h>
#include "../menu.h"
#include "../../Lists/UserList/userlist.h"
#include "../../Lists/BookList/booklist.h"
#include "normalmenu.h"

//普通样式
static void style_normal() {
	setfillcolor(RGB(191, 165, 243));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}

//引导信息样式
static void style_instruction() {
	setfillcolor(RGB(54, 203, 190));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}


//返回键样式
static void style_back_start() {
	setfillcolor(RGB(191, 165, 243));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}

static void style_back_hover() {
	setfillcolor(YELLOW);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
}

static void style_back_click() {
	setfillcolor(RED);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}


//选项键样式
static void style_select_start() {
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
}
static void style_select_hover() {
	setfillcolor(YELLOW);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
}
static void style_select_click() {
	setfillcolor(RED);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}




int normalMenu(int selectW, int selectH, int selectNum, char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInstru) {
	//t-->top, l-->left, h-->height, w-->width
	int t, l, h, w;	//用于绘制的

	//tw-->textwidth, th-->textheight

	int tw, th;
	//获取窗口大小
	int screenH = getheight();
	int screenW = getwidth();

	int startHOfSelect = backH + grapInbcAndInstru + instruH;
	int startHOfInfo = backH + grapInbcAndInstru;

	ExMessage msg = {0};
	int click_back_flag;
	int click_select_flag;

	int hover_back_flag;
	int hover_select_flag;

	while (true) {
		Sleep(10);
		click_back_flag = -1;
		click_select_flag = -1;

		hover_back_flag = -1;
		hover_select_flag = -1;

		msg = getmessage();

		//返回键检测
		l = 0; t = 0; w = backW; h = backH;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_back_flag = 1;
			if (msg.message == WM_LBUTTONDOWN) {
				click_back_flag = 1;
			}
		}
		//selections检测
		l = 0; t = startHOfSelect; w = selectW; h = selectH*selectNum;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_select_flag = (msg.y - startHOfSelect)/selectH;
			if (msg.message == WM_LBUTTONDOWN) {
				click_select_flag = hover_select_flag;
			}
		}


		BeginBatchDraw();

		//绘制back键
		style_back_start();
		if (hover_back_flag == 1) {
			if (click_back_flag == 1) style_back_click();
			else style_back_hover();
		}

		t = 0, l = 0; h = backH; w = backW;
		getRoundRectleBlock(back, l, t, w, h);


		//绘制引导信息
		style_instruction();	//引导信息样式

		int instruW = selectW;
		t = backH + grapInbcAndInstru;
		l = 0; w = instruW; h = instruH;

		getRectangleBlock(instruction, l, t, w, h);


		//绘制select
		for (int i = 0; i < selectNum; i++) {
			style_select_start();
			if (i == hover_select_flag) {
				if (click_select_flag >= 0) style_select_click();
				else style_select_hover();
			}
			//块的上界
			t = startHOfSelect + i*selectH;
			l = 0; w = selectW; h = selectH;

			getRectangleBlock(selections[i], l, t, w, h);

		}
		EndBatchDraw();

		//进行点击后的行为
		if (click_back_flag != -1) {
			//返回
			return 0;
		} else if (click_select_flag != -1) {
			//选项
			return click_select_flag + 1;
		}

	}

}


int detailUserInfoMenu(int selectW, int selectH, int selectNum, char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInstru, const char* userInfoTips, UserInfo* Info, int grapInSeleAndInfo) {
	
	return 0;

}



