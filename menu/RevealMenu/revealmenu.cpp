#include "revealmenu.h"
#include <easyx.h>
#include "../../function/function.h"

static void style_instruction() {
	setfillcolor(RGB(54, 203, 190));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}

static void style_back_button_start() {
	setfillcolor(RGB(191, 165, 243));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
}

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


static void style_book_hover() {
	setfillcolor(RGB(5, 127, 215));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
}
static void style_book_start() {
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
}
static void style_book_click() {
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

Book* revealMenu(int* res, int selectW, int selectH, int selectNum,char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInsrtru, int dictionW, int dictionH, const char* booksTips, BookList* bookList, int grapInSeleAndBooks, int row, int col) {
	
	//t-->top, l-->left, h-->height, w-->width
	int t, l, h, w;	//用于绘制的

	//tw-->textwidth, th-->textheight

	int tw, th;
	//获取窗口大小
	int screenH = getheight();
	int screenW = getwidth();


	
	
	

	int startHOfSelect = backH + grapInbcAndInsrtru + instruH;
	int startHOfBooks = backH + grapInbcAndInsrtru;

	ExMessage msg = {0};
	int click_back_flag;
	int click_select_flag;
	int click_diction_flag;
	int click_book_flag;

	
	//返回键和选项键悬浮标志
	int hover_back_flag;
	int hover_select_flag;
	int hover_diction_flag;
	int hover_book_flag;

	//得到每本书的展示宽度
	int singleBookW = (screenW - selectW - grapInSeleAndBooks)/col;
	int singleBookH = (screenH - startHOfBooks)/row;

	int startBooksNum = 0;
	BookNode* q = bookList->head;
	
	while (true) {
		Sleep(10);
		click_back_flag = -1;
		click_select_flag = -1;
		click_diction_flag = -1;
		click_book_flag = -1;

		hover_back_flag = -1;
		hover_select_flag = -1;
		hover_diction_flag = -1;
		hover_book_flag = -1;

		//peekmessage(&msg, EX_MOUSE);
		msg = getmessage();

		//返回键检测
		if (msg.x <= backW && msg.x >= 0 && msg.y <= backH && msg.y >= 0) {
			hover_back_flag = 1;
			if (msg.message == WM_LBUTTONDOWN) {
				click_back_flag = 1;
			}
		}
		//selections检测

		if (msg.x <= selectW && msg.x >= 0 && msg.y <= startHOfSelect + selectH * selectNum && msg.y >= startHOfSelect) {
			hover_select_flag = (msg.y - startHOfSelect)/selectH;
			if (msg.message == WM_LBUTTONDOWN) {
				click_select_flag = hover_select_flag;
			}
		}

		//切换键检测
		//<
		if (msg.x <= dictionW && msg.x >= 0 && msg.y <= screenH && msg.y >= screenH - dictionH) {
			hover_diction_flag = 0;
			if (msg.message == WM_LBUTTONDOWN) {
				click_diction_flag = 0;
			}
		}
		//>
		if (msg.x <= selectW && msg.x >= selectW - dictionW && msg.y <= screenH && msg.y >= screenH - dictionH) {
			hover_diction_flag = 1;
			if (msg.message == WM_LBUTTONDOWN) {
				click_diction_flag = 1;
			}
		}

		//books检测

		if (msg.x <= screenW && msg.x >= selectW + grapInSeleAndBooks && msg.y <= screenH && msg.y >= startHOfBooks) {
			hover_book_flag = (msg.y - startHOfBooks)/singleBookH*col + (msg.x - selectW - grapInSeleAndBooks)/singleBookW;
			if (msg.message == WM_LBUTTONDOWN) {
				//防止空闲的位置
				if (hover_book_flag + startBooksNum < bookList->size) {
					click_book_flag = hover_book_flag;
				}
				
			}
		}

		//绘制之前先清屏, 书籍的信息会变动
		//开始绘制
		BeginBatchDraw();
		cleardevice();
		
		//绘制back键
		style_back_button_start();
		if (hover_back_flag == 1) {
			if (click_back_flag == 1) style_button_dbclick();
			else style_button_hover();
		}
		
		t = 0, l = 0; h = backH; w = backW;
		getRoundRectleBlock(back, l, t, w, h);

		/*tw = textwidth(back);
		th = textheight(back);
		fillroundrect(l, t, l + w, t + h, 10, 10);
		outtextxy(l + (w - tw)/2, t + (h - th) / 2 , back);*/

		//绘制引导信息
		style_instruction();	//引导信息样式

		int instruW = selectW;
		t = backH + grapInbcAndInsrtru;
		l = 0; w = instruW; h = instruH;

		getRectangleBlock(instruction, l, t, w, h);

		/*tw = textwidth(instruction);
		th = textheight(instruction);

		fillrectangle(l, t, l + w, t + h);
		outtextxy(l + (w - tw)/2, t + (h - th) / 2, instruction);*/



		//绘制select
		for (int i = 0; i < selectNum; i++) {
			style_button_start();
			if (i == hover_select_flag) {
				if (click_select_flag >= 0) style_button_dbclick();
				else style_button_hover();
			}
			//块的上界
			t = startHOfSelect + i*selectH;
			l = 0; w = selectW; h = selectH;
			
			getRectangleBlock(selections[i], l, t, w, h);
			/*fillrectangle(l, t, l + w, t + h);
			tw = textwidth(selections[i]);
			th = textwidth(selections[i]);
			outtextxy(l + (w - tw)/2, t + (h - th) / 2, selections[i]);*/
		}

		//绘制方向键
		//<
		style_button_start();
		if (hover_diction_flag == 0) {
			if (click_diction_flag == 0) style_book_click();
			else style_button_hover();
		}
		t = screenH - dictionH;
		l = 0; h = dictionH; w = dictionW;

		getRectangleBlock("<<<", l, t, w, h);

		/*fillrectangle(l, t, l + w, t + h);
		tw = textwidth("<<<");
		th = textwidth("<<<");
		outtextxy(l + (w - tw)/2, t + (h - th) / 2, "<<<");*/

		//>
		style_button_start();
		if (hover_diction_flag == 1) {
			if (click_diction_flag == 1) style_book_click();
			else style_button_hover();
		}
		t = screenH - dictionH;
		l = selectW - dictionW;
		h = dictionH; w = dictionW;

		getRectangleBlock(">>>", l, t, w, h);

		/*fillrectangle(l, t, l + w, t + h);
		tw = textwidth(">>>");
		th = textwidth(">>>");
		outtextxy(l + (w - tw)/2, t + (h - th) / 2, ">>>");*/


		//绘制书籍提示信息
		style_button_start();
		t = 0;
		l = selectW + grapInSeleAndBooks;
		h = startHOfBooks;
		w = screenW - l;

		getRoundRectleBlock(booksTips, l, t, w, h);

		/*th = textheight(booksTips);
		tw = textheight(booksTips);

		outtextxy(selectW + grapInSeleAndBooks, (startHOfSelectAndBooks - th)/2, booksTips);*/

		//绘制书籍信息
		BookNode* p = q;
		for (int i = 0; i < col * row && i < bookList->size - startBooksNum; i++, p = p->next) {
			style_book_start();
			if (i == hover_book_flag) {
				if (click_book_flag >= 0) style_book_click();
				else style_book_hover();
			}

			l = selectW + grapInSeleAndBooks + (i%col)*singleBookW;
			t = startHOfBooks + (i/col)*singleBookH;
			h = singleBookH; w = singleBookW;
			printSimpleBookInfo(p->book, l, t, w, h);
		}
		settextstyle(16, 0, "宋体");
		EndBatchDraw();


		//进行点击后的行为
		if (click_back_flag != -1) {
			*res = 0;
			return NULL;
		} else if (click_select_flag != -1) {
			*res = click_select_flag + 1;
			return NULL;
		} else if (click_book_flag != -1) {
			for (int i = 0; i < click_book_flag; i++) {
				q = q->next;
			}
			*res = -1;
			return q->book;
		} else if (click_diction_flag == 0) {
			if (startBooksNum - col * row >= 0) {
				for (int i = 0; i < col * row; i++) {
					q = q->prev;
				}
				startBooksNum -= col*row;
			} else {
				MessageBox(GetHWnd(), "已经是开始页了!!!", "提示", MB_OK);
			}
		} else if (click_diction_flag == 1) {
			if (startBooksNum + col * row < bookList->size) {
				for (int i = 0; i < col * row; i++) {
					q = q->next;
				}
				startBooksNum += col*row;
			} else {
				MessageBox(GetHWnd(), "已经是最后一页了!!!", "提示", MB_OK);

			}
		}

		
	}
}


