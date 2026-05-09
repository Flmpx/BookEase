#include "base.h"
#include "Lists/BookList/booklist.h"
#include "Lists/UserList/userlist.h"
#include <string.h>





UserInfoCmpCondition getEmptyUserInfoCmpCondition() {
	UserInfoCmpCondition empty;
	empty.id = InValid_ID;
	empty.name = NULL;
	return empty;
}


bool isSimilarUserInfo(UserInfo* user, UserInfoCmpCondition* userCondition) {
	//比较学号
	if (userCondition->id != InValid_ID && user->id != userCondition->id) {
		return false;
	}
	//比较名字
	if (userCondition->name != NULL && strstr(user->name, userCondition->name) == NULL) {
		return false;
	}

	return true;
	
}


BookCmpCondition getEmptyBookCmpCondition() {
	BookCmpCondition empty;
	empty.author = empty.isbn = empty.title = NULL;
	empty.condition = Invalid_BookCondition;
	empty.downPrice = empty.upPrice = Invalid_Price;
	empty.downTime = empty.upTime = InValid_Time;
	empty.id = InValid_ID;
	empty.seller = getEmptyUserInfoCmpCondition();
	return empty;
}

bool isSimilarBook(Book* book, BookCmpCondition* bookCondition) {

	//比较书籍id
	if (bookCondition->id != InValid_ID && book->id != bookCondition->id) {
		return false;
	}
	//比较售卖者
	if (isSimilarUserInfo(book->seller, &(bookCondition->seller)) == false) {
		return false;
	}

	//比较书名
	if (bookCondition->title != NULL && strstr(book->title, bookCondition->title) == NULL) {
		return false;
	}

	//比较isbn
	if (bookCondition->isbn != NULL && strstr(book->ISBN, bookCondition->isbn) == NULL) {
		return false;
	}

	//比较作者

	if (bookCondition->author != NULL && strstr(book->author, bookCondition->author) == NULL) {
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
	
	if (bookCondition->downTime != InValid_Time && book->publishTime < bookCondition->downTime) {
		return false;
	}
	if (bookCondition->upTime != InValid_Time && book->publishTime > bookCondition->upTime) {
		return false;
	}

	
	//比较新旧程度

	if (bookCondition->condition != Invalid_BookCondition && book->condition != bookCondition->condition) {
		return false;
	}

	return true;
}
