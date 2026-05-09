#include "menulists.h"
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
static void style_tip() {
	setfillcolor(RGB(54, 203, 190));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}

static void style_back_button() {
	setfillcolor(RGB(191, 165, 243));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}

static void style_other() {
	setbkmode(TRANSPARENT);
	setlinecolor(WHITE);
	settextcolor(WHITE);
}



