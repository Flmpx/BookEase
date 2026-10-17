/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/


#include "menu.hpp"
#include "../tools/tools.hpp"
#include "theme.hpp"

#include <list>
#include <vector>

namespace BK {

    namespace Menu {

        /**
         * @brief 检测当前鼠标位置是否在块内
         * 
         * @param msg 消息
         * @param l 块左界
         * @param t 块右界
         * @param w 块宽度
         * @param h 块高度
         */
        auto isInBlock(const ExMessage& msg, int_t l, int_t t, int_t w, int_t h) -> bool {
            if (msg.x > l && msg.x < l + w && msg.y > t && msg.y < t + h) {
                return true;
            } else {
                return false;
            }
        }


        /**
         * @brief 输出普通菜单内容
         * 
         * @param back 返回块内容
         * @param instru 选项引导信息块内容
         * @param selections 全部选项块的内容
         * @param layout 普通菜单的布局
         * @return 返回 0 则为点击了返回键  
         * @return 1 为点击了第 1 个选项, 2 为第 2 个, 以此类推  
         */
        auto showNormal(const std::string& back, const std::string& instru, const std::vector<std::string>& selections, const Layout::Normal& layout) -> int_t {
            int_t l {0}, t {0}, w {0}, h {0};


            auto [back_w, back_h, grap_back_instru, instru_h, select_w, select_h] = layout;


            int_t instru_start_h {back_h + grap_back_instru};
            int_t select_start_h {instru_start_h + instru_h};

            ExMessage msg {0};

            std::vector<bool> click_flags(1 + selections.size(), 0);
            std::vector<bool> hover_flags(1 + selections.size(), 0);

            while (true) {
                /* 初始化标志 */
                click_flags.assign(click_flags.size(), false);
                hover_flags.assign(hover_flags.size(), false);

                msg = getmessage();

                /* 返回键检测 */
                l = 0, t = 0, w = back_w, h = back_h;
                if (isInBlock(msg, l, t, w, h)) {
                    hover_flags[0] = true;
                    if (msg.message == WM_LBUTTONDOWN) {
                        click_flags[0] = true;
                    }
                }

                /* 各选项检测 */
                l = 0, t = select_start_h, w = select_w, h = select_h * selections.size();
                if (isInBlock(msg, l, t, w, h)) {
                    hover_flags[(msg.y - select_start_h) / select_h + 1] = true;
                    if (msg.message == WM_LBUTTONDOWN) {
                        click_flags[(msg.y - select_start_h) / select_h + 1] = true;
                    }
                }


                /* 开始绘制 */
                
                BeginBatchDraw();
                {
                    /* 绘制Back键 */
                    Theme::BackBlock::start();
                    if (hover_flags[0]) Theme::BackBlock::hover();
                    if (click_flags[0]) Theme::BackBlock::click();

                    l = 0, t = 0, w = back_w, h = back_h;
                    Tools::Draw::roundRectleBlock(back, l, t, w, h);

                    /* 绘制引导信息 */
                    Theme::InstruBlock::start();

                    l = 0, t = instru_start_h, w = select_w, h = instru_h;
                    Tools::Draw::rectangleBlock(instru, l, t, w, h);

                    /* 绘制选项 */
                    for (int i = 0; i < selections.size(); i++) {
                        Theme::SelectBlock::start();
                        if (hover_flags[i + 1]) Theme::SelectBlock::hover();
                        if (click_flags[i + 1]) Theme::SelectBlock::click();

                        l = 0, t = select_start_h + select_h * i, w = select_w, h = select_h;
                        Tools::Draw::rectangleBlock(selections[i], l, t, w, h);
                    }
                }
                EndBatchDraw();

                /* 对点击行为作出反应 */
                for (int_t i = 0; i < click_flags.size(); i++) {
                    if (click_flags[i]) {
                        return i;
                    }
                }
            }
        }

