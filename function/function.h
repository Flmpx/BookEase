#ifndef FUNCTION_H
#define FUNCTION_H
#include "../base.h"
#include "../Lists/UserList/userlist.h"
#include "../Lists/BookList/booklist.h"

/// @brief 将书籍信息里面的售卖者, 购买者和预约者的信息位置建立联系
/// @param book 书籍指针
/// @param plist 用户信息链表(一般为主用户信息链表)
/// @return 操作状态码
extern InfoOfReturn linkBookForUser(Book* book, UserList* plist);



/// @brief 在一个矩形中打印用户信息
/// @param info 信息指针
/// @param l 矩形左边界
/// @param t 矩形上边界
/// @param w 矩形宽度
/// @param h 矩形高度
/// @note 一般为当前登录的用户信息
extern void printUserInfo(UserInfo* info, int l, int t, int w, int h);

/// @brief 在一个矩形中打印书籍的简单信息
/// @param book 书籍指针
/// @param l 矩形左边界
/// @param t 矩形上边界
/// @param w 矩形宽度
/// @param h 矩形高度
extern void printSimpleBookInfo(Book* book, int l, int t, int w, int h);


/// @brief 在一个矩形中打印书籍的全部信息
/// @param book 书籍指针
/// @param l 矩形左边界
/// @param t 矩形上边界
/// @param w 矩形宽度
/// @param h 矩形高度
extern void printAllBookInfo(Book* book, int l, int t, int w, int h);


extern void printStatistics(UserList* mainUserList, BookList* mainBookList, int l, int t, int w, int h);

/*
* 下面三个函数是用于输入的
*/

extern bool InputStr(char* Str, const char* InputBoxInfo, const char* InputBoxTip, int maxLen);


extern bool InputInter(ll* num, const char* InputBoxInfo, const char* InputBoxTip);


extern bool InputFloat(double* num, const char* InputBoxInfo, const char* InputBoxTip);

extern bool InputDate(time_t* time, const char* InputBoxInfo, const char* InputBoxTip);

/*
*	下面是改变一些内容的
*
*/

extern void changeBookCategory(BookCategory* category);

extern void changeBookCondition(BookCondition* condition);


extern bool changeUserKey(UserInfo* onlineUser);

extern bool changeUserInfo(UserInfo* onlineUser);


extern bool changeBookInfo(Book* book);






extern void printBookInfoToFile(Book* book, const char* fileHeadName);

#endif
