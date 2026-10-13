/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "../tools.hpp"
#include <easyx.h>

namespace BK {

    namespace Tools {

        namespace Draw {

            /**
             * @brief 画一个直角块
             * 
             * @param text 文本
             * @param l 块左界
             * @param t 块右界
             * @param w 块宽度
             * @param h 块高度
             */
            auto rectangleBlock(const std::string& text, int_t l, int_t t, int_t w, int_t h) -> void {
                int_t tw {textwidth(text.c_str())};
                int_t th {textheight(text.c_str())};
        
                fillrectangle(l, t, l + w, t + h);
                outtextxy(l + (w - tw) / 2, t + (h - th) / 2, text.c_str());
            }
        
            /**
             * @brief 画一个圆角块
             * 
             * @param text 文本
             * @param l 块左界
             * @param t 块右界
             * @param w 块宽度
             * @param h 块高度
             */
            auto roundRectleBlock(const std::string& text, int_t l, int_t t, int_t w, int_t h) -> void {
                int_t tw {textwidth(text.c_str())};
                int_t th {textheight(text.c_str())};
        
                fillroundrect(l, t, l + w, t + h, 10, 10);
                outtextxy(l + (w - tw) / 2, t + (h - th) / 2, text.c_str());
            }

        }
    }
}