#include <easyx.h>
#include <stdio.h>

//static void style_button_start() {
//	setfillcolor(WHITE);
//	setlinecolor(BLACK);
//	setlinestyle(PS_SOLID, 1);
//}
//static void style_button_hover() {
//	setfillcolor(YELLOW);
//	setlinecolor(BLACK);
//	setlinestyle(PS_SOLID, 3);
//}
//static void style_button_dbclick() {
//	setfillcolor(RED);
//	setlinecolor(BLACK);
//	setlinestyle(PS_SOLID, 2);
//}
//static void style_tip() {
//	setfillcolor(RGB(54, 203, 190));
//	setlinecolor(BLACK);
//	setlinestyle(PS_SOLID, 2);
//}
//
//static void style_back_button() {
//	setfillcolor(RGB(191, 165, 243));
//	setlinecolor(BLACK);
//	setlinestyle(PS_SOLID, 2);
//}
//
//static void style_other() {
//	setbkmode(TRANSPARENT);
//	setlinecolor(WHITE);
//	settextcolor(WHITE);
//}
//
//static void printOther(int menuwidth, int others_num, char others[][101]) {
//
//
//	//提前得到窗口高度和宽度
//	int screen_w = getwidth();
//	int screen_h = getheight();
//
//	int t_area_h = 0;
//	int tw, th;
//	for (int i = 0; i < others_num; i++) {
//		t_area_h += textheight(others[i]);
//	}
//
//	int t_now_y = (screen_h-t_area_h)/2;	//当前的文本的开始的y轴坐标
//	int t_now_x;
//
//	style_other();
//	BeginBatchDraw();
//	for (int i = 0; i < others_num; i++) {
//		tw = textwidth(others[i]);
//		th = textheight(others[i]);
//		t_now_x = menuwidth + ((screen_w-menuwidth) - tw)/2;
//		outtextxy(t_now_x, t_now_y, others[i]);
//		t_now_y += th;
//	}
//	EndBatchDraw();
//}
//
//int menuOf(int menuwidth, int menuheight, int select_num, char* instruction, char selections[][101], int others_num, char others[][101]) {
//	int i;
//
//	int tw, th;	//选项文本的高度和宽度
//
//	printOther(menuheight, others_num, others);	//打印其他信息
//
//
//	setbkmode(TRANSPARENT);	//设置文本为透明模式
//
//
//	//返回键
//	char back[101] = {"<<<返回"};	//返回键文本
//
//
//	int back_w = 80, back_h = 30;	//
//	int grap_back_and_info = 20;
//
//	//先显示引导信息
//	int tip_h = 20, tip_w = menuwidth;
//	tw = textwidth(instruction);
//	th = textheight(instruction);
//
//
//	style_tip();	//引导信息样式
//	fillrectangle(0, back_h+grap_back_and_info, tip_w, tip_h+grap_back_and_info+back_h);
//	outtextxy((tip_w-tw)/2, back_h+grap_back_and_info+(tip_h-th)/2, instruction);
//
//	int info_start_h = tip_h+grap_back_and_info+back_h;
//	ExMessage msg = {0};
//	int flagReturn = -1;
//
//	while (true) {
//		Sleep(10);
//		int hover_loaction = select_num+1;
//		int hover_back = 0;
//		peekmessage(&msg, EX_MOUSE);
//		if (msg.x <= menuwidth && msg.x >= 0 && msg.y <= menuheight * select_num+info_start_h && msg.y >= info_start_h ) {
//			hover_loaction = (msg.y-info_start_h)/menuheight;
//			if (msg.message == WM_LBUTTONDOWN) {
//				flagReturn = hover_loaction+1;
//			}
//		}
//		if (msg.x <= back_w && msg.x >= 0 && msg.y <= back_h && msg.y >= 0) {
//			hover_back = 1;
//			if (msg.message == WM_LBUTTONDOWN) {
//				flagReturn = 0;
//			}
//		}
//		BeginBatchDraw();
//
//		//绘制back键
//		if (hover_back) style_button_hover();
//		else style_back_button();
//		tw = textwidth(back);
//		th = textheight(back);
//		fillroundrect(0, 0, back_w, back_h, 10, 10);
//		outtextxy((back_w-tw)/2, (back_h-th)/2, back);
//
//		for (i = 0; i < select_num; i++) {
//			style_button_start();
//			if (i == hover_loaction) {
//				if (flagReturn >= 0) style_button_dbclick();
//				else style_button_hover();
//			}
//			fillrectangle(0, info_start_h+i*menuheight, menuwidth, info_start_h + (i+1)*menuheight);
//			tw = textwidth(selections[i]);
//			th = textheight(selections[i]);
//			settextcolor(BLACK);
//			outtextxy((menuwidth-tw)/2,info_start_h + i*menuheight+(menuheight-th)/2, selections[i]);
//		}
//		EndBatchDraw();
//		if (flagReturn != -1) {
//			Sleep(200);
//			return flagReturn;
//		}
//	}	
//}
int main()
{


	
	printf("helloworld\n");
	return 0;
}
