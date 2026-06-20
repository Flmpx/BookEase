/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/
#ifndef NORMALMENU_H
#define NORMALMENU_H


/// @brief 普通选项菜单
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
/// @return 返回0代表点击了返回键, 1代表点击了第一个选项
extern int normalMenu(int selectW, int selectH, int selectNum, char selections[][101], int backW, int backH, const char* back, int instruH, const char* instruction, int grapInbcAndInstru);

#endif
