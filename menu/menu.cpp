#include "menu.h"
#include <easyx.h>

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
