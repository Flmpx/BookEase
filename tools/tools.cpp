#include "tools.hpp"
#include <sstream>
#include <ctime>
#include <cstring>

namespace BK {

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
        if (msg.x >= l && msg.x <= l + w && msg.y >= t && msg.y <= t + h) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief 画一个直角块
     * 
     * @param text 文本
     * @param l 块左界
     * @param t 块右界
     * @param w 块宽度
     * @param h 块高度
     */
    auto getRectangleBlock(const std::string& text, int_t l, int_t t, int_t w, int_t h) -> void {
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
    auto getRoundRectleBlock(const std::string& text, int_t l, int_t t, int_t w, int_t h) -> void {
        int_t tw {textwidth(text.c_str())};
        int_t th {textheight(text.c_str())};

        fillroundrect(l, t, l + w, t + h, 10, 10);
        outtextxy(l + (w - tw) / 2, t + (h - th) / 2, text.c_str());
    }

    /**
     * @brief 输出用户信息到窗口(文字上下居中, 左右居左)
     * 
     * @param user 用户
     * @param l 左界
     * @param t 上界
     * @param w 宽度
     * @param h 高度
     */
    auto printUser(const std::shared_ptr<User>& user, int_t l, int_t t, int_t w, int_t h) -> void {
        int_t info_num {7};
        int_t th {h / info_num};
        
        print("     用户名:", user->name, l, t += th, w, h);
        print("     用户ID:", user->id, l, t += th, w, h);
        print("     电话:", user->tel, l, t += th, w, h);
        print("     QQ:", user->qq, l, t += th, w, h);
        print("     微信号:", user->wechat, l, t += th, w, h);
        print("     注册时间:", user->register_time, l, t += th, w, h);
    }

    /**
     * @brief 输出书籍信息到窗口(文字上下居中, 左右居左)
     * 
     * @param book 书籍
     * @param l 左界
     * @param t 上界
     * @param w 宽度
     * @param h 高度
     */
    auto printBook(const std::shared_ptr<Book>& book, int_t l, int_t t, int_t w, int_t h) -> void {
        int_t info_num {10};
        int_t th {h / info_num};

        print("     ID:", book->id, l, t += th, w, h);
        print("     书名:", book->title, l, t += th, w, h);
        print("     作者:", book->author, l, t += th, w, h);
        print("     出版社:", book->press, l, t += th, w, h);
        print("     ISBN:", book->isbn, l, t += th, w, h);
        print("     价格:", book->price, l, t += th, w, h);
        print("     书籍完整度:", book->integrity, l, t += th, w, h);
        print("     书籍类别:", getBookCategoryString(static_cast<BookCategory>(book->category)), l, t += th, w, h);
        print("     书籍状态:", getBookStatusString(static_cast<BookStatus>(book->status)), l, t += th, w, h);
    }

    /**
     * @brief 输出统计信息到窗口(文字上下居中, 左右居左)
     * 
     * @param books 书籍链表
     * @param users 用户链表
     * @param l 左界
     * @param t 上界
     * @param w 宽度
     * @param h 高度
     */
    auto printStatistics(const std::list<std::shared_ptr<Book>>& books, const std::list<std::shared_ptr<User>>& users, int_t l, int_t t, int_t w, int_t h) -> void {
        const time_t release_time {1778935434};
        print("     软件发布时间", release_time, l, t, w, h);
        print("     总用户数:", users.size(), l, t, w, h);
        print("     总书籍数目:", books.size(), l, t, w, h);

        int_t num_on_sale {0}, num_reserved {0}, num_removed {0}, num_sold {0};
        float_t all_price {0.0};

        for (auto& it : books) {
            switch (static_cast<BookStatus>(it->status)) {
                case BookStatus::on_sale:   num_on_sale++;  break;
                case BookStatus::reserved:  num_reserved++; break;
                case BookStatus::removed:   num_removed++;  break;
                case BookStatus::sold:      num_sold++;     break;
            }
            all_price += it->price;
        }

        print("     在售书籍数目:", num_on_sale, l, t, w, h);
        print("     已被预定书籍数目:", num_reserved, l, t, w, h);
        print("     下架书籍数目:", num_removed, l, t, w, h);
        print("     已交易书籍数目:", num_sold, l, t, w, h);
        print("     总交易金额:", all_price, l, t, w, h);
    }

    namespace Input {

        /**
         * @brief 输入字符串
         * 
         * @param s 待输入的字符串
         * @param info 显示信息
         * @param tip 信息类型
         * @return 成功输入返回true, 取消输入返回false
         */
        auto string(std::string& s, const std::string& info, const std::string tip) -> bool {
            bool changed {false};
            int circle {1};

            char buf[BUF_SIZE] {""};
            std::snprintf(buf, BUF_SIZE, "%s", s.c_str());
            do {
                circle = 1;
                if (InputBox(buf, BUF_SIZE, info.c_str(), tip.c_str(), buf, 0, 0, false)) {
                    if (buf[0] != '\0') {
                        s = buf;
                        changed = true;
                        circle = 0;
                    } else {
                        MessageBox(GetHWnd(), "输入不能为空", "提示", MB_OK | MB_ICONWARNING);
                        circle = 1;
                    }
                } else {
                    circle = 0;
                    changed = false;
                }
            } while (circle);

            return changed;
        }

        /**
         * @brief 输入整数(不允许负数)
         * 
         * @param i 待输入的整数
         * @param info 显示信息
         * @param tip 信息类型
         * @return 成功输入返回 true, 取消输入返回 false
         */
        auto integer(int_t& i, const std::string& info, const std::string& tip) -> bool {
            bool changed {false};
            int circle {1};

            int_t tmp_num {0};
            char buf[BUF_SIZE] {""};
            std::snprintf(buf, BUF_SIZE, "%lld", i);
            do {
                circle = 1;
                if (InputBox(buf, BUF_SIZE, info.c_str(), tip.c_str(), buf, 0, 0, false)) {
                    int_t n {0};
                    if (std::sscanf(buf, "%lld%n", &tmp_num, &n) == 1 && buf[n] == '\0' && tmp_num >= 0) {
                        i = tmp_num;
                        circle = 0;
                        changed = true;
                    } else {
                        MessageBox(GetHWnd(), "输入数据异常", "提示", MB_OK | MB_ICONWARNING);
				        circle = 1;
                    }
                } else {
                    circle = 0;
                    changed = false;
                }
            } while (circle);

            return changed;
        }

        /**
         * @brief 输入浮点数(不允许负数)
         * 
         * @param i 待输入的浮点数
         * @param info 显示信息
         * @param tip 信息类型
         * @return 成功输入返回 true, 取消输入返回 false
         */
        auto floatPoint(float_t& f, const std::string& info, const std::string& tip) -> bool {
            bool changed {false};
            int circle {1};

            float_t tmp_num {0};
            char buf[BUF_SIZE] {""};
            std::snprintf(buf, BUF_SIZE, "%lf", f);
            do {
                circle = 1;
                if (InputBox(buf, BUF_SIZE, info.c_str(), tip.c_str(), buf, 0, 0, false)) {
                    int_t n {0};
                    if (std::sscanf(buf, "%lf%n", &tmp_num, &n) == 1 && buf[n] == '\0' && tmp_num >= -EPS) {
                        f = tmp_num;
                        circle = 0;
                        changed = true;
                    } else {
                        MessageBox(GetHWnd(), "输入数据异常", "提示", MB_OK | MB_ICONWARNING);
				        circle = 1;
                    }
                } else {
                    circle = 0;
                    changed = false;
                }
            } while (circle);

            return changed;
        }

        /**
         * @brief 输入日期(1970 < 年份 < 3000)
         * 
         * @param i 待输入的日期
         * @param info 显示信息
         * @param tip 信息类型
         * @return 成功输入返回 true, 取消输入返回 false
         */
        auto date(time_t& t, const std::string& info, const std::string& tip) -> bool {
            bool changed {false};
            int circle {1};

            int_t tmp_time {t > 0 ? t : 0};
            struct tm struct_time {};
            localtime_s(&struct_time, &tmp_time);
            char buf[BUF_SIZE] {""};
            std::snprintf(buf, BUF_SIZE, "%d %d %d", struct_time.tm_year, struct_time.tm_mon + 1, struct_time.tm_mday);
            int y {0}, m {0}, d {0};
            do {
                circle = 1;
                if (InputBox(buf, BUF_SIZE, info.c_str(), tip.c_str(), buf, 0, 0, false)) {
                    int_t n {0};
                    if (std::sscanf(buf, "%d%d%d%n", &y, &m, &d, &n) == 3 && buf[n] == '\0' && y < 3000 && y > 1970) {
                        struct_time.tm_year = y - 1900;
                        struct_time.tm_mon = m - 1;
				        struct_time.tm_mday = d;

                        t = mktime(&struct_time);
                        
                        circle = 0;
                        changed = true;
                    } else {
                        MessageBox(GetHWnd(), "输入数据异常", "提示", MB_OK | MB_ICONWARNING);
				        circle = 1;
                    }
                } else {
                    circle = 0;
                    changed = false;
                }
            } while (circle);

            return changed;
        }
    }
}