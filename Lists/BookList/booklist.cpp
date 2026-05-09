#include "booklist.h"
#include <stdio.h>
#include <stdlib.h>
#include "../UserList/userlist.h"
#include <string.h>

void initBookList(BookList* plist) {
	plist->head = plist->tail = NULL;
	plist->size = 0;
}

InfoOfReturn insertBookInBookList(BookList* plist, Book* book) {
	if (book == NULL) {
		printf("传入信息无效\n");
		return Warning;
	}
	
	BookNode* newNode = (BookNode*)malloc(sizeof(BookNode));

	if (newNode == NULL) {
		printf("内存分配失败");
		return Warning;
	}
	newNode->book = book;	//只是传指针
	newNode->prev = plist->tail;
	newNode->next = NULL;

	if (plist->size) {
		plist->tail->next = newNode;
		plist->tail = newNode;
	} else {
		plist->head = plist->tail = newNode;
	}

	plist->size++;
	return Success;

}


static BookNode* getNodeByIdInBookList(BookList* plist, ll id) {
	BookNode* p = plist->head;
	while (p) {
		if (p->book->id == id) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

Book* getPtrBookByIdInBookList(BookList* plist, ll id) {
	BookNode* p = getNodeByIdInBookList(plist, id);
	if (p) {
		return p->book;
	} else {
		return NULL;
	}
}


BookList getSimilarBookListInAllBookList(BookList* allBookList, BookCmpCondition* bookCondition) {
	BookList similarBookList;
	initBookList(&similarBookList);
	BookNode* p = allBookList->head;
	while (p) {
		if (isSimilarBook(p->book, bookCondition) == true) {
			insertBookInBookList(&similarBookList, p->book);
		}
		p = p->next;
	}
	return similarBookList;
}

static InfoOfReturn delStartNodeInBookList(BookList* plist) {
	BookNode* p = plist->head;

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


static InfoOfReturn delEndNodeInBookList(BookList* plist) {
	BookNode* p = plist->tail;

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

InfoOfReturn delNodeByIdInBookList(BookList* plist, ll id) {
	BookNode* p = getNodeByIdInBookList(plist, id);
	if (p == NULL) return None;
	if (p == plist->head) return delStartNodeInBookList(plist);
	if (p == plist->tail) return delEndNodeInBookList(plist);

	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(p);
	plist->size--;
	return Success;
}

InfoOfReturn delBookInBookList(BookList* plist, ll id) {
	BookNode* p = getNodeByIdInBookList(plist, id);
	if (p == NULL) return None;


	free(p->book);


	if (p == plist->head) return delStartNodeInBookList(plist);
	if (p == plist->tail) return delEndNodeInBookList(plist);

	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(p);
	plist->size--;
	return Success;

}




void freeBookList(BookList* plist) {
	BookNode* p = plist->head;
	BookNode* q = NULL;
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
	initBookList(plist);
}

void deepFreeBookList(BookList* plist) {
	BookNode* p = plist->head;
	BookNode* q = NULL;
	while (p) {
		q = p;
		p = p->next;
		free(q->book);
		free(q);
	}
	initBookList(plist);
}