        /**
         * @brief 输出显示书籍详细信息的菜单内容
         * 
         * @param back 返回块内容
         * @param instru 选项引导信息块内容
         * @param selections 全部选项块的内容
         * @param book_tip 书籍详细信息块的提示信息内容
         * @param book 书籍详细信息块的内容
         * @param layout 书籍详情菜单的布局
         * @param reveal_time 是否展示与时间有关的书籍信息
         * @return 返回 0 则为点击了返回键  
         * @return 1 为点击了第 1 个选项, 2 为第 2 个, 以此类推  
         */
        auto showBook(const std::string& back, const std::string& instru, const std::vector<std::string>& selections, const std::string& book_tip, const std::shared_ptr<Book>& book, const Layout::Book& layout, bool reveal_time) -> int_t {
            int_t screen_h {getheight()};
            int_t screen_w {getwidth()};
            int_t l {0}, t {0}, w {0}, h {0};

            auto [normal, grap_select_book] = layout;
            auto [back_w, back_h, grap_back_instru, instru_h, select_w, select_h] = normal;

            /* 绘制书籍详细信息块的提示信息块 */
            Theme::TipBlock::start();

            l = select_w + grap_select_book; t = 0; w = screen_w - l; h = back_h + grap_back_instru;
            Tools::Draw::roundRectleBlock(book_tip, l, t, w, h);

            /* 绘制书籍详细信息块 */
            Theme::NormalBlock::start();

            l = select_w + grap_select_book; t = back_h + grap_back_instru; w = screen_w - l; h = screen_h - t;
            Tools::Draw::roundRectleBlock("", l, t, w, h);
            Tools::Print::book(book, l, t, w, h, reveal_time);

            return showNormal(back, instru, selections, normal);
        }

        /**
         * @brief 输出显示用户详细信息的菜单内容
         * 
         * @param back 返回块内容
         * @param instru 选项引导信息块内容
         * @param selections 全部选项块的内容
         * @param user_tip 用户详细信息块的提示信息块
         * @param user 用户详细信息块的内容
         * @param layout 用户详情菜单的布局
         * @param reveal_time 是否展示与时间有关的用户信息
         * @return 返回 0 则为点击了返回键   
         * @return 1 为点击了第 1 个选项, 2 为第 2 个, 以此类推  
         */
        auto showUser(const std::string& back, const std::string& instru, const std::vector<std::string>& selections, const std::string& user_tip, const std::shared_ptr<User>& user, const Layout::User& layout, bool reveal_time) -> int_t {
            int_t screen_h {getheight()};
            int_t screen_w {getwidth()};
            int_t l {0}, t {0}, w {0}, h {0};

            auto [normal, grap_select_user] = layout;
            auto [back_w, back_h, grap_back_instru, instru_h, select_w, select_h] = normal;

            /* 绘制用户详细信息块的提示信息块 */
            Theme::TipBlock::start();

            l = select_w + grap_select_user; t = 0; w = screen_w - l; h = back_h + grap_back_instru;
            Tools::Draw::roundRectleBlock(user_tip, l, t, w, h);

            /* 绘制用户详细信息块 */
            Theme::NormalBlock::start();

            l = select_w + grap_select_user; t = back_h + grap_back_instru; w = screen_w - l; h = screen_h - t;
            Tools::Draw::roundRectleBlock("", l, t, w, h);
            Tools::Print::user(user, l, t, w, h, reveal_time);

            return showNormal(back, instru, selections, normal);
        }

