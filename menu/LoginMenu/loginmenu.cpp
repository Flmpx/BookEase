#include "../../base.h"
#include <easyx.h>

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
static void style_button_dbclick() {
	setfillcolor(RED);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}


int loginMenu(int blockWidth, int blockHeight, int marginOfBlock) {
	int screenWidth = getwidth();	
	int screenHeight = getheight();

	//reg-->register-->注册
	//log-->login-->登录

	const char* regStr = "注册";
	const char* logStr = "登录";
	//两个数组分别代表注册和登陆的两个block的上下界, 左右界
	//0-->上, 1-->下, 2-->左, 3-->右
	int regBlockxy[4];
	int logBlockxy[4];
	regBlockxy[0] = logBlockxy[0] = (screenHeight/3*2) - (blockHeight/2);
	regBlockxy[1] = logBlockxy[1] = (screenHeight/3*2) + (blockHeight/2);

	regBlockxy[3] = (screenWidth/2) - (marginOfBlock/2);
	logBlockxy[2] = (screenWidth/2) + (marginOfBlock/2);

	regBlockxy[2] = regBlockxy[3] - blockWidth;
	logBlockxy[3] = logBlockxy[2] + blockWidth;

	int twOfreg = textwidth(regStr);
	int thOfreg = textheight(regStr);
	int twOflog = textwidth(logStr);
	int thOflog = textheight(logStr);

	int flagReturn = -1;	//0代表返回注册, 1代表返回登录

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	ExMessage msg = {0};
	while (true) {
		Sleep(10);
		bool hover_reg = false, hover_log = false;

		peekmessage(&msg, EX_MOUSE);

		if (msg.x >= regBlockxy[2] && msg.x <= regBlockxy[3] && msg.y >= regBlockxy[0] && msg.y <= regBlockxy[1]) {
			hover_reg = true;
			if (msg.message == WM_LBUTTONDOWN) {
				//点击了登录
				flagReturn = 0;
			}
		}

		if (msg.x >= logBlockxy[2] && msg.x <= logBlockxy[3] && msg.y >= logBlockxy[0] && msg.y <= logBlockxy[1]) {
			hover_log = true;
			if (msg.message == WM_LBUTTONDOWN) {
				//点击了注册
				flagReturn = 1;
			}
		}
		BeginBatchDraw();

		//绘制Reg
		style_button_start();
		if (hover_reg) {
			if (flagReturn >= 0) style_button_dbclick();
			else style_button_hover();
		}
		//					左			上				右				下
		fillroundrect(regBlockxy[2], regBlockxy[0], regBlockxy[3], regBlockxy[1], 10, 10);
		outtextxy(regBlockxy[2] + (blockWidth - twOfreg)/2, regBlockxy[0] + (blockHeight - thOfreg)/2, regStr);



		//绘制Log
		style_button_start();
		if (hover_log) {
			if (flagReturn >= 0) style_button_dbclick();
			else style_button_hover();
		}
		//					左			上				右				下
		fillroundrect(logBlockxy[2], logBlockxy[0], logBlockxy[3], logBlockxy[1], 10, 10);
		outtextxy(logBlockxy[2] + (blockWidth - twOflog)/2, logBlockxy[0] + (blockHeight - thOflog)/2, logStr);

		EndBatchDraw();

		if (flagReturn != -1) {
			Sleep(200);
			return flagReturn;
		}
	}
}
