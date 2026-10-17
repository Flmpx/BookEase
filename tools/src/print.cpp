/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "../tools.hpp"

#include <easyx.h>

namespace BK {

    namespace Tools {

        namespace Print {

            namespace {
                constexpr int_t NUM_USER_INFO {5};          // 用户基础信息的条数
                constexpr int_t NUM_BOOK_INFO {9};          // 书籍基础信息的条数
        
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
            }
        
            /**
             * @brief 输出用户信息到窗口(文字上下居中, 左右居左)
             * 
             * @param user 用户
             * @param l 左界
             * @param t 上界
             * @param w 宽度
             * @param h 高度
             * @param reveal_time 是否展示与时间有关的信息
             */
            auto user(const std::shared_ptr<User>& user, int_t l, int_t t, int_t w, int_t h, bool reveal_time) -> void {
                int_t info_num {NUM_USER_INFO};
        
                /* 只有展示时间的时候开启 */
                if (reveal_time) {
                    info_num++;
                }
        
                int_t th {h / info_num};
                int_t cnt {0};
        
                print("     用户名:", user->name, l, t + th * cnt++, w, th);    
                print("     用户ID:", user->id, l, t + th * cnt++, w, th);
                print("     电话:", user->tel, l, t + th * cnt++, w, th);
                print("     QQ:", user->qq, l, t + th * cnt++, w, th);
                print("     微信号:", user->wechat, l, t + th * cnt++, w, th);
        
                /* 只有展示时间的时候开启 */
                if (reveal_time) {
                    print("     注册时间:", user->register_time, l, t + th * cnt++, w, th);
                }
            }
        
            /**
             * @brief 输出书籍信息到窗口(文字上下居中, 左右居左)
             * 
             * @param book 书籍
             * @param l 左界
             * @param t 上界
             * @param w 宽度
             * @param h 高度
             * @param reveal_time 是否展示与时间有关的信息
             */
            auto book(const std::shared_ptr<Book>& book, int_t l, int_t t, int_t w, int_t h, bool reveal_time) -> void {
                int_t info_num {NUM_BOOK_INFO};
        
                /* 只有展示时间的时候开启 */
                if (reveal_time) {
                    switch (book->status) {
                        case BookStatus::on_sale: info_num += 1; break;
                        case BookStatus::removed: info_num += 1; break;
                        case BookStatus::reserved: info_num += 2; break;
                        case BookStatus::sold: info_num += 2; break;
                    }
                }
        
                int_t th {h / info_num};
                int_t cnt {0};
        
                print("     ID:", book->id, l, t + th * cnt++, w, th);     
                print("     书名:", book->title, l, t + th * cnt++, w, th);
                print("     作者:", book->author, l, t + th * cnt++, w, th);
                print("     出版社:", book->press, l, t + th * cnt++, w, th);
                print("     ISBN:", book->isbn, l, t + th * cnt++, w, th);
                print("     价格:", book->price, l, t + th * cnt++, w, th);
                print("     书籍完整度:", book->integrity, l, t + th * cnt++, w, th);
                print("     书籍类别:", getBookCategoryString(static_cast<BookCategory>(book->category)), l, t + th * cnt++, w, th);
                print("     书籍状态:", getBookStatusString(static_cast<BookStatus>(book->status)), l, t + th * cnt++, w, th);
        
                /* 只有展示时间的时候开启 */
                if (reveal_time) {
                    switch (book->status) {
                        case BookStatus::on_sale:
                            print("     发布时间: ", book->publish_time, l, t + th * cnt++, w, th);
                            break;
                        case BookStatus::removed: 
                            print("     下架时间: ", book->removed_time, l, t + th * cnt++, w, th);
                            break;
                        case BookStatus::reserved: 
                            print("     发布时间: ", book->publish_time, l, t + th * cnt++, w, th);
                            print("     预定时间: ", book->reserve_time, l, t + th * cnt++, w, th);
                            break;
                        case BookStatus::sold:
                            print("     发布时间: ", book->publish_time, l, t + th * cnt++, w, th);
                            print("     购买时间: ", book->buy_time, l, t + th * cnt++, w, th);
                            break;
                    }
                }
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
            auto statistics(const std::list<std::shared_ptr<Book>>& books, const std::list<std::shared_ptr<User>>& users, int_t l, int_t t, int_t w, int_t h) -> void {
                int_t info_num {8};
                int_t th {h / info_num};
                
                Time release_time {};
                release_time.set(time_t(1778935434));
                print("     软件发布时间: ", release_time, l, t, w, th);           // 第一个的高度要从t开始
                print("     总用户数:", users.size(), l, t += th, w, th);
                print("     总书籍数目:", books.size(), l, t += th, w, th);
        
                int_t num_on_sale {0}, num_reserved {0}, num_removed {0}, num_sold {0};
                Price all_price(int_t(0));
        
                for (auto& it : books) {
                    switch (static_cast<BookStatus>(it->status)) {
                        case BookStatus::on_sale:   num_on_sale++;  break;
                        case BookStatus::reserved:  num_reserved++; break;
                        case BookStatus::removed:   num_removed++;  break;
                        case BookStatus::sold:      num_sold++;     break;
                    }
                    if (it->status == BookStatus::sold) all_price += it->price;
                }
        
                print("     在售书籍数目:", num_on_sale, l, t += th, w, th);
                print("     已被预定书籍数目:", num_reserved, l, t += th, w, th);
                print("     下架书籍数目:", num_removed, l, t += th, w, th);
                print("     已交易书籍数目:", num_sold, l, t += th, w, th);
                print("     总交易金额:", all_price, l, t += th, w, th);
            }
        }
    }
}