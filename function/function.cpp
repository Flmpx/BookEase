#include "function.h"
#include <easyx.h>
#include <string.h>
#include <stdio.h>
#include "../base.h"
#include <time.h>

InfoOfReturn linkBookForUser(Book* book, UserList* plist) {
	//一本书一定有售卖者
	UserInfo* sellerInfo = getPtrUserInfoByIdInUserList(plist, book->sellerId);

	//一本书可能有购买者或者预约者
	UserInfo* buyerInfo = NULL;
	if (book->buyerId != Invalid_Num) {
		buyerInfo = getPtrUserInfoByIdInUserList(plist, book->buyerId);
	}
	UserInfo* reserverInfo = NULL;
	if (book->reserverId != Invalid_Num) {
		reserverInfo = getPtrUserInfoByIdInUserList(plist, book->reserverId);
	}

	book->seller = sellerInfo;
	book->buyer = buyerInfo;
	book->reserver = reserverInfo;
	return Success;
}


void printUserInfo(UserInfo* info, int l, int t, int w, int h) {
	int InofNum = 6;
	int th = h/InofNum;
	fillrectangle(l, t, l + w, t + h);
	char tempStr[1001];
	int cnt = 0;
	sprintf(tempStr, "用户名:%s", info->name);
	outtextxy(l, t+(cnt++)*th, tempStr);

	sprintf(tempStr, "学号:%lld", info->id);
	outtextxy(l, t+(cnt++)*th, tempStr);
	
	sprintf(tempStr, "电话:%lld", info->tel);
	outtextxy(l, t+(cnt++)*th, tempStr);

	sprintf(tempStr, "QQ:%lld", info->QQ);
	outtextxy(l, t+(cnt++)*th, tempStr);

	sprintf(tempStr, "微信号:%s", info->WeChat);
	outtextxy(l, t+(cnt++)*th, tempStr);

	struct tm time = *localtime(&(info->registerTime));


	sprintf(tempStr, "注册时间:%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
	outtextxy(l, t+(cnt++)*th, tempStr);


}

void printSimpleBookInfo(Book* book, int l, int t, int w, int h) {
	int InfoNum = 6;
	int th = h/InfoNum;
	//settextstyle(th, 0, "宋体");
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

	struct tm time = *localtime(&(book->publishTime));
	sprintf(tempStr, "上架时间:%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
	outtextxy(l, t+(cnt++)*th, tempStr);

}


void printAllBookInfo(Book* book, int l, int t, int w, int h) {
	int InfoNum = 13;
	if (book->buyerId != Invalid_Num) {
		InfoNum += 7;
	}
	if (book->reserverId != Invalid_Num) {
		InfoNum += 7;
	}
	int th = h/InfoNum;
	//settextstyle(th, 0, "宋体");
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

	line(l, t + (cnt*th), l + w, t + (cnt*th));
	cnt++;

	sprintf(tempStr, "卖方用户名:%s", book->seller->name);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "卖方学号:%lld", book->seller->id);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "卖方电话:%lld", book->seller->tel);
	outtextxy(l, t+(cnt++*th), tempStr);
	

	sprintf(tempStr, "卖方QQ号:%lld", book->seller->QQ);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "卖方微信号:%s", book->seller->WeChat);
	outtextxy(l, t+(cnt++*th), tempStr);

	struct tm time = *localtime(&(book->publishTime));
	sprintf(tempStr, "发布时间:%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
	outtextxy(l, t+(cnt++)*th, tempStr);
	
	line(l, t + (cnt*th), l + w, t + (cnt*th));
	cnt++;

	if (book->reserverId != Invalid_Num) {
		sprintf(tempStr, "预定方用户名:%s", book->reserver->name);
		outtextxy(l, t+(cnt++*th), tempStr);
	
		sprintf(tempStr, "预定方学号:%lld", book->reserver->id);
		outtextxy(l, t+(cnt++*th), tempStr);
		
		sprintf(tempStr, "预定方电话:%lld", book->reserver->tel);
		outtextxy(l, t+(cnt++*th), tempStr);

		sprintf(tempStr, "预定方QQ号:%lld", book->reserver->QQ);
		outtextxy(l, t+(cnt++*th), tempStr);
	
		sprintf(tempStr, "预定方微信号:%s", book->reserver->WeChat);
		outtextxy(l, t+(cnt++*th), tempStr);

		time = *localtime(&(book->reserveTime));
		sprintf(tempStr, "预定时间:%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
		outtextxy(l, t+(cnt++)*th, tempStr);

		line(l, t + (cnt*th), l + w, t + (cnt*th));
		cnt++;
	}


	if (book->buyerId != Invalid_Num) {
		sprintf(tempStr, "买方用户名:%s", book->buyer->name);
		outtextxy(l, t+(cnt++*th), tempStr);

		sprintf(tempStr, "买方学号:%lld", book->buyer->id);
		outtextxy(l, t+(cnt++*th), tempStr);

		sprintf(tempStr, "买方电话:%lld", book->buyer->tel);
		outtextxy(l, t+(cnt++*th), tempStr);

		sprintf(tempStr, "买方QQ号:%lld", book->buyer->QQ);
		outtextxy(l, t+(cnt++*th), tempStr);

		sprintf(tempStr, "买方微信号:%s", book->buyer->WeChat);
		outtextxy(l, t+(cnt++*th), tempStr);

		time = *localtime(&(book->buyTime));
		sprintf(tempStr, "购买时间:%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
		outtextxy(l, t+(cnt++)*th, tempStr);

		line(l, t + (cnt*th), l + w, t + (cnt*th));
		cnt++;
	}



}



bool InputStr(char* Str, const char* InputBoxInfo, const char* InputBoxTip, int maxLen) {
	bool changed = false;
	int circle = 1;
	char temp[1001] = "";
	do {
		circle = 1;
		if (InputBox(temp, maxLen, InputBoxInfo, InputBoxTip, temp, 0, 0, false)) {
			if (temp[0] != '\0') {
				strcpy(Str, temp);
				changed = true;
				circle = 0;
			} else {
				MessageBox(GetHWnd(), "输入不能为空", "提示", MB_OK);
				circle = 1;
			}
		} else {
			circle = 0;
			changed = false;
		}

	} while (circle);
	return changed;
}

bool InputInter(ll* num, const char* InputBoxInfo, const char* InputBoxTip) {
	bool changed = false;
	int circle = 1;
	ll temp_num;
	char temp[1001] = "";
	do {
		circle = 1;
		if (InputBox(temp, 1000, InputBoxInfo, InputBoxTip, temp, 0, 0, false)) {
			if (sscanf(temp, "%lld", &temp_num) == 1 && temp_num > Invalid_Num) {
				*num = temp_num;
				circle = 0;
				changed = true;
			} else {
				MessageBox(GetHWnd(), "输入有误", "提示", MB_OK);
				circle = 1;
			}
		} else {
			changed = false;
			circle = 0;
		}

	} while (circle);
	return changed;
}


bool InputFloat(double* num, const char* InputBoxInfo, const char* InputBoxTip) {
	bool changed = false;
	int circle = 1;
	double temp_num;
	char temp[1001] = "";
	do {
		circle = 1;
		if (InputBox(temp, 1000, InputBoxInfo, InputBoxTip, temp, 0, 0, false)) {
			if (sscanf(temp, "%lf", &temp_num) == 1 && temp_num > Invalid_Num - EPS) {
				*num = temp_num;
				circle = 0;
				changed = true;
			} else {
				MessageBox(GetHWnd(), "输入有误", "提示", MB_OK);
				circle = 1;
			}
		} else {
			changed = true;
			circle = 0;
		}

	} while (circle);

	return changed;
}
