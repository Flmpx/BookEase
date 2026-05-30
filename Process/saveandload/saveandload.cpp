#include "saveandload.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../function/function.h"

UserList loadUserListFromFile(const char* filePath) {
	FILE* userFile = fopen(filePath, "r");
	if (userFile == NULL) {
		/*
		* 如果读取失败, 那就再创建一个
		*/
		userFile = fopen(filePath, "w");
		fclose(userFile);
		userFile = fopen(filePath, "r");
	}


	UserList list;
	initUserList(&list);


	UserInfo info;

	while (true) {
		
		/*
		*	分别读取用户id, salt, hashkey, 用户名, 电话, QQ号, 微信号, 注册时间
		*	同时用res记录读取成功的数量
		*/
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
			/* 如果读取数目不足, 说明读到文档末尾或者文件有问题*/
			break;
		}

		/*动态分配一个一模一样的用户, 然后插入主用户链表*/
		UserInfo* copyInfo = (UserInfo*)malloc(sizeof(UserInfo));
		if (copyInfo == NULL) {
			printf("内存分配失败\n");
			return list;
		}
		memcpy(copyInfo, &info, sizeof(UserInfo));
		insertUserInfoInUserList(&list, copyInfo);
	}
	/*关闭文件*/
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
		/*
		* 分别写入用户id, salt, hashkey, 用户名, 电话, QQ号, 微信号, 注册时间
		*/
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
	/*关闭文件*/
	fclose(userFile);
	return Success;

}




BookList loadBookListFromFile(const char* filePath, UserList* plist) {
	FILE* bookFile = fopen(filePath, "r");
	if (bookFile == NULL) {
		/*
		* 如果读取失败, 那就再创建一个
		*/
		bookFile = fopen(filePath, "w");
		fclose(bookFile);
		bookFile = fopen(filePath, "r");
	}

	BookList list;
	initBookList(&list);

	Book book;

	while (true) {
		/*
		* 分别读取书籍的id, 名字, isbn, 作者, 价格, 状态, 新旧程度
		* 发布者id, 发布时间
		* 购买者id, 购买时间
		* 预定者时间, 预定时间
		*/
		int res = fscanf(bookFile, "%lld %s %s %s %lf %d %d %d\n%lld %lld\n%lld %lld\n%lld %lld\n", 
			&book.id, 
			book.title,
			book.ISBN,
			book.author,
			&book.price, 
			&book.status,
			&book.condition,
			&book.category,
			&book.sellerId, &book.publishTime,
			&book.buyerId, &book.buyTime,
			&book.reserverId, &book.reserveTime);

		if (res != 14) {
			/* 如果读取数目不足, 说明读到文档末尾或者文件有问题*/
			break;
		}
		
		/*将每一本书和发布者, 预定者, 购买者之间建立联系*/
		linkBookForUser(&book, plist);

		/*复制一本一样的书*/
		Book* copyBook = (Book*)malloc(sizeof(Book));
		if (copyBook == NULL) {
			printf("内存分配失败\n");
			return list;
		}

		memcpy(copyBook, &book, sizeof(Book));
		insertBookInBookList(&list, copyBook);

		/* 更新最大的书籍id*/
		if (book.id > MaxBookId) {
			MaxBookId = book.id;
		}
	}
	/*关闭文件*/
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
		/*
		* 分别写入书籍的id, 名字, isbn, 作者, 价格, 状态, 新旧程度
		* 发布者id, 发布时间
		* 购买者id, 购买时间
		* 预定者时间, 预定时间
		*/
		fprintf(bookFile, "%lld %s %s %s %lf %d %d %d\n%lld %lld\n%lld %lld\n%lld %lld\n", book->id,
																							book->title,
																							book->ISBN,
																							book->author,
																							book->price,

																							book->status,
																							book->condition,
																							book->category,

																							book->sellerId,
																							book->publishTime,

																							book->buyerId,
																							book->buyTime,

																							book->reserverId, 
																							book->reserveTime);
		/*转向下一个节点*/
		p = p->next;

	}

	/*关闭文件*/
	fclose(bookFile);
	return Success;
}