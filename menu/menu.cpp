/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/
#include "menu.h"
#include <easyx.h>


//普通样式
void style_normal() {
    setfillcolor(RGB(250, 250, 252));
    setlinecolor(RGB(180, 190, 200));
    setlinestyle(PS_SOLID, 1);
}

//书籍上方小横条的提示信息样式
void style_tips() {
    setfillcolor(RGB(220, 235, 255));  
    setlinecolor(RGB(80, 130, 200));   
    setlinestyle(PS_SOLID, 1);         
}

//引导信息样式
void style_instruction() {
    setfillcolor(RGB(220, 245, 240));  
    setlinecolor(RGB(70, 180, 170));   
    setlinestyle(PS_SOLID, 1);
}

//返回键样式 
void style_back_start() {
    setfillcolor(RGB(240, 240, 245));  
    setlinecolor(RGB(150, 160, 180)); 
    setlinestyle(PS_SOLID, 1);
}

void style_back_hover() {
    setfillcolor(RGB(225, 230, 240));  
    setlinecolor(RGB(120, 140, 180)); 
    setlinestyle(PS_SOLID, 1);
}

void style_back_click() {
    setfillcolor(RGB(210, 220, 235)); 
    setlinecolor(RGB(100, 120, 160));  
    setlinestyle(PS_SOLID, 1);
}

//选项键样式 
void style_select_start() {
    setfillcolor(WHITE);
    setlinecolor(RGB(100, 150, 220));  
    setlinestyle(PS_SOLID, 1);
}
void style_select_hover() {
    setfillcolor(RGB(235, 245, 255));  
    setlinecolor(RGB(80, 140, 220));   
    setlinestyle(PS_SOLID, 2);         
}
void style_select_click() {
    setfillcolor(RGB(220, 235, 250));  
    setlinecolor(RGB(60, 130, 210)); 
    setlinestyle(PS_SOLID, 2);
}

//方向键样式, 用于控制书籍的翻页功能 
void style_diction_start() {
    setfillcolor(RGB(255, 250, 240)); 
    setlinecolor(RGB(220, 160, 80));   
    setlinestyle(PS_SOLID, 1);
}
void style_diction_hover() {
    setfillcolor(RGB(255, 240, 220));  
    setlinecolor(RGB(210, 140, 60));   
    setlinestyle(PS_SOLID, 2);
}
void style_diction_click() {
    setfillcolor(RGB(255, 230, 200));  
    setlinecolor(RGB(200, 120, 40));   
    setlinestyle(PS_SOLID, 2);
}

//书籍样式 
void style_book_start() {
    setfillcolor(WHITE);
    setlinecolor(RGB(180, 200, 220));  
    setlinestyle(PS_SOLID, 1);
}
void style_book_hover() {
    setfillcolor(RGB(245, 250, 255));  
    setlinecolor(RGB(100, 150, 220));  
    setlinestyle(PS_SOLID, 2);
}
void style_book_click() {
    setfillcolor(RGB(235, 245, 255));  
    setlinecolor(RGB(80, 130, 200));   
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
