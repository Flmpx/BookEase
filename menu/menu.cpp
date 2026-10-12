/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "menu.hpp"
#include <list>
#include <vector>
#include "../tools/tools.hpp"
#include "theme.hpp"

namespace BK {

    /**
     * @brief 构建一个菜单的基础信息
     * 
     * @param back_w 返回块宽度
     * @param back_h 返回块高度
     * @param back_content 返回块内容
     * @param grap_back_instru 返回块与选项引导信息块之间的间隔
     * @param instru_h 选项引导信息块的高度(宽度与选项一致)
     * @param instru 选项引导信息块内容
     * @param select_w 单个选项块的宽度
     * @param select_h 单个选项块的高度
     */
    Menu::Menu(int_t back_w, int_t back_h, const std::string& back_content, int_t grap_back_instru, int_t instru_h, const std::string& instru, int_t select_w, int_t select_h)
    : back_w_(back_w), back_h_(back_h), back_content_(back_content), grap_back_instru_(grap_back_instru), instru_h_(instru_h), instru_(instru), select_w_(select_w), select_h_(select_h) 
    {}

    /**
     * @brief 输出普通菜单内容
     * 
     * @param selections 全部选项块的内容
     * @return 返回 0 则为点击了返回键  
     * @return 1 为点击了第 1 个选项, 2 为第 2 个, 以此类推  
     */
    auto Menu::showNormal(const std::vector<std::string>& selections) const -> int_t {
        int_t l {0}, t {0}, w {0}, h {0};

        int_t instru_start_h {back_h_ + grap_back_instru_};
        int_t select_start_h {instru_start_h + instru_h_};

        ExMessage msg {0};

        std::vector<bool> click_flags(1 + selections.size(), 0);
        std::vector<bool> hover_flags(1 + selections.size(), 0);

        while (true) {
            /* 初始化标志 */
            click_flags.assign(click_flags.size(), false);
            hover_flags.assign(hover_flags.size(), false);

            msg = getmessage();

            /* 返回键检测 */
            l = 0, t = 0, w = back_w_, h = back_h_;
            if (isInBlock(msg, l, t, w, h)) {
                hover_flags[0] = true;
                if (msg.message == WM_LBUTTONDOWN) {
                    click_flags[0] = true;
                }
            }

            /* 各选项检测 */
            l = 0, t = select_start_h, w = select_w_, h = select_h_ * selections.size();
            if (isInBlock(msg, l, t, w, h)) {
                hover_flags[(msg.y - select_start_h) / select_h_ + 1] = true;
                if (msg.message == WM_LBUTTONDOWN) {
                    click_flags[(msg.y - select_start_h) / select_h_ + 1] = true;
                }
            }


            /* 开始绘制 */
            
            BeginBatchDraw();
            {
                /* 绘制Back键 */
                Theme::BackBlock::start();
                if (hover_flags[0]) Theme::BackBlock::hover();
                if (click_flags[0]) Theme::BackBlock::click();

                l = 0, t = 0, w = back_w_, h = back_h_;
                getRoundRectleBlock(back_content_, l, t, w, h);

                /* 绘制引导信息 */
                Theme::InstruBlock::start();

                l = 0, t = instru_start_h, w = select_w_, h = instru_h_;
                getRectangleBlock(instru_, l, t, w, h);

                /* 绘制选项 */
                for (int i = 0; i < selections.size(); i++) {
                    Theme::SelectBlock::start();
                    if (hover_flags[i + 1]) Theme::SelectBlock::hover();
                    if (click_flags[i + 1]) Theme::SelectBlock::click();

                    l = 0, t = select_start_h + select_h_ * i, w = select_w_, h = select_h_;
                    getRectangleBlock(selections[i], l, t, w, h);
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
     * @param selections 全部选项块的内容
     * @param grap_select_book 书籍详细信息块与选项块之间的间隔
     * @param book_tip 书籍详细信息块的提示信息内容
     * @param book 书籍详细信息块的内容
     * @param reveal_time 是否展示与时间有关的书籍信息
     * @return 返回 0 则为点击了返回键  
     * @return 1 为点击了第 1 个选项, 2 为第 2 个, 以此类推  
     */
    auto Menu::showBook(const std::vector<std::string>& selections, int_t grap_select_book, const std::string& book_tip, const std::shared_ptr<Book>& book, bool reveal_time) const -> int_t {
        int_t screen_h {getheight()};
        int_t screen_w {getwidth()};
        int_t l {0}, t {0}, w {0}, h {0};

        /* 绘制书籍详细信息块的提示信息块 */
        Theme::TipBlock::start();

        l = select_w_ + grap_select_book; t = 0; w = screen_w - l; h = back_h_ + grap_back_instru_;
        getRoundRectleBlock(book_tip, l, t, w, h);

        /* 绘制书籍详细信息块 */
        Theme::NormalBlock::start();

        l = select_w_ + grap_select_book; t = back_h_ + grap_back_instru_; w = screen_w - l; h = screen_h - t;
        getRoundRectleBlock("", l, t, w, h);
        printBook(book, l, t, w, h, reveal_time);

        return showNormal(selections);
    }

    /**
     * @brief 输出显示用户详细信息的菜单内容
     * 
     * @param selections 全部选项块的内容
     * @param grap_select_user 用户详细信息块与选项块之间的间隔
     * @param user_tip 用户详细信息块的提示信息块
     * @param user 用户详细信息块的内容
     * @param reveal_time 是否展示与时间有关的用户信息
     * @return 返回 0 则为点击了返回键   
     * @return 1 为点击了第 1 个选项, 2 为第 2 个, 以此类推  
     */
    auto Menu::showUser(const std::vector<std::string>& selections, int_t grap_select_user, const std::string& user_tip, const std::shared_ptr<User>& user, bool reveal_time) const -> int_t {
        int_t screen_h {getheight()};
        int_t screen_w {getwidth()};
        int_t l {0}, t {0}, w {0}, h {0};

        /* 绘制用户详细信息块的提示信息块 */
        Theme::TipBlock::start();

        l = select_w_ + grap_select_user; t = 0; w = screen_w - l; h = back_h_ + grap_back_instru_;
        getRoundRectleBlock(user_tip, l, t, w, h);

        /* 绘制用户详细信息块 */
        Theme::NormalBlock::start();

        l = select_w_ + grap_select_user; t = back_h_ + grap_back_instru_; w = screen_w - l; h = screen_h - t;
        getRoundRectleBlock("", l, t, w, h);
        printUser(user, l, t, w, h, reveal_time);

        return showNormal(selections);
    }

    /**
     * @brief 输出显示统计信息的菜单内容
     * 
     * @param selections 全部选项块的内容
     * @param grap_select_statistics 统计信息块与选项块之间的间隔
     * @param statistics_tip 统计信息块的提示信息块
     * @param books 全部书籍信息
     * @param users 全部用户信息
     * @return 返回 0 则为点击了返回键  
     * @return 1 为点击了第 1 个选项, 2 为第 2 个, 以此类推  
     */
    auto Menu::showStatistics(const std::vector<std::string>& selections, int_t grap_select_statistics, const std::string& statistics_tip, const std::list<std::shared_ptr<Book>>& books, const std::list<std::shared_ptr<User>>& users) const -> int_t {
        int_t screen_h {getheight()};
        int_t screen_w {getwidth()};
        int_t l {0}, t {0}, w {0}, h {0};

        /* 绘制统计信息块的提示信息块 */
        Theme::TipBlock::start();

        l = select_w_ + grap_select_statistics; t = 0; w = screen_w - l; h = back_h_ + grap_back_instru_;
        getRoundRectleBlock(statistics_tip, l, t, w, h);

        /* 绘制统计信息块 */
        Theme::NormalBlock::start();

        l = select_w_ + grap_select_statistics; t = back_h_ + grap_back_instru_; w = screen_w - l; h = screen_h - t;
        getRoundRectleBlock("", l, t, w, h);
        printStatistics(books, users, l, t, w, h);

        return showNormal(selections);
    }    

    /**
     * @brief 输出显示多书籍信息的菜单内容
     * 
     * @param selections 全部选项块的内容
     * @param diction_w 方向块宽度
     * @param diction_h 方向块高度
     * @param grap_select_books 多书籍信息块与选项块之间的间隔
     * @param books_tip 多书籍信息块的提示信息块
     * @param row 显示的书籍行数
     * @param col 显示的书籍列数
     * @param books 书籍链表
     * 
     * @return 返回 0 则为点击了返回键  
     * @return 1 为点击了第 1 个选项, 2 为第 2 个, 以此类推  
     * @return -1 为点击了第 1 本书籍, -2 为第二本, 以此类推  
     */
    auto Menu::showBooks(const std::vector<std::string>& selections, int_t diction_w, int_t diction_h, int_t grap_select_books, const std::string& books_tip, int_t row, int col, const std::list<std::shared_ptr<Book>>& books) const -> int_t {
        int_t l {0}, t {0}, w {0}, h {0};

        int_t screen_h {getheight()};
        int_t screen_w {getwidth()};
        int_t instru_start_h {back_h_ + grap_back_instru_};
        int_t select_start_h {instru_start_h + instru_h_};
        int_t books_start_h {instru_start_h};
        int_t books_start_w {select_w_ + grap_select_books};
        int_t book_w {(screen_w - books_start_w) / col};
        int_t book_h {(screen_h - books_start_h) / row};

        ExMessage msg {0};

        std::vector<int> click_flags_select(1 + selections.size()); 
        std::vector<int> click_flags_dir(2);
        std::vector<int> click_flags_book(row * col);

        std::vector<int> hover_flags_select(1 + selections.size());
        std::vector<int> hover_flags_dir(2);
        std::vector<int> hover_flags_book(row * col);

        int_t book_now_num {0};
        auto book_now {books.begin()};

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
            l = 0, t = 0, w = back_w_, h = back_h_;
            if (isInBlock(msg, l, t, w, h)) {
                hover_flags_select[0] = true;
                if (msg.message == WM_LBUTTONDOWN) {
                    click_flags_select[0] = true;
                }
            }

            /* 各选项检测 */
            l = 0, t = select_start_h, w = select_w_, h = select_h_ * selections.size();
            if (isInBlock(msg, l, t, w, h)) {
                hover_flags_select[(msg.y - select_start_h) / select_h_ + 1] = true;
                if (msg.message == WM_LBUTTONDOWN) {
                    click_flags_select[(msg.y - select_start_h) / select_h_ + 1] = true;
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
                l = select_w_ - diction_w; t = screen_h - diction_h; w = diction_w; h = diction_h;
                if (isInBlock(msg, l, t, w, h)) {
                    hover_flags_dir[1] = true;
                    if (msg.message == WM_LBUTTONDOWN) {
                        click_flags_dir[1] = true;
                    }
                }
            }

            /* 书籍区域检测 */
            l = select_w_ + grap_select_books; t = books_start_h; w = screen_w - l; h = screen_h - t;
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

                l = 0, t = 0, w = back_w_, h = back_h_;
                getRoundRectleBlock(back_content_, l, t, w, h);

                /* 绘制引导信息 */
                Theme::InstruBlock::start();

                l = 0, t = instru_start_h, w = select_w_, h = instru_h_;
                getRectangleBlock(instru_, l, t, w, h);

                /* 绘制选项 */
                for (int i = 0; i < selections.size(); i++) {
                    Theme::SelectBlock::start();
                    if (hover_flags_select[i + 1]) Theme::SelectBlock::hover();
                    if (click_flags_select[i + 1]) Theme::SelectBlock::click();

                    l = 0, t = select_start_h + select_h_ * i, w = select_w_, h = select_h_;
                    getRectangleBlock(selections[i], l, t, w, h);
                }

                /* 绘制方向键 */
                {
                    /* <<< */
                    Theme::DictionBlock::start();
                    if (hover_flags_dir[0]) Theme::DictionBlock::hover();
                    if (click_flags_dir[0]) Theme::DictionBlock::click();

                    l = 0; t = screen_h - diction_h; w =diction_w; h = diction_h;
                    getRectangleBlock("<<<", l, t, w, h);
                    
                    /* >>> */
                    Theme::DictionBlock::start();
                    if (hover_flags_dir[1]) Theme::DictionBlock::hover();
                    if (click_flags_dir[1]) Theme::DictionBlock::click();

                    l = select_w_ - diction_w; t = screen_h - diction_h; w = diction_w; h = diction_h;
                    getRectangleBlock(">>>", l, t, w, h);
                }

                /* 绘制书籍提示信息 */
                Theme::TipBlock::start();

                l = books_start_w; t = 0; w = screen_w - l; h = books_start_h;
                getRoundRectleBlock(books_tip, l, t, w, h);

                /* 绘制书籍信息 */
                auto book_tmp {book_now};
                for (uint_t i = 0; i < col * row && i < books.size() - book_now_num; i++, book_tmp++) {
                    Theme::BookBlock::start();
                    if (hover_flags_book[i]) Theme::BookBlock::hover();
                    if (click_flags_book[i]) Theme::BookBlock::click();

                    l = books_start_w + (i % col) * book_w;
                    t = books_start_h + (i / col) * book_h;
                    w = book_w; h = book_h;
                    getRoundRectleBlock("", l, t, w, h);
                    printBook(*book_tmp, l, t, w, h);
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
    auto Selection::draw() const -> void {
        getRoundRectleBlock(tip, l, t, w, h);
    }

    /**
     * @brief 判断鼠标是否悬浮在选项块区域
     * 
     * @param msg 消息
     */
    auto Selection::isHover(const ExMessage& msg) const -> bool {
        return isInBlock(msg, l, t, w, h);
    }

    /**
     * @brief 判断鼠标是否点击了选项块
     * 
     * @param msg 消息
     */
    auto Selection::isClick(const ExMessage& msg) const -> bool {
        return isHover(msg) && msg.message == WM_LBUTTONDOWN;
    }


    /**
     * @brief 输出多个块式选项
     * 
     * @param blocks 块式选项数组
     * @return 返回 0 代表点击了第 1 各, 1 代表第 2 各, 以此类推
     */
    auto showSelections(const std::vector<Selection>& blocks) -> int_t {
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