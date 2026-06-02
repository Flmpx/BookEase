#include "post.h"
#include <easyx.h>
#include "../../menu/DetailMenu/detailmenu.h"
#include "../../menu/NormalMenu/normalmenu.h"
#include "../../Process/saveandload/saveandload.h"
#include "../../function/function.h"




int post(BookList* mainBookList, UserInfo* onlineUser) {
	int circle = 1;
	Book* book = (Book*)malloc(sizeof(Book));
	*book = getEmptyBook();
	

	/*
	*待发布书籍的默认信息
	*/
	book->status = ON_SALE;
	book->condition = NEW;
	book->category = OTHER;
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
				saveBookListToFile(mainBookList, "Data/bookinfo.txt");
				MaxBookId++;
				MessageBox(GetHWnd(), "发布成功", "提示", MB_OK);
				circle = 0;
			break;


			case 2:
				if (changeBookInfo(book)) {
					MessageBox(GetHWnd(), "修改保存成功", "提示", MB_OK);
				}
			break;



		}
		

		
	} while (circle);
	return 1;
}





