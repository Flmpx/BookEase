#include "base.h"
char BookStatusStr[4][101] = {"在售卖", "已预约", "已售卖", "已下架"};
char BookConditionStr[4][101] = {"几乎全新", "有点破损", "还可以用", "可以接受"};

#include "Lists/BookList/booklist.h"
#include "Lists/UserList/userlist.h"
#include <string.h>



UserInfo getEmptyUserInfo() {
	UserInfo info;
	strcpy(info.hashKey, Invalid_Str);
	info.id = Invalid_Num;
	strcpy(info.name, Invalid_Str);
	info.QQ = Invalid_Num;
	info.registerTime = Invalid_Num;
	strcpy(info.salt, Invalid_Str);
	info.tel = Invalid_Num;
	strcpy(info.WeChat, Invalid_Str);
	return info;

}

Book getEmptyBook() {
	Book book;
	book.seller = NULL;
	book.sellerId = Invalid_Num;
	book.buyer = NULL;
	book.buyerId = Invalid_Num;
	book.reserver = NULL;
	book.reserverId = Invalid_Num;
	book.id = Invalid_Num;

	strcpy(book.title, Invalid_Str);
	strcpy(book.ISBN, Invalid_Str);
	strcpy(book.author, Invalid_Str);

	book.price = Invalid_FloatNum;

	book.publishTime = book.buyTime = book.reserveTime = Invalid_Num;

	book.status = Invalid_BookStatus;
	book.condition = Invalid_BookCondition;

	return book;
}




UserInfoCmpCondition getEmptyUserInfoCmpCondition() {
	UserInfoCmpCondition empty;
	empty.id = Invalid_Num;
	empty.name[0] = '\0';
	return empty;
}


bool isSimilarUserInfo(UserInfo* user, UserInfoCmpCondition* userCondition) {
	//比较学号
	if (userCondition->id != Invalid_Num && user->id != userCondition->id) {
		return false;
	}
	//比较名字
	if (userCondition->name[0] != '\0' && strstr(user->name, userCondition->name) == NULL) {
		return false;
	}

	return true;
	
}


BookCmpCondition getEmptyBookCmpCondition() {
	BookCmpCondition empty;
	empty.author[0] = '\0';
	empty.isbn[0] = '\0';
	empty.title[0] = '\0';
	empty.condition = Invalid_BookCondition;
	empty.downPrice = empty.upPrice = Invalid_FloatNum;
	empty.downTime = empty.upTime = Invalid_Num;
	empty.id = Invalid_Num;
	empty.seller = getEmptyUserInfoCmpCondition();
	return empty;
}

bool isSimilarBook(Book* book, BookCmpCondition* bookCondition) {

	//比较书籍id
	if (bookCondition->id != Invalid_Num && book->id != bookCondition->id) {
		return false;
	}
	//比较售卖者
	if (isSimilarUserInfo(book->seller, &(bookCondition->seller)) == false) {
		return false;
	}

	//比较书名
	if (bookCondition->title[0] != '\0' && strstr(book->title, bookCondition->title) == NULL) {
		return false;
	}

	//比较isbn
	if (bookCondition->isbn[0] != '\0' && strstr(book->ISBN, bookCondition->isbn) == NULL) {
		return false;
	}

	//比较作者

	if (bookCondition->author[0] != '\0' && strstr(book->author, bookCondition->author) == NULL) {
		return false;
	}
	
	//比较价格
	if (bookCondition->downPrice > -EPS && book->price < bookCondition->downPrice - EPS) {
		return false;
	}
	if (bookCondition->upPrice > -EPS && book->price > bookCondition->upPrice + EPS) {
		return false;
	}

	
	//比较发布时间
	
	if (bookCondition->downTime != Invalid_Num && book->publishTime < bookCondition->downTime) {
		return false;
	}
	if (bookCondition->upTime != Invalid_Num && book->publishTime > bookCondition->upTime) {
		return false;
	}

	
	//比较新旧程度

	if (bookCondition->condition != Invalid_BookCondition && book->condition != bookCondition->condition) {
		return false;
	}

	return true;
}

