#include "function.h"
#include <easyx.h>
#include <string.h>
#include <stdio.h>
#include "../../Process/login/login.h"
#include "../../menu/DetailMenu/detailmenu.h"
#include "../../menu/NormalMenu/normalmenu.h"
#include "../../menu/RevealMenu/revealmenu.h"
#include "../base.h"
#include "../Lists/BookList/booklist.h"
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
	int InofNum = 7;
	int th = h/InofNum;
	fillrectangle(l, t, l + w, t + h);
	char tempStr[1001] = "";
	int cnt = 0;
	/*距离上方占据一定空间*/
	outtextxy(l, t+(cnt++)*th, tempStr);


	sprintf(tempStr, "     用户名:%s", info->name);
	outtextxy(l, t+(cnt++)*th, tempStr);

	sprintf(tempStr, "     学号:%lld", info->id);
	outtextxy(l, t+(cnt++)*th, tempStr);
	
	sprintf(tempStr, "     电话:%lld", info->tel);
	outtextxy(l, t+(cnt++)*th, tempStr);

	sprintf(tempStr, "     QQ:%lld", info->QQ);
	outtextxy(l, t+(cnt++)*th, tempStr);

	sprintf(tempStr, "     微信号:%s", info->WeChat);
	outtextxy(l, t+(cnt++)*th, tempStr);

	struct tm time = *localtime(&(info->registerTime));


	sprintf(tempStr, "     注册时间:%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
	outtextxy(l, t+(cnt++)*th, tempStr);


}

void printSimpleBookInfo(Book* book, int l, int t, int w, int h) {
	int InfoNum = 9;
	int th = h/InfoNum;
	//settextstyle(th, 0, "     宋体");
	fillrectangle(l, t, l + w, t + h);

	char tempStr[1001] = "";
	int cnt = 0;

	/*距离上方占据一定空间*/
	outtextxy(l, t+(cnt++)*th, tempStr);

	sprintf(tempStr, "     ID:%lld", book->id);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "     书名:%s", book->title);
	outtextxy(l, t+(cnt++*th), tempStr);

	sprintf(tempStr, "     作者:%s", book->author);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "     ISBN:%s", book->ISBN);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "     价格:%g", book->price);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "     新旧程度:%s", BookConditionStr[book->condition]);
	outtextxy(l, t+(cnt++*th), tempStr);

	sprintf(tempStr, "     书籍类别:%s", BookCategoryStr[book->category]);
	outtextxy(l, t+(cnt++*th), tempStr);

	struct tm time = *localtime(&(book->publishTime));
	sprintf(tempStr, "     上架时间:%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
	outtextxy(l, t+(cnt++)*th, tempStr);

}


