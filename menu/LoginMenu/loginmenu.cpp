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

	//reg-->register-->×¢²á
	//log-->login-->µÇÂ¼

	const char* regStr = "×¢²á";
	const char* logStr = "µÇÂ¼";

	int flagReturn = -1;	//0´ú±í·µ»Ø×¢²á, 1´ú±í·µ»ØµÇÂ¼

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	ExMessage msg = {0};
	while (true) {
		Sleep(6);

		bool hover_reg = false, hover_log = false;

		//peekmessage(&msg, EX_MOUSE);
		msg = getmessage();

		//¼ì²â×¢²á
		w = blockWidth; h = blockHeight;
		l = screenW/2 - marginOfBlock/2 - w;
		t = screenH/3*2 - h/2;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_reg = true;
			if (msg.message == WM_LBUTTONDOWN) {
				//µã»÷ÁË×¢²á
				flagReturn = 0;
			}
		}

		//¼ì²âµÇÂ¼¼ü
		w = blockWidth; h = blockHeight;
		l = screenW/2 + marginOfBlock/2;
		t = screenH/3*2 - h/2;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_log = true;
			if (msg.message == WM_LBUTTONDOWN) {
				//µã»÷ÁËµÇÂ¼
				flagReturn = 1;
			}
		}
		BeginBatchDraw();

		//»æÖÆReg

		style_button_start();
		if (hover_reg) {
			if (flagReturn >= 0) style_button_click();
			else style_button_hover();
		}
		w = blockWidth; h = blockHeight;
		l = screenW/2 - marginOfBlock/2 - w;
		t = screenH/3*2 - h/2;

		getRoundRectleBlock(regStr, l, t, w, h);



		//»æÖÆLog
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


		//ÅÐ¶ÏµÍ¼¶ÐÐÎª
		if (flagReturn != -1) {
			Sleep(200);
			return flagReturn;
		}
	}
}
