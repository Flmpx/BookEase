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




BookNode* getMid(BookNode* head) {
	if (!head || !(head->next)) {
		return head;
	}


	/*快慢指针法得到中间节点*/

	BookNode* fast = head->next;
	BookNode* slow = head;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;

}

BookNode* mergeTwoLists(BookNode* l1, BookNode* l2, cmpBook cmp) {
	BookNode dummy = {NULL, NULL, NULL};

	BookNode* tail = &dummy;

	while (l1 && l2) {
		int res = cmp(l1->book, l2->book);
		if (res <= 0) {
			tail->next = l1;
			l1->prev = tail;
			l1 = l1->next;
		} else {
			tail->next = l2;
			l2->prev = tail;
			l2 = l2->next;
		}
		tail = tail->next;
	}
	
	if (l1) {
		tail->next = l1;
		l1->prev = tail;
	} else {
		tail->next = l2;
		l2->prev = tail;
	}
	
	return dummy.next;

}



BookNode* sortBookNode(BookNode* head, cmpBook cmp) {

	if (!head || !head->next) {
		return head;
	}

	BookNode* mid = getMid(head);
	BookNode* r = mid->next;
	BookNode* l = head;
	mid->next = r->prev = NULL;

	r = sortBookNode(r, cmp);
	l = sortBookNode(l, cmp);

	BookNode* res = mergeTwoLists(l, r, cmp);
	res->prev = NULL;

	return res;
}

BookNode* getTail(BookNode* head) {
	if (!head) {
		return head;
	}

	while (head->next) {
		head = head->next;
	}

	return head;
}

void sortBookList(BookList* plist, cmpBook cmp) {
	plist->head = sortBookNode(plist->head, cmp);
	plist->tail = getTail(plist->head);
}



void initIterBookList(IterBookList* iter, BookList* list) {
	iter->next = list->head;
}


bool iterBookListHasNext(IterBookList* iter) {
	return iter->next != NULL;
}

Book* iterBookListNext(IterBookList* iter) {
	if (iter->next == NULL) {
		return NULL;
	}
	Book* ptrBook = iter->next->book;
	iter->next = iter->next->next;
	return ptrBook;
}