        /**
         * @brief 输出显示统计信息的菜单内容
         * 
         * @param back 返回块内容
         * @param instru 选项引导信息块内容
         * @param selections 全部选项块的内容
         * @param statistics_tip 统计信息块的提示信息块
         * @param books 全部书籍信息
         * @param users 全部用户信息
         * @param layout 统计信息菜单的布局
         * @return 返回 0 则为点击了返回键  
         * @return 1 为点击了第 1 个选项, 2 为第 2 个, 以此类推  
         */
        auto showStatistics(const std::string& back, const std::string& instru, const std::vector<std::string>& selections, const std::string& statistics_tip, const std::list<std::shared_ptr<Book>>& books, const std::list<std::shared_ptr<User>>& users, const Layout::Statistics& layout) -> int_t {
            int_t screen_h {getheight()};
            int_t screen_w {getwidth()};
            int_t l {0}, t {0}, w {0}, h {0};

            auto [normal, grap_select_statistics] = layout;
            auto [back_w, back_h, grap_back_instru, instru_h, select_w, select_h] = normal;

            /* 绘制统计信息块的提示信息块 */
            Theme::TipBlock::start();

            l = select_w + grap_select_statistics; t = 0; w = screen_w - l; h = back_h + grap_back_instru;
            Tools::Draw::roundRectleBlock(statistics_tip, l, t, w, h);

            /* 绘制统计信息块 */
            Theme::NormalBlock::start();

            l = select_w + grap_select_statistics; t = back_h + grap_back_instru; w = screen_w - l; h = screen_h - t;
            Tools::Draw::roundRectleBlock("", l, t, w, h);
            Tools::Print::statistics(books, users, l, t, w, h);

            return showNormal(back, instru, selections, normal);
        }

