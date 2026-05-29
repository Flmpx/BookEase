#include "revealmenu.h"
#include <easyx.h>
#include "../../function/function.h"
#include "../menu.h"





Book* revealMenu(int* res, int selectW, int selectH, int selectNum,char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInstru, int dictionW, int dictionH, const char* booksTips, BookList* bookList, int grapInSeleAndBooks, int row, int col) {
	
	//t-->top, l-->left, h-->height, w-->width
	int t, l, h, w;	//用于绘制的

	//tw-->textwidth, th-->textheight

	int tw, th;
	//获取窗口大小
	int screenH = getheight();
	int screenW = getwidth();


	
	
	

	int startHOfSelect = backH + grapInbcAndInstru + instruH;
	int startHOfBooks = backH + grapInbcAndInstru;

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
		Sleep(6);
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
		l = 0; t = 0; w = backW; h = backH;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_back_flag = 1;
			if (msg.message == WM_LBUTTONDOWN) {
				click_back_flag = 1;
			}
		}
		//selections检测
		l = 0; t = startHOfSelect; w = selectW; h = selectH*selectNum;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_select_flag = (msg.y - startHOfSelect)/selectH;
			if (msg.message == WM_LBUTTONDOWN) {
				click_select_flag = hover_select_flag;
			}
		}

		//切换键检测
		//<
		l = 0; t = screenH - dictionH; w = dictionW; h = dictionH;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_diction_flag = 0;
			if (msg.message == WM_LBUTTONDOWN) {
				click_diction_flag = 0;
			}
		}
		//>
		l = selectW - dictionW; t = screenH - dictionH; w = dictionW; h = dictionH;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_diction_flag = 1;
			if (msg.message == WM_LBUTTONDOWN) {
				click_diction_flag = 1;
			}
		}

		//books检测
		l = selectW + grapInSeleAndBooks; t = startHOfBooks; w = screenW - l; h = screenH - t;
		if (isInBlock(&msg, l, t, w, h)) {
			hover_book_flag = (msg.y - startHOfBooks)/singleBookH*col + (msg.x - selectW - grapInSeleAndBooks)/singleBookW;
			if (msg.message == WM_LBUTTONDOWN) {
				//防止空闲的位置
				if (hover_book_flag + startBooksNum < bookList->size) {
					click_book_flag = hover_book_flag;
				}
				
			}
		}

		//开始绘制
		BeginBatchDraw();

		//绘制之前先清屏, 书籍的信息会变动
		cleardevice();
		
		//绘制back键
		style_back_start();
		if (hover_back_flag == 1) {
			if (click_back_flag == 1) style_back_click();
			else style_back_hover();
		}
		
		t = 0, l = 0; h = backH; w = backW;
		getRoundRectleBlock(back, l, t, w, h);


		//绘制引导信息
		style_instruction();	//引导信息样式

		int instruW = selectW;
		t = backH + grapInbcAndInstru;
		l = 0; w = instruW; h = instruH;

		getRectangleBlock(instruction, l, t, w, h);


		//绘制select
		for (int i = 0; i < selectNum; i++) {
			style_select_start();
			if (i == hover_select_flag) {
				if (click_select_flag >= 0) style_select_click();
				else style_select_hover();
			}
			//块的上界
			t = startHOfSelect + i*selectH;
			l = 0; w = selectW; h = selectH;
			
			getRectangleBlock(selections[i], l, t, w, h);

		}

		//绘制方向键
		//<
		style_diction_start();
		if (hover_diction_flag == 0) {
			if (click_diction_flag == 0) style_diction_click();
			else style_diction_hover();
		}
		t = screenH - dictionH;
		l = 0; h = dictionH; w = dictionW;

		getRectangleBlock("<<<", l, t, w, h);


		//>
		style_diction_start();
		if (hover_diction_flag == 1) {
			if (click_diction_flag == 1) style_diction_click();
			else style_diction_hover();
		}
		t = screenH - dictionH;
		l = selectW - dictionW;
		h = dictionH; w = dictionW;

		getRectangleBlock(">>>", l, t, w, h);


		//绘制书籍提示信息
		style_tips();	//普通样式
		t = 0;
		l = selectW + grapInSeleAndBooks;
		h = startHOfBooks;
		w = screenW - l;

		getRoundRectleBlock(booksTips, l, t, w, h);

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
		EndBatchDraw();


		//进行点击后的行为
		if (click_back_flag != -1) {
			//返回
			*res = 0;
			return NULL;
		} else if (click_select_flag != -1) {
			//选项
			*res = click_select_flag + 1;
			return NULL;
		} else if (click_book_flag != -1) {
			//点击书籍
			for (int i = 0; i < click_book_flag; i++) {
				q = q->next;
			}
			*res = -1;
			return q->book;
		} else if (click_diction_flag == 0) {
			//点击<<<
			if (startBooksNum - col * row >= 0) {
				for (int i = 0; i < col * row; i++) {
					q = q->prev;
				}
				startBooksNum -= col*row;
			} else {
				MessageBox(GetHWnd(), "已经是开始页了!!!", "提示", MB_OK);
			}
		} else if (click_diction_flag == 1) {
			//点击>>>
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


