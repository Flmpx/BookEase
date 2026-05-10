#include "../../base.h"
#include <easyx.h>
#include "../menu.h"

static void style_button_start() {
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
}
static void style_button_hover() {
	setfillcolor(YELLOW);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
}
static void style_button_click() {
	setfillcolor(RED);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}


int loginMenu(int blockWidth, int blockHeight, int marginOfBlock) {
	int screenW = getwidth();	
	int screenH = getheight();

	int l, t, w, h;

	//reg-->register-->注册
	//log-->login-->登录

	const char* regStr = "注册";
	const char* logStr = "登录";

	int flagReturn = -1;	//0代表返回注册, 1代表返回登录

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	ExMessage msg = {0};
	while (true) {
		Sleep(10);

		bool hover_reg = false, hover_log = false;

		//peekmessage(&msg, EX_MOUSE);
		msg = getmessage();

		//检测注册
		w = blockWidth; h = blockHeight;
		l = screenW/2 - marginOfBlock/2 - w;
		t = screenH/3*2 - h/2;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_reg = true;
			if (msg.message == WM_LBUTTONDOWN) {
				//点击了注册
				flagReturn = 0;
			}
		}

		//检测登录键
		w = blockWidth; h = blockHeight;
		l = screenW/2 + marginOfBlock/2;
		t = screenH/3*2 - h/2;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_log = true;
			if (msg.message == WM_LBUTTONDOWN) {
				//点击了登录
				flagReturn = 1;
			}
		}
		BeginBatchDraw();

		//绘制Reg

		style_button_start();
		if (hover_reg) {
			if (flagReturn >= 0) style_button_click();
			else style_button_hover();
		}
		w = blockWidth; h = blockHeight;
		l = screenW/2 - marginOfBlock/2 - w;
		t = screenH/3*2 - h/2;

		getRoundRectleBlock(regStr, l, t, w, h);



		//绘制Log
		style_button_start();
		if (hover_log) {
			if (flagReturn >= 0) style_button_click();
			else style_button_hover();
		}

		w = blockWidth; h = blockHeight;
		l = screenW/2 + marginOfBlock/2;
		t = screenH/3*2 - h/2;

		getRoundRectleBlock(logStr, l, t, w, h);

		EndBatchDraw();


		//判断低级行为
		if (flagReturn != -1) {
			Sleep(200);
			return flagReturn;
		}
	}
}
