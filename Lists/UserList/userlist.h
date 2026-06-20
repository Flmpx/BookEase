/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/
#ifndef USERLIST_H
#define USERLIST_H
#include "../../base.h"



/// @brief 用户信息节点, 存储用户信息指针
struct UserNode {
	UserNode* next;
	UserNode* prev;
	UserInfo* user;
};


/// @brief 用户信息List
struct UserList {
	UserNode* head;
	UserNode* tail;
	int size;
};


/// @brief 初始化用户信息链表
/// @param plist 链表指针
extern void initUserList(UserList* plist);

/// @brief 通过学号在用户信息链表中得到用户信息指针
/// @param plist 链表指针
/// @param id 学号
/// @return 用户信息指针
extern UserInfo* getPtrUserInfoByIdInUserList(UserList* plist, ll id);


/// @brief 插入用户信息指针到链表中(只是指针传递, 不会复制一份用户信息)
/// @param plist 链表指针
/// @param info 用户信息指针
/// @return 操作状态返回值
extern InfoOfReturn insertUserInfoInUserList(UserList* plist, UserInfo* info);



/// @brief 删除用户信息链表中用户信息节点(这不会删除用户信息)
/// @param plist 链表指针
/// @param id 学号
/// @return 操作状态返回值
extern InfoOfReturn delNodeByIdInUserList(UserList* plist, ll id);


/// @brief 用于释放主用户信息链表中的用户信息, 一般用于销户, 
/// @param plist 链表指针
/// @param id 学号
/// @return 操作状态返回值
extern InfoOfReturn delUserInfoInUserList(UserList* plist, ll id);





/// @brief 释放用户信息链表(只释放链表, 不释放用户信息数据)
/// @param plist 链表指针
extern void freeUserList(UserList* plist);

/// @brief 释放用户信息链表(同时释放用户信息, 用于程序终止时)
/// @param plist 链表指针
extern void deepFreeUserList(UserList* plist);

#endif