void printAllBookInfo(Book* book, int l, int t, int w, int h) {
	int InfoNum = 16;
	if (book->buyerId != Invalid_Num) {
		InfoNum += 7;
	}
	if (book->reserverId != Invalid_Num) {
		InfoNum += 7;
	}
	int th = h/InfoNum;
	//settextstyle(th, 0, "     宋体");
	fillrectangle(l, t, l + w, t + h);
	char tempStr[1001] = "";
	int cnt = 0;

	/*距离上方占据一定空间*/
	outtextxy(l, t+(cnt++)*th, tempStr);


	sprintf(tempStr, "     ID:%lld", book->id);
	outtextxy(l, t+(cnt++*th), tempStr);

	sprintf(tempStr, "     书名:%s", book->title);
	outtextxy(l, t+(cnt++*th), tempStr);

	sprintf(tempStr, "     作者:%s", book->author);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "     ISBN:%s", book->ISBN);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "     价格:%g", book->price);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "     新旧程度:%s", BookConditionStr[book->condition]);
	outtextxy(l, t+(cnt++*th), tempStr);

	sprintf(tempStr, "     书籍类别:%s", BookCategoryStr[book->category]);
	outtextxy(l, t+(cnt++*th), tempStr);

	line(l, t + (cnt*th), l + w, t + (cnt*th));
	cnt++;

	sprintf(tempStr, "     卖方用户名:%s", book->seller->name);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "     卖方学号:%lld", book->seller->id);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "     卖方电话:%lld", book->seller->tel);
	outtextxy(l, t+(cnt++*th), tempStr);
	

	sprintf(tempStr, "     卖方QQ号:%lld", book->seller->QQ);
	outtextxy(l, t+(cnt++*th), tempStr);
	
	sprintf(tempStr, "     卖方微信号:%s", book->seller->WeChat);
	outtextxy(l, t+(cnt++*th), tempStr);

	struct tm time = *localtime(&(book->publishTime));
	sprintf(tempStr, "     发布时间:%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
	outtextxy(l, t+(cnt++)*th, tempStr);
	
	line(l, t + (cnt*th), l + w, t + (cnt*th));
	cnt++;

	if (book->reserverId != Invalid_Num) {
		sprintf(tempStr, "     预定方用户名:%s", book->reserver->name);
		outtextxy(l, t+(cnt++*th), tempStr);
	
		sprintf(tempStr, "     预定方学号:%lld", book->reserver->id);
		outtextxy(l, t+(cnt++*th), tempStr);
		
		sprintf(tempStr, "     预定方电话:%lld", book->reserver->tel);
		outtextxy(l, t+(cnt++*th), tempStr);

		sprintf(tempStr, "     预定方QQ号:%lld", book->reserver->QQ);
		outtextxy(l, t+(cnt++*th), tempStr);
	
		sprintf(tempStr, "     预定方微信号:%s", book->reserver->WeChat);
		outtextxy(l, t+(cnt++*th), tempStr);

		time = *localtime(&(book->reserveTime));
		sprintf(tempStr, "     预定时间:%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
		outtextxy(l, t+(cnt++)*th, tempStr);

		line(l, t + (cnt*th), l + w, t + (cnt*th));
		cnt++;
	}


	if (book->buyerId != Invalid_Num) {
		sprintf(tempStr, "     买方用户名:%s", book->buyer->name);
		outtextxy(l, t+(cnt++*th), tempStr);

		sprintf(tempStr, "     买方学号:%lld", book->buyer->id);
		outtextxy(l, t+(cnt++*th), tempStr);

		sprintf(tempStr, "     买方电话:%lld", book->buyer->tel);
		outtextxy(l, t+(cnt++*th), tempStr);

		sprintf(tempStr, "     买方QQ号:%lld", book->buyer->QQ);
		outtextxy(l, t+(cnt++*th), tempStr);

		sprintf(tempStr, "     买方微信号:%s", book->buyer->WeChat);
		outtextxy(l, t+(cnt++*th), tempStr);

		time = *localtime(&(book->buyTime));
		sprintf(tempStr, "     购买时间:%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
		outtextxy(l, t+(cnt++)*th, tempStr);

		line(l, t + (cnt*th), l + w, t + (cnt*th));
		cnt++;
	}



}


void printStatistics(UserList* mainUserList, BookList* mainBookList, int l, int t, int w, int h) {
	int InfoNum = 8;
	int th = h/InfoNum;
	char tempStr[1001] = "";

	int cnt = 0;
	fillrectangle(l, t, l + w, t + h);

	/*距离上方占据一定空间*/
	outtextxy(l, t+(cnt++)*th, tempStr);

	time_t nowTime = time(NULL);
	time_t diffTime = nowTime - releaseTime;

	int day = diffTime/(60*60*24);
	int hour = diffTime % (60*60*24) / (60*60);
	int min = diffTime % (60*60) /(60);
	int sec = diffTime % (60);

	sprintf(tempStr, "     BookEase已经走过了 %d 天 %d 小时 %d 分钟 %d 秒", day, hour, min, sec);
	outtextxy(l, t+(cnt++*th), tempStr);

	IterBookList iter;
	initIterBookList(&iter, mainBookList);
	double amount = 0;
	int numOfStatus[4] = {0};

	while (iterBookListHasNext(&iter)) {
		Book* book = iterBookListNext(&iter);
		BookStatus flag = book->status;
		numOfStatus[flag]++;
		if (flag == SOLD) {
			amount += book->price;
		}
	}

	sprintf(tempStr, "     有 %d 本书来到了这里(总上架数目)", mainBookList->size);
	outtextxy(l, t+(cnt++*th), tempStr);

	sprintf(tempStr, "     有 %d 本书正在等待被发现(在售数目)", numOfStatus[ON_SALE]);
	outtextxy(l, t+(cnt++*th), tempStr);

	sprintf(tempStr, "     有 %d 本书似乎找到了新去处(已预定数目)", numOfStatus[RESERVED]);
	outtextxy(l, t+(cnt++*th), tempStr);

	sprintf(tempStr, "     有 %d 本书的原主人还在犹豫(已下架数目)", numOfStatus[REMOVED]);
	outtextxy(l, t+(cnt++*th), tempStr);

	sprintf(tempStr, "     有 %d 本书找到了新去处(已售数目)", numOfStatus[SOLD]);
	outtextxy(l, t+(cnt++*th), tempStr);



	sprintf(tempStr, "     有 %.2lf 元的资金流过此处(总交易金额)", amount);
	outtextxy(l, t+(cnt++*th), tempStr);

}

// 删除字符串的空格等无效字符
static void delSpaceOfStr(char* str) {
	int l = strlen(str);
	int diff = 0;
	for (int i = 0; i <= l; i++) {
		str[i - diff] = str[i];
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r') {
			diff++;
		}
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
				delSpaceOfStr(temp);
				strcpy(Str, temp);
				changed = true;
				circle = 0;
			} else {
				MessageBox(GetHWnd(), "输入不能为空", "提示", MB_OK | MB_ICONWARNING);
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
	ll temp_num = *num;
	char temp[1001] = "";
	do {
		circle = 1;
		if (InputBox(temp, 1000, InputBoxInfo, InputBoxTip, temp, 0, 0, false)) {
			if (sscanf(temp, "%lld", &temp_num) == 1 && temp_num > Invalid_Num) {
				*num = temp_num;
				circle = 0;
				changed = true;
			} else {
				MessageBox(GetHWnd(), "输入有误", "提示", MB_OK | MB_ICONWARNING);
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
	double temp_num = *num;
	char temp[1001] = "";
	do {
		circle = 1;
		if (InputBox(temp, 1000, InputBoxInfo, InputBoxTip, temp, 0, 0, false)) {
			if (sscanf(temp, "%lf", &temp_num) == 1 && temp_num > Invalid_Num - EPS) {
				*num = temp_num;
				circle = 0;
				changed = true;
			} else {
				MessageBox(GetHWnd(), "输入有误", "提示", MB_OK | MB_ICONWARNING);
				circle = 1;
			}
		} else {
			changed = false;
			circle = 0;
		}

	} while (circle);

	return changed;
}


bool InputDate(time_t* time, const char* InputBoxInfo, const char* InputBoxTip) {
	
	bool changed = false;	//默认未改动
	int circle = 1;


	time_t temp_time = *time;
	/*获取时间结构体,
	*主要是由于这里输入的时间只有年月日, 没法保证时间的精确度
	*所以让传入的时间作为除年月日外的结构体字段*/
	struct tm struct_time = *localtime(&temp_time);	

	int year, mon, day;
	char temp[1001] = "";
	do {
		circle = 1;

		circle = 1;
		if (InputBox(temp, 1000, InputBoxInfo, InputBoxTip, temp, 0, 0, false)) {
			if (sscanf(temp, "%d %d %d", &year, &mon, &day) == 3 && year < 3000 && year > 1970) {
				struct_time.tm_year = year - 1900;
				struct_time.tm_mon = mon - 1;
				struct_time.tm_mday = day;

				*time = mktime(&struct_time);

				circle = 0;
				changed = true;
			} else {
				MessageBox(GetHWnd(), "输入有误", "提示", MB_OK | MB_ICONWARNING);
				circle = 1;
			}
		} else {
			changed = false;
			circle = 0;
		}
	} while (circle);
	return changed;
}

/*一定会被修改*/
void changeBookCondition(BookCondition* condition) {

	cleardevice();
	int input_num = normalMenu(200, 90, 4, BookConditionStr, 100, 30, "返回", 20, "选择书籍的新旧程度", 30);
	switch (input_num) {

	case 1: *condition = NEW; break;

	case 2: *condition = LIKE_NEW; break;

	case 3: *condition = GOOD; break;

	case 4:	*condition = ACCEPTABLE; break;
	}
}

void changeBookCategory(BookCategory* category) {
	cleardevice();
	int input_num = normalMenu(200, 90, 5, BookCategoryStr, 100, 30, "返回", 20, "选择书籍类别", 30);
	switch (input_num) {
		case 1 : *category = TEXTBOOK; break;
		
		case 2 : *category = FICTION; break;

		case 3 : *category = ACADEMIC; break;
		
		case 4 : *category = EXAM; break;
		
		case 5 : *category = OTHER; break;

	}
}


bool changeUserKey(UserInfo* onlineUser) {
	if (!authenUserInfo(onlineUser)) {
		return false;
	}
	char temp_key[1001] = "";
	if (InputStr(temp_key, "输入新密码", "提示", 1000)) {
		generateSalt(onlineUser->salt, 12);
		generateHashKey(temp_key, onlineUser->salt, onlineUser->hashKey);
		return true;
	} else {
		return false;
	}
}


bool changeUserInfo(UserInfo* onlineUser) {
	UserInfo* temp_user = (UserInfo*)malloc(sizeof(UserInfo));
	memcpy(temp_user, onlineUser, sizeof(UserInfo));

	bool changed = false;

	int circle = 1;
	do {
		circle = 1;
		cleardevice();
		char selections[][101] = {"保存修改", "修改用户名", "修改电话", "修改QQ号", "修改微信号"};
		int input_num = detailUserInfoMenu(200, 90, 5, selections, 90, 30, "不保存退出", 20, "选择修改的信息", 10, "正在被修改的用户信息详情", temp_user, 10);
		switch (input_num) {
		case 0:
			if (MessageBox(GetHWnd(), "确认退出修改吗? 修改不会保存", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				circle = false;
				circle = 0;
			}
			break;

		case 1:
			memcpy(onlineUser, temp_user, sizeof(UserInfo));
			changed = true;
			circle = 0;

			break;
		case 2:
			InputStr(temp_user->name, "输入用户名\n\"一个好的名字能让别人更快的记住你\"", "输入", NAME_MAX_LEN - 3);

			break;

		case 3:
			InputInter(&(temp_user->tel), "输入电话", "输入");
			break;

		case 4:
			InputInter(&(temp_user->QQ), "输入QQ号", "输入");
			break;

		case 5:
			InputStr(temp_user->WeChat, "输入微信号", "输入", WECHAR_MAX_LEN - 1);

			break;
		}

	} while(circle);
	free(temp_user);

	return changed;
}





bool changeBookInfo(Book* book) {
	Book* temp_book = (Book*)malloc(sizeof(Book));
	memcpy(temp_book, book, sizeof(Book));
	bool changed = false;
	int circle = 1;
	do {
		circle = 1;
		cleardevice();

		char selections[][101] = {"保存修改", "书籍名称", "ISBN", "书籍作者", "书籍状态", "书籍类别", "书籍价格"};

		int input_num = detailBookMenu(200, 90, 7, selections, 100, 30, "退出修改", 20, "选择操作", 10, "正在被修改的书籍详情", temp_book, 10);

		switch (input_num) {
		case 0:
			if (MessageBox(GetHWnd(), "确认退出修改吗? 修改不会保存", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				changed = false;
				circle = 0;
			}
			break;

		case 1:
			memcpy(book, temp_book, sizeof(Book));		//把临时书籍信息复制回原来的书籍
			changed = true;
			circle = 0;

			break;

		case 2:
			InputStr(temp_book->title, "输入书籍名称", "输入", TITLE_MAX_LEN - 3);
			break;

		case 3:

			InputStr(temp_book->ISBN, "输入书籍ISBN", "输入", ISBN_MAX_LEN - 3);
			break;

		case 4:

			InputStr(temp_book->author, "输入书籍作者", "输入", AUTHOR_MAX_LEN - 3);
			break;

		case 5:

			changeBookCondition(&(temp_book->condition));
			break;

		case 6:
			changeBookCategory(&(temp_book->category));
			break;
		case 7:

			InputFloat(&(temp_book->price), "输入一个小数代表书籍价格", "输入价格");
			break;
		}

	} while (circle);
	free(temp_book);
	return changed;
}


void printUserInfoToFile(FILE* file, UserInfo* user) {
	if (user) {
		fprintf(file, "用户名: %s\n", user->name);
		fprintf(file, "学号: %lld\n", user->id);
		fprintf(file, "电话: %lld\n", user->tel);
		fprintf(file, "QQ: %lld\n", user->QQ);
		fprintf(file, "微信号: %s\n", user->WeChat);
	} else {
		fprintf(file, "无\n");
	}
}


void printTimeToFile(FILE* file, time_t time, const char* info) {
	tm structTime = *localtime(&time);
	int year = structTime.tm_year + 1900;
	int mon = structTime.tm_mon + 1;
	int day = structTime.tm_mday;
	int h = structTime.tm_hour;
	int m = structTime.tm_min;
	int s = structTime.tm_sec;
	fprintf(file, "%s: %d 年 %d 月 %d 日 %d 时 %d 分 %d 秒\n", info, year, mon, day, h, m, s);
}

void printBookInfoToFile(Book* book, const char* fileHeadName) {
	time_t nowTime = time(NULL);
	tm structTime = *localtime(&nowTime);
	char fileName[1001];
	/*文件名格式*/
	sprintf(fileName, "%s_%lld_%04d%02d%02d_%02d%02d%02d.txt", fileHeadName, book->id, 
											structTime.tm_year + 1900, 
											structTime.tm_mon + 1,
											structTime.tm_mday, 
											structTime.tm_hour,
											structTime.tm_min,
											structTime.tm_sec);
	FILE* file = fopen(fileName, "w");
	fprintf(file, "书名: %s\n", book->title);
	fprintf(file, "ISBN: %s\n", book->ISBN);
	fprintf(file, "作者: %s\n", book->author);
	fprintf(file, "价格: %.2lf 元\n", book->price);
	fprintf(file, "书籍状态: %s\n", BookStatusStr[book->status]);
	fprintf(file, "书籍新旧程度: %s\n", BookConditionStr[book->condition]);
	fprintf(file, "书籍类别: %s\n", BookCategoryStr[book->category]);

	fprintf(file, "\n书籍发布者信息:\n");
	printUserInfoToFile(file, book->seller);
	printTimeToFile(file, book->publishTime, "书籍发布时间");

	fprintf(file, "\n书籍预定者信息:\n");
	printUserInfoToFile(file, book->reserver);
	if (book->reserver) {
		printTimeToFile(file, book->reserveTime, "书籍预定时间");
	}


	fprintf(file, "\n书籍购买者信息:\n");
	printUserInfoToFile(file, book->buyer);
	if (book->buyer) {
		printTimeToFile(file, book->buyTime, "书籍购买时间");
	}



	fprintf(file, "BookEase@Flmpx");
	fclose(file);
	MessageBox(GetHWnd(), fileName, "文件已保存至程序所在目录下的:", MB_OK | MB_ICONINFORMATION);


}
