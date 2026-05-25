#include "post.h"
#include <easyx.h>
#include "../../menu/DetailMenu/detailmenu.h"
#include "../../menu/NormalMenu/normalmenu.h"
#include "../../Process/saveandload/saveandload.h"

int changeBookCondition(Book* book) {
	
		cleardevice();
		int input_num = normalMenu(200, 90, 4, BookConditionStr, 100, 30, "返回", 20, "选择书籍的新旧程度", 30);
		switch (input_num) {
			
			case 1: book->condition = NEW; break;

			case 2: book->condition = LIKE_NEW; break;

			case 3: book->condition = GOOD; break;
			
			case 4:	book->condition = ACCEPTABLE; break;
		}

		return 1;
}


int InputStr(char* Str, const char* InputBoxInfo, const char* InputBoxTip, int maxLen) {
	int circle = 1;
	char temp[1001] = "";
	do {
		circle = 1;
		if (InputBox(temp, maxLen, InputBoxInfo, InputBoxTip, temp, 0, 0, false)) {
			if (temp[0] != '\0') {
				strcpy(Str, temp);
				circle = 0;
			} else {
				MessageBox(GetHWnd(), "输入不能为空", "提示", MB_OK);
				circle = 1;
			}
		} else {
			circle = 0;
		}

	} while (circle);
	return 1;
}

int changeBookInfo(Book* book) {
	int circle = 1;
	do {
		circle = 1;
		cleardevice();

		char selections[][101] = {"书籍名称", "ISBN", "书籍作者", "书籍状态", "书籍价格"};

		int input_num = detailBookMenu(200, 90, 5, selections, 100, 30, "退出修改", 20, "选择操作", 30, "当前待发布书籍详情", book, 10);

		switch (input_num) {
			case 0:

				circle = 0;
			break;

			case 1:
				InputStr(book->title, "输入书籍名称", "输入", BOOK_TITLE_MAX_LEN - 3);
			break;
			
			case 2:

				InputStr(book->ISBN, "输入书籍ISBN", "输入", ISBN_MAX_LEN - 3);
			break;
			
			case 3:

				InputStr(book->author, "输入书籍作者", "输入", BOOK_AUTHOR_MAX_LEN - 3);
			break;
			
			case 4:

				changeBookCondition(book);
			break;
			
			case 5:

			break;
		}

	} while (circle);
	return 1;
}


int post(BookList* mainBookList, UserInfo* onlineUser) {
	int circle = 1;
	Book* book = (Book*)malloc(sizeof(Book));
	*book = getEmptyBook();

	/*更新当前登录用户信息*/
	book->seller = onlineUser;
	book->sellerId = onlineUser->id;
	book->id = MaxBookId + 1;

	do {
		circle = 1;
		cleardevice();

		char selections[][101] = {"确认发布", "进行修改"};

		int input_num = detailBookMenu(200, 90, 2, selections, 150, 30, "退出并取消发布", 20, "选择操作", 10, "当前待发布书籍详情", book, 10);

		switch (input_num) {
			case 0:

				if (MessageBox(GetHWnd(), "确定要取消发布吗?", "提示", MB_YESNO) == IDYES) {
					free(book);
					circle = 0;
				}


			break;


			case 1:
				book->publishTime = time(NULL);
				insertBookInBookList(mainBookList, book);
				saveBookListToFile(mainBookList, "bookinfo.txt");
				MaxBookId++;
				MessageBox(GetHWnd(), "发布成功", "提示", MB_OK);
				circle = 0;
			break;


			case 2:
				changeBookInfo(book);
			break;



		}
		

		
	} while (circle);
	return 1;
}





