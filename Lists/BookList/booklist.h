#ifndef BOOKLIST_H
#define BOOKLIST_H
#include "../../base.h"


/// @brief 书籍信息节点
struct BookNode {
	BookNode* prev;
	BookNode* next;
	Book* book;
};


/// @brief 书籍链表
struct BookList {
	BookNode* head;
	BookNode* tail;
	int size;
};

/// @brief 初始化书籍链表
/// @param plist 链表指针
extern void initBookList(BookList* plist);


/// @brief 插入书籍指针到书籍链表中
/// @param plist 链表指针
/// @param book 书籍指针
/// @return 操作状态码
extern InfoOfReturn insertBookInBookList(BookList* plist, Book* book);


/// @brief 通过书籍id在书籍链表中获得书籍指针
/// @param plist 链表指针
/// @param id 书籍id
/// @return 书籍指针, 若不存在返回空指针
extern Book* getPtrBookByIdInBookList(BookList* plist, ll id);


/// @brief 通过书籍id删除书籍链表中节点(不会清除书籍信息)
/// @param plist 链表指针
/// @param id 书籍id
/// @return 操作状态码
extern InfoOfReturn delNodeByIdInBookList(BookList* plist, ll id);


/// @brief 通过书籍id删除书籍链表中节点和书籍信息
/// @param plist 链表指针
/// @param id 书籍id
/// @return 操作状态码
extern InfoOfReturn delBookInBookList(BookList* plist, ll id);


/// @brief 释放书籍链表(不会释放书籍信息)
/// @param plist 链表指针
extern void freeBookList(BookList* plist);


/// @brief 释放书籍链表(书籍信息同步释放, 一般用于程序终止时)
/// @param plist 链表指针
extern void deepFreeBookList(BookList* plist);


/// @brief 得到主书籍信息链表中符合要求的书籍链表
/// @param allBookList 主书籍链表
/// @param bookCondition 书籍条件
/// @return 符合要求的的书籍链表, 使用完请使用freeBookList函数释放
extern BookList getSimilarBookListInAllBookList(BookList* allBookList, BookCmpCondition* bookCondition);

#endif
