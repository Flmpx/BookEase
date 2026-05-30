#include "userlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//为了方便, 这里的插入只进行尾插, 其他插入根本用不到
//这里只是管理用户信息的指针, 内部不会存储用户信息的副本



/*
		!!!用户信息链表一般只有一个, 特殊情况除外

*/

void initUserList(UserList* plist) {
	plist->head = plist->tail = NULL;
	plist->size = 0;
}

static UserNode* getNodeByIdInUserList(UserList* plist, ll id) {
	UserNode* p = plist->head;
	while (p) {
		if (p->user->id == id) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

UserInfo* getPtrUserInfoByIdInUserList(UserList* plist, ll id) {
	UserNode* p = getNodeByIdInUserList(plist, id);
	if (p) {
		return p->user;
	} else {
		return NULL;
	}
}

InfoOfReturn insertUserInfoInUserList(UserList* plist, UserInfo* info) {
	if (info == NULL) {
		printf("传入信息无效\n");
		return Warning;
	}
	UserNode* newNode = (UserNode*)malloc(sizeof(UserNode));
	if (newNode == NULL) {
		printf("内存分配失败");
		return Warning;
	}
	

	//初始化新节点
	newNode->next = NULL;
	newNode->prev = plist->tail;
	newNode->user = info;

	if (plist->size) {
		plist->tail->next = newNode;
		plist->tail = newNode;
	} else {
		plist->head = plist->tail = newNode;
	}

	plist->size++;
	return Success;
}



static InfoOfReturn delStartNodeInUserList(UserList* plist) {
	UserNode* p = plist->head;

	if (plist->size > 1) {
		plist->head = plist->head->next;
		plist->head->prev = NULL;
	} else {
		plist->head = plist->tail = NULL;
	}

	free(p);
	plist->size--;
	return Success;
}

static InfoOfReturn delEndNodeInUserList(UserList* plist) {
	UserNode* p = plist->tail;

	if (plist->size > 1) {
		plist->tail = plist->tail->prev;
		plist->tail->next = NULL;
	} else {
		plist->head = plist->tail = NULL;
	}

	free(p);
	plist->size--;
	return Success;

}


InfoOfReturn delNodeByIdInUserList(UserList* plist, ll id) {
	UserNode* p = getNodeByIdInUserList(plist, id);
	if (p == NULL) return None;
	if (p == plist->head) return delStartNodeInUserList(plist);
	if (p == plist->tail) return delEndNodeInUserList(plist);

	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(p);
	plist->size--;
	return Success;
}

InfoOfReturn delUserInfoInUserList(UserList* plist, ll id) {
	UserNode* p = getNodeByIdInUserList(plist, id);
	if (p == NULL) return None;

	
	free(p->user);


	if (p == plist->head) return delStartNodeInUserList(plist);
	if (p == plist->tail) return delEndNodeInUserList(plist);

	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(p);
	plist->size--;
	return Success;
	
}



void freeUserList(UserList* plist) {
	UserNode* p = plist->head;
	UserNode* q = NULL;
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
	initUserList(plist);
}

void deepFreeUserList(UserList* plist) {
	UserNode* p = plist->head;
	UserNode* q = NULL;
	while (p) {
		q = p;
		p = p->next;
		free(q->user);
		free(q);
	}
	initUserList(plist);
}

