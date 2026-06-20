/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/
#ifndef DETAILMENU_H
#define DETAILMENU_H
#include "../../base.h"
#include "../../Lists/BookList/booklist.h"
#include "../../Lists/UserList/userlist.h"

/// @brief 显示详细用户信息的菜单
/// @param selectW 选项宽度
/// @param selectH 选项高度
/// @param selectNum 选项数目
/// @param selections 选项内容
/// @param backW 返回键宽度
/// @param backH 返回键高度
/// @param back 返回键内容
/// @param instruH 引导信息高度(宽度与选项一致)
/// @param instruction 引导信息内容
/// @param grapInbcAndInsrtru 返回键和引导信息的间距
/// @param infoTips 用户信息提示信息
/// @param info 用户信息指针
/// @param grapInSeleAndInfo 选项和用户信息之间的距离
/// @return 返回0代表点击了返回键, 1代表点击了第一个选项
int detailUserInfoMenu(int selectW, int selectH, int selectNum, char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInstru, const char* infoTips, UserInfo* info, int grapInSeleAndInfo);



/// @brief 显示详细书籍信息的菜单
/// @param selectW 选项宽度
/// @param selectH 选项高度
/// @param selectNum 选项数目
/// @param selections 选项内容
/// @param backW 返回键宽度
/// @param backH 返回键高度
/// @param back 返回键内容
/// @param instruH 引导信息高度(宽度与选项一致)
/// @param instruction 引导信息内容
/// @param grapInbcAndInsrtru 返回键和引导信息的间距
/// @param infoTips 书籍信息的提示信息
/// @param book 书籍指针
/// @param grapInSeleAndBook 选项和书籍信息之间的距离 
/// @return 返回0代表点击了返回键, 1代表点击了第一个选项
int detailBookMenu(int selectW, int selectH, int selectNum, char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInstru, const char* infoTips, Book* book, int grapInSeleAndBook);


/// @brief 显示详细统计信息的菜单
/// @param selectW 选项宽度
/// @param selectH 选项高度
/// @param selectNum 选项数目
/// @param selections 选项内容
/// @param backW 返回键宽度
/// @param backH 返回键高度
/// @param back 返回键内容
/// @param instruH 引导信息高度(宽度与选项一致)
/// @param instruction 引导信息内容
/// @param grapInbcAndInsrtru 返回键和引导信息的间距
/// @param infoTips 统计信息的提示信息
/// @param mainBookList 主书籍链表
/// @param mainUserList 主用户链表
/// @param grapInSeleAndStatistics 选项和统计信息之间的距离 
/// @return 返回0代表点击了返回键, 1代表点击了第一个选项
extern int detailStatisticsMenu(int selectW, int selectH, int selectNum, char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInstru, const char* infoTips, BookList* mainBookList, UserList* mainUserList, int grapInSeleAndStatistics);
#endif
