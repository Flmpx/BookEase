#include "login.h"
#include "../../base.h"
#include "../../Lists/UserList/userlist.h"
#include "../../function/function.h"
#include <easyx.h>
#include "../saveandload/saveandload.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
//输入密码要判空, 学号不需要, 空学号也无法转化为数字


static ll mod = 100000000009;
static ll base = 131;


void generateSalt(char* salt, int n) {
	srand(time(NULL));
	const char* flag = "ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()<>{}|";
	int len = strlen(flag);
	int i;
	for (i = 0; i < n; i++) {
		salt[i] = flag[rand()%len];
	}
	salt[i] = '\0';
}


ll hash(const char* str) {
	int len = strlen(str);
	ll res = 0;
	for (int i = 0; i < len; i++) {
		res = (res*base + str[i]*99 + 171) % mod;
	}
	return res;
}



void generateHashKey(const char* key, const char* salt, char* hashKey) {
	char temp[1001];
	sprintf(temp, "%s%s", key, salt);
	ll hashNum = hash(temp);
	sprintf(hashKey, "%llx", hashNum);


}


bool authenUserInfo(UserInfo* user) {
	int circle = 0;
	int res;
	char tempHashKey[1001] = "";
	char temp[1001] = "";
	do {
		circle = 1;

		if (InputStr(temp, "请输入登录密码", "输入用户信息", 1000)) {
			generateHashKey(temp, user->salt, tempHashKey);
			if (strcmp(tempHashKey, user->hashKey) == 0) {
				res = 1;
				circle = 0;
				MessageBox(GetHWnd(), "认证成功", "提示", MB_OK);


			} else {
				circle = 1;
				MessageBox(GetHWnd(), "认证失败, 请重试", "提示", MB_OK);
			}
		} else {
			res = 0;
			circle = 0;
		}
	} while (circle);
	return res;
}

UserInfo* loginFunc(UserList* users) {
	ll id;
	int res;
	int circle;
	UserInfo* user = NULL;
	do {
		circle = 1;
		if (InputInter(&id, "请输入学号", "输入用户信息")) {
			user = getPtrUserInfoByIdInUserList(users, id);	//通过用户链表获得当前用户的信息
			if (user) {
				//用户存在
				if (authenUserInfo(user)) {
					//验证成功就退出循环
					circle = 0;
				} else {
					//验证失败就把user重设为NULL, 循环继续
					user = NULL;
					circle = 1;
				}
			} else {
				//如果输入有误或用户不存在, 弹出提示
				MessageBox(GetHWnd(), "用户不存在, 检查是否输入错误或者进行注册", "提示", MB_OK);
				circle = 1;
			}
		} else {
			//取消输入
			res = 0;
			circle = 0;
		}

	} while (circle);
	//返回登录用户, 如果登录不成功返回NULL
	return user;
}

static UserInfo* createUser(ll id) {
	UserInfo* user = NULL;
	char temp[1001] = "";
	int circle;
	do {
		
		circle = 1;
		if (InputStr(temp, "请输入密码", "输入用户信息", 1000)) {
			user = (UserInfo*)malloc(sizeof(UserInfo));
			*user = getEmptyUserInfo();
			generateSalt(user->salt, 12);
			generateHashKey(temp, user->salt, user->hashKey);
			user->id = id;
			sprintf(user->name, "%lld", user->id);
			user->registerTime = time(NULL);
			circle = 0;
		} else {
			circle = 0;
			user = NULL;
		}	
	} while (circle);
	return user;
}


int registerFunc(UserList* users) {
	int circle = 0;
	char temp[1001] = "";
	ll id;
	int res;
	UserInfo* user;
	do {
		circle = 1;
		
		if (InputInter(&id, "请输入学号", "输入用户信息")) {
			user = getPtrUserInfoByIdInUserList(users, id);
			if (user) {
				res = 0;
				circle = 0;
				MessageBox(GetHWnd(), "当前用户已注册, 请前往登录", "提示", MB_OK);

			} else {
				user = createUser(id);
				if (user) {
					insertUserInfoInUserList(users, user);
					saveUserListToFile(users, "Data/userinfo.txt");
					MessageBox(GetHWnd(), "注册成功, 请前往登录", "提示", MB_OK);
					res = 1;
					circle = 0;
				} else {
					circle = 1;
				}
			}
		} else {
			res = 0;
			circle = 0;
		}		
	} while (circle);
	return res;
}


