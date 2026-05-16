#include "menu.h"
#include <easyx.h>


void style_normal() {
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	
}

//普通样式
void style_tips() {
	setfillcolor(RGB(191, 165, 243));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}

//引导信息样式
void style_instruction() {
	setfillcolor(RGB(54, 203, 190));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}


//返回键样式
void style_back_start() {
	setfillcolor(RGB(191, 165, 243));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}

void style_back_hover() {
	setfillcolor(YELLOW);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
}

void style_back_click() {
	setfillcolor(RED);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}


//选项键样式
void style_select_start() {
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
}
void style_select_hover() {
	setfillcolor(YELLOW);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
}
void style_select_click() {
	setfillcolor(RED);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}


//方向键样式
void style_diction_start() {
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
}
void style_diction_hover() {
	setfillcolor(YELLOW);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
}
void style_diction_click() {
	setfillcolor(RED);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}


//书籍样式
void style_book_start() {
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
}
void style_book_hover() {
	setfillcolor(RGB(5, 127, 215));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
}
void style_book_click() {
	setfillcolor(RED);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}



void getRectangleBlock(const char* text, int l, int t, int w, int h) {
	int tw = textwidth(text);
	int th = textheight(text);
	fillrectangle(l, t, l + w, t + h);
	outtextxy(l + (w - tw)/2, t + (h - th)/2, text);
}


void getRoundRectleBlock(const char* text, int l, int t, int w, int h) {
	int tw = textwidth(text);
	int th = textheight(text);
	fillroundrect(l, t, l + w, t + h, 10, 10);
	outtextxy(l + (w - tw)/2, t + (h - th)/2, text);
}

bool isInBlock(ExMessage* msg, int l, int t, int w, int h) {
	if (msg->x <= l + w && msg->x >= l && msg->y <= t + h && msg->y >= t) {
		return true;
	} else {
		return false;
	}
}
