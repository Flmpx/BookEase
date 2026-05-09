#include <easyx.h>
#include <stdio.h>
#include "base.h"
#include "menu/LoginMenu/loginmenu.h"
#include "Lists/BookList/booklist.h"
#include "Lists/UserList/userlist.h"
#include "menu/RevealMenu/revealmenu.h"

int main()
{

	initgraph(1250, 640);
	setbkcolor(RGB(34, 166, 242));
	cleardevice();
	Book book;
	memcpy(book.author, "ddd", 4);
	memcpy(book.title, "aaa", 4);
	memcpy(book.ISBN, "aa", 3);
	book.price = 100;
	book.condition = NEW;
	BookList list;
	initBookList(&list);
	insertBookInBookList(&list, &book);

	int circle;
	do {
		circle = 1;

		int input_num = loginMenu(200, 90, 400);
		int i;
		char ins[2][101] = {"1", "2"};
		revealMenu(&i, 200, 80, 2, ins, 60, 20, "返回", 30, "aaaa", 10, 60, 40, "aaaa", &list, 5, 3, 3);

	} while (circle);
	
	printf("helloworld\n");
	return 0;
}