        /**
         * @brief 输出显示多书籍信息的菜单内容
         * 
         * @param back 返回块内容
         * @param instru 选项引导信息块内容
         * @param selections 全部选项块的内容
         * @param books_tip 多书籍信息块的提示信息块
         * @param books 书籍链表
         * @param layout 多书籍信息菜单的布局
         * @param now_index 从该下标所属页开始展示
         * @return 返回 0 则为点击了返回键  
         * @return 1 为点击了第 1 个选项, 2 为第 2 个, 以此类推  
         * @return -1 为点击了第 1 本书籍, -2 为第二本, 以此类推  
         */
        auto showBooks(const std::string& back, const std::string& instru, const std::vector<std::string>& selections, const std::string& books_tip, const std::list<std::shared_ptr<Book>>& books, const Layout::Books& layout, int_t now_index) -> int_t {
            int_t l {0}, t {0}, w {0}, h {0};
            int_t screen_h {getheight()};
            int_t screen_w {getwidth()};

            auto [normal, diction_w, diction_h, grap_select_books, row, col] = layout;
            auto [back_w, back_h, grap_back_instru, instru_h, select_w, select_h] = normal;

            int_t instru_start_h {back_h + grap_back_instru};
            int_t select_start_h {instru_start_h + instru_h};
            int_t books_start_h {instru_start_h};
            int_t books_start_w {select_w + grap_select_books};
            int_t book_w {(screen_w - books_start_w) / col};
            int_t book_h {(screen_h - books_start_h) / row};

            ExMessage msg {0};

            std::vector<int> click_flags_select(1 + selections.size()); 
            std::vector<int> click_flags_dir(2);
            std::vector<int> click_flags_book(row * col);

            std::vector<int> hover_flags_select(1 + selections.size());
            std::vector<int> hover_flags_dir(2);
            std::vector<int> hover_flags_book(row * col);

            if (books.size() == 0) {
                now_index = 0;
            } else if (now_index >= books.size()) {
                now_index = books.size() - 1;
            }
            int_t book_now_num {(now_index / (row * col)) * (row * col) };
            
            auto book_now {books.begin()};
            for (int_t i = 0; i < book_now_num; i++) {
                book_now++;
            }

            while (true) {
                /* 初始化标志 */
                click_flags_select.assign(click_flags_select.size(), false);
                click_flags_dir.assign(click_flags_dir.size(), false);
                click_flags_book.assign(click_flags_book.size(), false);

                hover_flags_select.assign(hover_flags_select.size(), false);
                hover_flags_dir.assign(hover_flags_dir.size(), false);
                hover_flags_book.assign(hover_flags_book.size(), false);

                msg = getmessage();

                /* 返回键检测 */
                l = 0, t = 0, w = back_w, h = back_h;
                if (isInBlock(msg, l, t, w, h)) {
                    hover_flags_select[0] = true;
                    if (msg.message == WM_LBUTTONDOWN) {
                        click_flags_select[0] = true;
                    }
                }

                /* 各选项检测 */
                l = 0, t = select_start_h, w = select_w, h = select_h * selections.size();
                if (isInBlock(msg, l, t, w, h)) {
                    hover_flags_select[(msg.y - select_start_h) / select_h + 1] = true;
                    if (msg.message == WM_LBUTTONDOWN) {
                        click_flags_select[(msg.y - select_start_h) / select_h + 1] = true;
                    }
                }

                /* 切换键检测 */
                {
                    /* <<< */
                    l = 0; t = screen_h - diction_h; w = diction_w; h = diction_h;
                    if (isInBlock(msg, l, t, w, h)) {
                        hover_flags_dir[0] = true;
                        if (msg.message == WM_LBUTTONDOWN) {
                            click_flags_dir[0] = true;
                        }
                    }
                    
                    /* >>> */
                    l = select_w - diction_w; t = screen_h - diction_h; w = diction_w; h = diction_h;
                    if (isInBlock(msg, l, t, w, h)) {
                        hover_flags_dir[1] = true;
                        if (msg.message == WM_LBUTTONDOWN) {
                            click_flags_dir[1] = true;
                        }
                    }
                }

                /* 书籍区域检测 */
                l = select_w + grap_select_books; t = books_start_h; w = screen_w - l; h = screen_h - t;
                if (isInBlock(msg, l, t, w, h)) {
                    int_t loc {(msg.y - books_start_h) / book_h * col + (msg.x - books_start_w) / book_w };
                    if (loc < books.size() - book_now_num) {
                        hover_flags_book[loc] = true;
                        if (msg.message == WM_LBUTTONDOWN) {
                            click_flags_book[loc] = true;
                        }
                    }
                }

                /* 开始绘制 */
                BeginBatchDraw();
                {
                    cleardevice();      // 绘制之前先清屏, 书籍的信息会变动

                    /* 绘制Back键 */
                    Theme::BackBlock::start();
                    if (hover_flags_select[0]) Theme::BackBlock::hover();
                    if (click_flags_select[0]) Theme::BackBlock::click();

                    l = 0, t = 0, w = back_w, h = back_h;
                    Tools::Draw::roundRectleBlock(back, l, t, w, h);

                    /* 绘制引导信息 */
                    Theme::InstruBlock::start();

                    l = 0, t = instru_start_h, w = select_w, h = instru_h;
                    Tools::Draw::rectangleBlock(instru, l, t, w, h);

                    /* 绘制选项 */
                    for (int i = 0; i < selections.size(); i++) {
                        Theme::SelectBlock::start();
                        if (hover_flags_select[i + 1]) Theme::SelectBlock::hover();
                        if (click_flags_select[i + 1]) Theme::SelectBlock::click();

                        l = 0, t = select_start_h + select_h * i, w = select_w, h = select_h;
                        Tools::Draw::rectangleBlock(selections[i], l, t, w, h);
                    }

                    /* 绘制方向键 */
                    {
                        /* <<< */
                        Theme::DictionBlock::start();
                        if (hover_flags_dir[0]) Theme::DictionBlock::hover();
                        if (click_flags_dir[0]) Theme::DictionBlock::click();

                        l = 0; t = screen_h - diction_h; w =diction_w; h = diction_h;
                        Tools::Draw::rectangleBlock("<<<", l, t, w, h);
                        
                        /* >>> */
                        Theme::DictionBlock::start();
                        if (hover_flags_dir[1]) Theme::DictionBlock::hover();
                        if (click_flags_dir[1]) Theme::DictionBlock::click();

                        l = select_w - diction_w; t = screen_h - diction_h; w = diction_w; h = diction_h;
                        Tools::Draw::rectangleBlock(">>>", l, t, w, h);
                    }

                    /* 绘制书籍提示信息 */
                    Theme::TipBlock::start();

                    l = books_start_w; t = 0; w = screen_w - l; h = books_start_h;
                    Tools::Draw::roundRectleBlock(books_tip, l, t, w, h);

                    /* 绘制书籍信息 */
                    auto book_tmp {book_now};
                    for (uint_t i = 0; i < col * row && i < books.size() - book_now_num; i++, book_tmp++) {
                        Theme::BookBlock::start();
                        if (hover_flags_book[i]) Theme::BookBlock::hover();
                        if (click_flags_book[i]) Theme::BookBlock::click();

                        l = books_start_w + (i % col) * book_w;
                        t = books_start_h + (i / col) * book_h;
                        w = book_w; h = book_h;
                        Tools::Draw::roundRectleBlock("", l, t, w, h);
                        Tools::Print::book(*book_tmp, l, t, w, h);
                    }
                }
                EndBatchDraw();

                /* 对点击行为作出反应 */
                {
                    /* 返回键+选项 */
                    for (int_t i = 0; i < click_flags_select.size(); i++) {
                        if (click_flags_select[i]) {
                            return i;
                        }
                    }

                    /* 书籍 */
                    for (int_t i = 0; i < click_flags_book.size(); i++) {
                        if (click_flags_book[i]) {
                            return -(book_now_num + i + 1);
                        }
                    }

                    /* 方向键 */
                    {
                        if (click_flags_dir[0]) {   /* <<< */
                            if (book_now_num - col * row >= 0) {
                                for (int_t i = 0; i < col * row; i++) {
                                    book_now--;
                                }
                                book_now_num -= col * row;
                            } else {
                                MessageBox(GetHWnd(), "已经是开始页了!!!", "提示", MB_OK | MB_ICONINFORMATION);
                            }
                        } else if (click_flags_dir[1]) {                    /* >>> */
                            if (book_now_num + col * row < books.size()) {
                                for (int_t i = 0; i < col * row; i++) {
                                    book_now++;
                                }
                                book_now_num += col * row;
                            } else {
                                MessageBox(GetHWnd(), "已经是最后一页了!!!", "提示", MB_OK | MB_ICONINFORMATION);
                            }
                        }
                    }
                }
            }
        }

