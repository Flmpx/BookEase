#include "saveandload.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../function/function.h"

UserList loadUserListFromFile(const char* filePath) {
	FILE* userFile = fopen(filePath, "r");
	if (userFile == NULL) {
		userFile = fopen(filePath, "w");
		fclose(userFile);
		userFile = fopen(filePath, "r");
	}
	UserList list;
	initUserList(&list);


	UserInfo info;

	while (true) {

		int res = fscanf(userFile, "%lld %s %s %s %lld %lld %s %lld", 
			&(info.id),
			info.salt,	
			info.hashKey, 
			info.name, 
			&(info.tel),
			&(info.QQ),
			info.WeChat, 
			&(info.registerTime));
		if (res != 8) {
			break;
		}
		UserInfo* copyInfo = (UserInfo*)malloc(sizeof(UserInfo));
		if (copyInfo == NULL) {
			printf("内存分配失败\n");
			return list;
		}
		memcpy(copyInfo, &info, sizeof(UserInfo));
		insertUserInfoInUserList(&list, copyInfo);
	}
	fclose(userFile);
	return list;

}



InfoOfReturn saveUserListToFile(UserList* plist, const char* filePath) {
	FILE* userFile = fopen(filePath, "w");
	if (userFile == NULL) {
		printf("文件%s创建失败\n", filePath);
		return Warning;
	}
	UserNode* p = plist->head;
	while (p) {
		UserInfo* info = p->user;
		fprintf(userFile, "%lld %s %s %s %lld %lld %s %lld\n", info->id, 
			info->salt, 
			info->hashKey, 
			info->name, 
			info->tel, 
			info->QQ, 
			info->WeChat, 
			info->registerTime);
		p = p->next;
	}
	fclose(userFile);
	return Success;

}




BookList loadBookListFromFile(const char* filePath, UserList* plist) {
	FILE* bookFile = fopen(filePath, "r");
	if (bookFile == NULL) {
		bookFile = fopen(filePath, "w");
		fclose(bookFile);
		bookFile = fopen(filePath, "r");
	}

	BookList list;
	initBookList(&list);

	Book book;

	while (true) {
		int res = fscanf(bookFile, "%lld %s %s %s %lf %d %d\n%lld %lld\n%lld %lld\n%lld %lld\n", 
			&book.id, 
			book.title,
			book.ISBN,
			book.author,
			&book.price, 
			&book.status,
			&book.condition,
			&book.sellerId, &book.publishTime,
			&book.buyerId, &book.buyTime,
			&book.reserverId, &book.reserveTime);

		if (res != 13) {
			break;
		}
		linkBookForUser(&book, plist);
		Book* copyBook = (Book*)malloc(sizeof(Book));
		if (copyBook == NULL) {
			printf("内存分配失败\n");
			return list;
		}
		memcpy(copyBook, &book, sizeof(Book));
		insertBookInBookList(&list, copyBook);
	}
	fclose(bookFile);
	return list;
}


InfoOfReturn saveBookListToFile(BookList* plist, const char* filePath) {
	FILE* bookFile = fopen(filePath, "w");
	if (bookFile == NULL) {
		printf("文件%s创建失败\n", filePath);
		return Warning;
	}
	BookNode* p = plist->head;
	while (p) {
		Book* book = p->book;
		fprintf(bookFile, "%lld %s %s %s %lf %d %d\n%lld %lld\n%lld %lld\n%lld %lld\n", book->id,
																							book->title,
																							book->ISBN,
																							book->author,
																							book->price,

																							book->status,
																							book->condition,

																							book->sellerId,
																							book->publishTime,

																							book->buyerId,
																							book->buyTime,

																							book->reserverId, 
																							book->reserveTime);
		p = p->next;

	}
	fclose(bookFile);
	return Success;
}