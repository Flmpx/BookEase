#include <easyx.h>
#include <stdio.h>
#include "menu/LoginMenu/loginmenu.h"
int main()
{

	initgraph(900, 500);
	setbkcolor(RGB(34, 166, 242));
	cleardevice();
	int circle;
	do {
		circle = 1;

		int input_num = loginMenu(200, 90, 400);

	} while (circle);
	
	printf("helloworld\n");
	return 0;
}
