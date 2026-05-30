#ifndef LOGIN_H
#define LOGIN_H
#include "../../base.h"
#include "../../Lists/UserList/userlist.h"


extern void generateSalt(char* salt, int n);

extern ll hash(const char* str);

extern void generateHashKey(const char* key, const char* salt, char* hashKey);



/// @brief 验证用户信息
/// @param user 用户信息指针
/// @return 如果验证成功返回true, 如果退出验证返回false
extern bool authenUserInfo(UserInfo* user);

/// @brief 登录功能
/// @param users 用户信息链表
/// @return 如果登录成功返回登录用户指针, 如果登录失败返回空指针
extern UserInfo* loginFunc(UserList* users);

/// @brief 注册功能
/// @param users 用户信息链表
/// @return 如果注册成功返回1, 如果注册失败返回0
extern int registerFunc(UserList* users);

#endif
