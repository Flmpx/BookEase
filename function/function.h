#ifndef FUNCTION_H
#define FUNCTION_H
#include "../base.h"
#include "../Lists/UserList/userlist.h"

/// @brief 将书籍信息里面的售卖者, 购买者和预约者的信息位置建立联系
/// @param book 书籍指针
/// @param plist 用户信息链表(一般为主用户信息链表)
/// @return 操作状态码
extern InfoOfReturn linkBookForUser(Book* book, UserList* plist);


#endif
