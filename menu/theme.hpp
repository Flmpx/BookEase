/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#ifndef BK_THEME_HPP_
#define BK_THEME_HPP_

namespace BK {
    namespace Theme {
        
        /* 普通块主题 */
        namespace NormalBlock {
            inline auto start() -> void {
                setfillcolor(RGB(250, 250, 252));
                setlinecolor(RGB(180, 190, 200));
                setlinestyle(PS_SOLID, 1);
            }
        }

        /* 提示块主题 */
        namespace TipBlock {
            inline auto start() -> void {
                setfillcolor(RGB(220, 235, 255));  
                setlinecolor(RGB(80, 130, 200));   
                setlinestyle(PS_SOLID, 1); 
            }
        }

        /* 引导信息块主题 */
        namespace InstruBlock {
            inline auto start() -> void {
                setfillcolor(RGB(220, 245, 240));  
                setlinecolor(RGB(70, 180, 170));   
                setlinestyle(PS_SOLID, 1);
            }
        }

        /* 返回块主题 */
        namespace BackBlock {
            inline auto start() -> void {
                setfillcolor(RGB(240, 240, 245));  
                setlinecolor(RGB(150, 160, 180)); 
                setlinestyle(PS_SOLID, 1);
            }

            inline auto hover() -> void {
                setfillcolor(RGB(225, 230, 240));  
                setlinecolor(RGB(120, 140, 180)); 
                setlinestyle(PS_SOLID, 1);
            }

            inline auto click() -> void {
                setfillcolor(RGB(210, 220, 235)); 
                setlinecolor(RGB(100, 120, 160));  
                setlinestyle(PS_SOLID, 1);
            }
        }

        /* 选项块主题 */
        namespace SelectBlock {
            inline auto start() -> void {
                setfillcolor(WHITE);
                setlinecolor(RGB(100, 150, 220));  
                setlinestyle(PS_SOLID, 1);
            }

            inline auto hover() -> void {
                setfillcolor(RGB(235, 245, 255));  
                setlinecolor(RGB(80, 140, 220));   
                setlinestyle(PS_SOLID, 2); 
            }

            inline auto click() -> void {
                setfillcolor(RGB(220, 235, 250));  
                setlinecolor(RGB(60, 130, 210)); 
                setlinestyle(PS_SOLID, 2);
            }
        }

        /* 翻页块主题 */
        namespace DictionBlock {
            inline auto start() -> void {
                setfillcolor(RGB(255, 250, 240)); 
                setlinecolor(RGB(220, 160, 80));   
                setlinestyle(PS_SOLID, 1);
            }

            inline auto hover() -> void {
                setfillcolor(RGB(255, 240, 220));  
                setlinecolor(RGB(210, 140, 60));   
                setlinestyle(PS_SOLID, 2);
            }

            inline auto click() -> void {
                setfillcolor(RGB(255, 230, 200));  
                setlinecolor(RGB(200, 120, 40));   
                setlinestyle(PS_SOLID, 2);
            }
        }

        /* 书籍块主题 */
        namespace BookBlock {
            inline auto start() -> void {
                setfillcolor(WHITE);
                setlinecolor(RGB(180, 200, 220));  
                setlinestyle(PS_SOLID, 1);
            }

            inline auto hover() -> void {
                setfillcolor(RGB(245, 250, 255));  
                setlinecolor(RGB(100, 150, 220));  
                setlinestyle(PS_SOLID, 2);
            }

            inline auto click() -> void {
                setfillcolor(RGB(235, 245, 255));  
                setlinecolor(RGB(80, 130, 200));   
                setlinestyle(PS_SOLID, 2);
            }
        }
    }
}

#endif