        /**
         * @brief 画出单个选项块
         * 
         */
        auto Select::draw() const -> void {
            Tools::Draw::roundRectleBlock(tip, l, t, w, h);
        }
    
        /**
         * @brief 判断鼠标是否悬浮在选项块区域
         * 
         * @param msg 消息
         */
        auto Select::isHover(const ExMessage& msg) const -> bool {
            return isInBlock(msg, l, t, w, h);
        }
    
        /**
         * @brief 判断鼠标是否点击了选项块
         * 
         * @param msg 消息
         */
        auto Select::isClick(const ExMessage& msg) const -> bool {
            return isHover(msg) && msg.message == WM_LBUTTONDOWN;
        }
    
    
        /**
         * @brief 输出多个块式选项
         * 
         * @param blocks 块式选项数组
         * @return 返回 0 代表点击了第 1 各, 1 代表第 2 各, 以此类推
         */
        auto showSelects(const std::vector<Select>& blocks) -> int_t {
            ExMessage msg {0};
    
            std::vector<bool> hover_flags(blocks.size());
            std::vector<bool> click_flags(blocks.size());
    
            while (true) {
                /* 清除标志位 */
                hover_flags.assign(hover_flags.size(), false);
                click_flags.assign(click_flags.size(), false);
    
                msg = getmessage();
    
                /* 检测 */
                for (int_t i = 0; i < blocks.size(); i++) {
                    if (blocks[i].isHover(msg)) {
                        hover_flags[i] = true;
                        if (blocks[i].isClick(msg)) {
                            click_flags[i] = true;
                        }
                    }
                }
    
                /* 绘制 */
                BeginBatchDraw();
                {
                    for (int_t i = 0; i < blocks.size(); i++) {
                        Theme::SelectBlock::start();
                        if (hover_flags[i]) Theme::SelectBlock::hover();
                        if (click_flags[i]) Theme::SelectBlock::click();
        
                        blocks[i].draw();
                    }
                }
                EndBatchDraw();
    
                /* 对点击行为作出反应 */
                for (int_t i = 0; i < blocks.size(); i++) {
                    if (click_flags[i]) {
                        return i;
                    }
                }
            }
        }
    }
}