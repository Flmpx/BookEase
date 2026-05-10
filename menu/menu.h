#ifndef MENU_H
#define MENU_H
#include <easyx.h>

/// @brief 得到文字在中间的直角矩形
/// @param text 文字内容
/// @param l 矩形左边界
/// @param t 矩形上边界
/// @param w 矩形宽度
/// @param h 矩形高度
extern void getRectangleBlock(const char* text, int l, int t, int w, int h);



/// @brief 得到文字在中间的圆角矩形
/// @param text 文字内容
/// @param l 矩形左边界
/// @param t 矩形上边界
/// @param w 矩形宽度
/// @param h 矩形高度
extern void getRoundRectleBlock(const char* text, int l, int t, int w, int h);

/// @brief 判断鼠标是否在矩形内部
/// @param msg 消息指针
/// @param l 矩形左边界
/// @param t 矩形上边界
/// @param w 矩形宽度
/// @param h 矩形高度
/// @return 如果在返回true, 否则false
extern bool isInBlock(ExMessage* msg, int l, int t, int w, int h);

#endif
