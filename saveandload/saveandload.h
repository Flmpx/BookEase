#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H
#include "../base.h"
#include "../Lists/BookList/booklist.h"
#include "../Lists/UserList/userlist.h"

/// @brief 通过文件加载用户信息链表(程序启动是启用)
/// @param filePath 文件路径
/// @return 用户信息链表
extern UserList loadUserListFromFile(const char* filePath);



/// @brief 保存用户信息链表到文件
/// @param plist 链表指针
/// @param filePath 文件路径
/// @return 操作状态返回值
extern InfoOfReturn saveUserListToFile(UserList* plist, const char* filePath);


/// @brief 从文件加载书籍信息到书籍链表中(用于程序启动, 会链接书籍和用户信息)
/// @param filePath 文件路径
/// @param plist 为了使书籍中的购买者等与用户信息指针建立联系, 需传入userList指针
/// @return 书籍链表
extern BookList loadBookListFromFile(const char* filePath, UserList* plist);


/// @brief 保存书籍链表到文件
/// @param plist 链表指针
/// @param filePath 文件路径
/// @return 操作状态返回值
extern InfoOfReturn saveBookListToFile(BookList* plist, const char* filePath);

#endif

