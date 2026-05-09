#include "function.h"
#include <easyx.h>


InfoOfReturn linkBookForUser(Book* book, UserList* plist) {
	//一本书一定有售卖者
	UserInfo* sellerInfo = getPtrUserInfoByIdInUserList(plist, book->sellerId);

	//一本书可能有购买者或者预约者
	UserInfo* buyerInfo = NULL;
	if (book->buyerId != InValid_ID) {
		buyerInfo = getPtrUserInfoByIdInUserList(plist, book->buyerId);
	}
	UserInfo* reserverInfo = NULL;
	if (book->reserverId != InValid_ID) {
		reserverInfo = getPtrUserInfoByIdInUserList(plist, book->reserverId);
	}

	book->seller = sellerInfo;
	book->buyer = buyerInfo;
	book->reserver = reserverInfo;
	return Success;
}

//void printBookInfo
