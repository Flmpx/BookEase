#ifndef FUNCTION_H
#define FUNCTION_H
#include "../base.h"
#include "../Lists/UserList/userlist.h"

/// @brief 将书籍信息里面的售卖者, 购买者和预约者的信息位置建立联系
/// @param book 书籍指针
/// @param plist 用户信息链表(一般为主用户信息链表)
/// @return 操作状态码
extern InfoOfReturn linkBookForUser(Book* book, UserList* plist);


/// @brief 打印书籍的简单信息
/// @param book 书籍指针
/// @param x 左上角x
/// @param y 左上角y
/// @param width 宽度
/// @param height 高度
extern void printSimpleBookInfo(Book* book, int x, int y, int width, int height);


/// @brief 打印书籍的全部信息
/// @param book 书籍指针
/// @param x 左上角x
/// @param y 左上角y
/// @param width 宽度
/// @param height 高度
extern void printAllBookInfo(Book* book, int x, int y, int width, int height);

#endif
