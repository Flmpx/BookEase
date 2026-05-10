#include "function.h"
#include <easyx.h>
#include <string.h>
#include <stdio.h>

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

void printSimpleBookInfo(Book* book, int l, int t, int w, int h) {
	int InfoNum = 5;
	int th = h/InfoNum;
	settextstyle(th, 0, "宋体");
	fillrectangle(l, t, l + w, t + h);

	char tempStr[1001];
	int cnt = 0;
	sprintf(tempStr, "书名:%s", book->title);
	outtextxy(l, t+(cnt++*th), tempStr);

	sprintf(tempStr, "作者:%s", book->author);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "ISBN:%s", book->ISBN);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "价格:%g", book->price);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "新旧程度:%s", BookConditionStr[book->condition]);
	outtextxy(l, t+(cnt++*th), tempStr);
}


void printAllBookInfo(Book* book, int x, int y, int width, int height) {
	int InfoNum = 5;
	int th = height/InfoNum;
	settextstyle(th, 0, "宋体");
	fillrectangle(x, y, x + width, y + height);
	char tempStr[1001];
	int cnt = 0;
	sprintf(tempStr, "书名:%s", book->title);
	outtextxy(x, y+(cnt++*th), tempStr);

	sprintf(tempStr, "作者:%s", book->author);
	outtextxy(x, y+(cnt++*th), tempStr);
	
	sprintf(tempStr, "ISBN:%s", book->ISBN);
	outtextxy(x, y+(cnt++*th), tempStr);
	
	sprintf(tempStr, "价格:%g", book->price);
	outtextxy(x, y+(cnt++*th), tempStr);
	
	sprintf(tempStr, "新旧程度:%s", BookConditionStr[book->condition]);
	outtextxy(x, y+(cnt++*th), tempStr);

	sprintf(tempStr, "卖方用户名:%s", book->seller->name);
	outtextxy(x, y+(cnt++*th), tempStr);
	
	sprintf(tempStr, "卖方学号:%lld", book->seller->id);
	outtextxy(x, y+(cnt++*th), tempStr);
	
	sprintf(tempStr, "卖方QQ号:%lld", book->seller->QQ);
	outtextxy(x, y+(cnt++*th), tempStr);
	
	sprintf(tempStr, "卖方微信号:%s", book->seller->WeChat);
	outtextxy(x, y+(cnt++*th), tempStr);

}


