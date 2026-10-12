/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#ifndef BK_TOOLS_HPP_
#define BK_TOOLS_HPP_

#include "../base/base.hpp"
#include <easyx.h>
#include <sstream>

namespace BK {

    /**
     * @brief 输出单行文字到窗口(上下居中, 左右居左)
     * 
     * @tparam T 类型
     * @param info 前缀信息
     * @param tp 信息
     * @param l 左界
     * @param t 上界
     * @param w 宽度
     * @param h 高度
     */
    template <typename T>
    inline auto print(const std::string& info, const T& tp, int_t l, int_t t, int_t w, int_t h) -> void {
        std::string str {info + std::to_string(tp)};
        int_t th {textheight(str.c_str())};

        outtextxy(l, t + (h - th) / 2, str.c_str());
    }
    
    template <>
    inline auto print<std::string>(const std::string& info, const std::string& tp, int_t l, int_t t, int_t w, int_t h) -> void {
        std::string str {info + tp};
        int_t th {textheight(str.c_str())};

        outtextxy(l, t + (h - th) / 2, str.c_str());
    }


    auto isInBlock(const ExMessage& msg, int_t l, int_t t, int_t w, int_t h) -> bool;
    auto getRectangleBlock(const std::string& text, int_t l, int_t t, int_t w, int_t h) -> void;
    auto getRoundRectleBlock(const std::string& text, int_t l, int_t t, int_t w, int_t h) -> void;

    auto printUser(const std::shared_ptr<User>& user, int_t l, int_t t, int_t w, int_t h, bool reveal_time = false) -> void;
    auto printBook(const std::shared_ptr<Book>& book, int_t l, int_t t, int_t w, int_t h, bool reveal_time = false) -> void;
    auto printStatistics(const std::list<std::shared_ptr<Book>>& books, const std::list<std::shared_ptr<User>>& users, int_t l, int_t t, int_t w, int_t h) -> void;

        
    auto input(std::string& s, const std::string& info, const std::string tip, const Range<uint_t> r = Range<uint_t>()) -> bool;
    auto input(int_t& i, const std::string& info, const std::string& tip, const Range<int_t> r = Range<int_t>()) -> bool;
    auto input(float_t& f, const std::string& info, const std::string& tip, const Range<float_t> r = Range<float_t>()) -> bool;
    auto input(Time& t, const std::string& info, const std::string& tip, const Range<Time> r = Range<Time>()) -> bool;

    auto authenKey(const Key& user) -> bool;

    auto change(BookCategory& categroy) -> void;
    auto change(Key& key) -> bool;
    auto change(std::shared_ptr<User>& user) -> bool;
    auto change(std::shared_ptr<Book>& book) -> bool;
}


#endif