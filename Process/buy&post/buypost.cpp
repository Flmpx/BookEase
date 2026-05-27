#include "buypost.h"
#include <easyx.h>
#include "../../menu/DetailMenu/detailmenu.h"
#include <stdio.h>

int buy(Book* book, UserInfo* onlineUser) {
	
	/*
		此函数由检索后点击书籍的购买, 我的页的预定和已购共同调用
	
	*/

	int circle = 1;
	do {
		circle = 1;
		cleardevice();

		char selections[][101] = {"在没购买的情况下这里会写是否预定"};
		if (book->buyerId != Invalid_Num) {
			strcpy(selections[0], "书籍已售, 无法操作");

		} else if (book->reserverId != Invalid_Num) {
			/*
				通过检索的树必定是在售状态的, 不可能是预定状态的, 这是用于我的页的预定页中可以找到自己的预定书籍

			*/
			strcpy(selections[0], "书籍已预定");
		} else {
			strcpy(selections[0], "书籍未预定");
		}





	} while (circle);
	return 1;
}
