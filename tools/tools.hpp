#ifndef BK_TOOLS_HPP_
#define BK_TOOLS_HPP_

#include "../base/base.hpp"
#include <easyx.h>
#include <sstream>

namespace BK {

    /**
     * @brief 输出文字到窗口(上下居中, 左右居左)
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
        std::stringstream tmp {};
        tmp << info << tp;

        std::string str(tmp.str());
        int_t th {textheight(str.c_str())};

        outtextxy(l, t + (h - th) / 2, str.c_str());
    }

    /**
     * @brief 输出时间到窗口(上下居中, 左右居左)
     * 
     * @tparam  时间
     * @param info 前缀信息
     * @param tp 时间
     * @param l 左界
     * @param t 上界
     * @param w 宽度
     * @param h 高度
     */
    template <>
    inline auto print<time_t>(const std::string& info, const time_t& tp, int_t l, int_t t, int_t w, int_t h) -> void {
        std::stringstream tmp {};
        if (tp >= 0) {
            struct tm time {};
            localtime_s(&time, &tp);

            tmp << info << time.tm_year + 1900 << "-" << time.tm_mon + 1 << "-" << time.tm_mday;
        } else {
            tmp << "None";
        }

        std::string str(tmp.str());
        int_t th {textheight(str.c_str())};

        outtextxy(l, t + (h - th) / 2, str.c_str());
    }

    auto isInBlock(const ExMessage& msg, int_t l, int_t t, int_t w, int_t h) -> bool;
    auto getRectangleBlock(const std::string& text, int_t l, int_t t, int_t w, int_t h) -> void;
    auto getRoundRectleBlock(const std::string& text, int_t l, int_t t, int_t w, int_t h) -> void;

    auto printUser(const std::shared_ptr<User>& user, int_t l, int_t t, int_t w, int_t h) -> void;
    auto printBook(const std::shared_ptr<Book>& book, int_t l, int_t t, int_t w, int_t h) -> void;
    auto printStatistics(const std::list<std::shared_ptr<Book>>& books, const std::list<std::shared_ptr<User>>& users, int_t l, int_t t, int_t w, int_t h) -> void;

    namespace Input {
        constexpr uint_t BUF_SIZE {256};
        auto string(std::string& s, const std::string& info, const std::string tip) -> bool;
        auto integer(int_t& i, const std::string& info, const std::string& tip) -> bool;
        auto floatPoint(float_t& f, const std::string& info, const std::string& tip) -> bool;
        auto date(time_t& t, const std::string& info, const std::string& tip) -> bool;
    }
}


#endif