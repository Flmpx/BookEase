#include "tools.hpp"
#include <sstream>
#include <ctime>

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
}