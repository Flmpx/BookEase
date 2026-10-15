/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#ifndef BK_MENU_HPP_
#define BK_MENU_HPP_

#include <easyx.h>
#include "../base/base.hpp"
#include <list>
#include <vector>
#include <string>

namespace BK {


    namespace Menu {

        auto isInBlock(const ExMessage& msg, int_t l, int_t t, int_t w, int_t h) -> bool;

        /* 布局 */
        namespace Layout {

            /* 普通菜单布局 */
            struct Normal {
                int_t back_w;                       // 返回块宽度
                int_t back_h;                       // 返回块高度
                int_t grap_back_instru;             // 引导信息块与返回块的间隔(宽度和选项一致)
                int_t instru_h;                     // 引导信息块高度
                int_t select_w;                     // 单个选项块宽度
                int_t select_h;                     // 单个选项块宽度
            };
            constexpr Normal NormalGen {100, 30, 10, 20, 200, 90};           // 普通菜单的一般布局

            /* 书籍详情菜单布局 */
            struct Book {
                Normal normal;                      // 菜单基础布局
                int_t grap_select_book;             // 书籍详情块与选项块之间的间隔
            };
            constexpr Book BookGen {NormalGen, 10};                         // 书籍详情菜单的一般布局
            
            /* 用户详情菜单布局 */
            struct User {
                Normal normal;                      // 菜单基础布局
                int_t grap_select_user;             // 用户详情块与选项块之间的间隔
            };
            constexpr User UserGen {NormalGen, 10};                         // 用户详情菜单的一般布局
            
            /* 统计信息菜单布局 */
            struct Statistics {
                Normal normal;                      // 菜单基础布局
                int_t grap_select_statistics;       // 统计信息块与选项块之间的间隔
            };
            constexpr Statistics StatisticsGen {NormalGen, 10};             // 统计信息菜单的一般布局
            
            /* 多书籍菜单布局 */
            struct Books {
                Normal normal;                      // 菜单基础布局
                int_t diction_w;                    // 翻页块的宽度
                int_t diction_h;                    // 翻页块的高度
                int_t grap_select_books;            // 多书籍块与选项块之间的间隔
                int_t row;                          // 多书籍块单页的行数
                int_t col;                          // 多书籍块单页的块数
            };
            constexpr Books BooksGen {NormalGen, 40, 40, 10, 3, 2};         // 多书籍菜单布局的一般布局

        }
        

        auto showNormal(const std::string& back, const std::string& instru, const std::vector<std::string>& selections, const Layout::Normal& layout) -> int_t;
        auto showBook(const std::string& back, const std::string& instru, const std::vector<std::string>& selections, const std::string& book_tip, const std::shared_ptr<Book>& book, const Layout::Book& layout, bool reveal_time = false) -> int_t;
        auto showUser(const std::string& back, const std::string& instru, const std::vector<std::string>& selections, const std::string& user_tip, const std::shared_ptr<User>& user, const Layout::User& layout, bool reveal_time = false) -> int_t;
        auto showStatistics(const std::string& back, const std::string& instru, const std::vector<std::string>& selections, const std::string& statistics_tip, const std::list<std::shared_ptr<Book>>& books, const std::list<std::shared_ptr<User>>& users, const Layout::Statistics& layout) -> int_t;
        auto showBooks(const std::string& back, const std::string& instru, const std::vector<std::string>& selections, const std::string& books_tip, const std::list<std::shared_ptr<Book>>& books, const Layout::Books& layout, int_t now_index = 0) -> int_t;


        /* 块式选项 */
        struct Select {
            int_t l, t;
            int_t w, h;
            std::string tip;
    
            auto draw() const -> void;
            auto isClick(const ExMessage& msg) const -> bool;
            auto isHover(const ExMessage& msg) const -> bool;
        };
    
        auto showSelects(const std::vector<Select>& blocks) -> int_t;
    }

    
}
#endif