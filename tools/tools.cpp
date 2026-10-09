#include "tools.hpp"
#include <sstream>
#include <ctime>
#include <cstring>
#include "../menu/menu.hpp"

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
        if (msg.x > l && msg.x < l + w && msg.y > t && msg.y < t + h) {
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
        
        print("     用户名:", user->name, l, t, w, th);      // 第一个的高度要从t开始
        print("     用户ID:", user->id, l, t += th, w, th);
        print("     电话:", user->tel, l, t += th, w, th);
        print("     QQ:", user->qq, l, t += th, w, th);
        print("     微信号:", user->wechat, l, t += th, w, th);
        print("     注册时间:", user->register_time, l, t += th, w, th);
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
        int_t info_num {9};
        int_t th {h / info_num};

        print("     ID:", book->id, l, t, w, th);       // 第一个的高度要从t开始
        print("     书名:", book->title, l, t += th, w, th);
        print("     作者:", book->author, l, t += th, w, th);
        print("     出版社:", book->press, l, t += th, w, th);
        print("     ISBN:", book->isbn, l, t += th, w, th);
        print("     价格:", book->price, l, t += th, w, th);
        print("     书籍完整度:", book->integrity, l, t += th, w, th);
        print("     书籍类别:", getBookCategoryString(static_cast<BookCategory>(book->category)), l, t += th, w, th);
        print("     书籍状态:", getBookStatusString(static_cast<BookStatus>(book->status)), l, t += th, w, th);
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
        int_t info_num {8};
        int_t th {h / info_num};
        
        const time_t release_time {1778935434};
        print("     软件发布时间", release_time, l, t, w, h);           // 第一个的高度要从t开始
        print("     总用户数:", users.size(), l, t + th, w, h);
        print("     总书籍数目:", books.size(), l, t += th, w, h);

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

        print("     在售书籍数目:", num_on_sale, l, t += th, w, h);
        print("     已被预定书籍数目:", num_reserved, l, t += th, w, h);
        print("     下架书籍数目:", num_removed, l, t += th, w, h);
        print("     已交易书籍数目:", num_sold, l, t += th, w, h);
        print("     总交易金额:", all_price, l, t += th, w, h);
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

    /**
     * @brief 验证用户密码
     * 
     * @param user 用户
     */
    auto authenUser(std::shared_ptr<User>& user) -> bool {
        int circle {0};
        std::string password {};
        bool res {false};
        do {
            circle = 1;
            if (Input::string(password, "请输入登录密码", "输入用户信息")) {
                if (user->key.verify(password)) {
                    circle = 0;
                    res = true;
                    MessageBox(GetHWnd(), "认证成功", "提示", MB_OK | MB_ICONINFORMATION);
                } else {
                    circle = 1;
                    MessageBox(GetHWnd(), "认证失败, 请重试", "提示", MB_OK | MB_ICONWARNING);
                }

            } else {
                circle = 0;
                res = false;
            }
        } while (circle);

        return res;
    }

    namespace Change {

        /**
         * @brief 修改书籍的类别(必定会被修改)
         * 
         * @param category 类别
         */
        auto bookCategory(BookCategory& category) -> void {
            cleardevice();
            Menu menu(80, 30, "返回", 30, 20, "选择书籍类别", 200, 90);
            std::vector<std::string> selections {
                "教材", "小说", "学术类", "考试类", "其他"
            };
            int_t choice {menu.showNormal(selections)};
            switch (choice) {
                case 1: category = BookCategory::textbook; break;
                case 2: category = BookCategory::fiction;  break;
                case 3: category = BookCategory::academic; break;
                case 4: category = BookCategory::exam;     break;
                case 5: category = BookCategory::other;    break;
            }
        }


        /**
         * @brief 修改用户密码
         * 
         * @param user 用户
         * @return 成功修改返回 true
         */
        auto userKey(std::shared_ptr<User>& user) -> bool {
            if (!authenUser(user)) {
                return false;
            }
            std::string new_password {};
            if (Input::string(new_password, "输入新密码", "提示")) {
                user->key.change(new_password);
                return true;
            } else {
                return false;
            }
        }

        /**
         * @brief 修改用户基本信息
         * 
         * @param user 用户
         * @return 成功修改返回 true
         */
        auto userInfo(std::shared_ptr<User>& user) -> bool {
            auto tmp_user {std::make_shared<User>(*user)};
            bool changed {false};

            Menu menu(80, 30, "不保存退出", 30, 20, "选择修改的信息", 200, 90);
            std::vector<std::string> selections {
                "保存修改", "修改用户名", "修改电话", "修改QQ号", "修改微信号"
            };

            int circle {1};
            do {
                circle = 1;
                cleardevice();
                int_t choice {menu.showUser(selections, 10, "正在被修改的用户信息详情", tmp_user)};

                switch (choice) {
                    case 0: 
                        if (MessageBox(GetHWnd(), "确认退出修改吗? 修改不会保存", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                            changed = false;
                            circle = 0;
                        }
                        break;
                    case 1: 
                        *user = *tmp_user;
                        changed = true;
                        circle = 0;
                        break;
                    case 2:
                        Input::string(tmp_user->name, "输入用户名\n\"一个好的名字能让别人更快的记住你\"", "输入");
                        break;
                    case 3:
                        Input::integer(tmp_user->tel, "输入电话", "输入");
                        break;
                    case 4:
                        Input::integer(tmp_user->tel, "输入QQ号", "输入");
                        break;
                    case 5:
                        Input::string(tmp_user->wechat, "输入微信号", "输入");
                        break;
                    
                }

            } while (circle);

            return changed;
        }

        /**
         * @brief 修改书籍信息
         * 
         * @param book 书籍
         * @return 成功修改返回 true
         */
        auto bookInfo(std::shared_ptr<Book>& book) -> bool {
            auto tmp_book {std::make_shared<Book>(*book)};
            bool changed {false};

            Menu menu(80, 30, "不保存退出", 30, 20, "选择修改的信息", 200, 70);
            std::vector<std::string> selections {
               "保存修改", "书籍名称", "ISBN", "书籍作者", "书籍出版社", "书籍类别", "书籍完整度", "书籍价格"
            };

            int circle {1};
            do {
                circle = 1;
                cleardevice();
                int_t choice {menu.showBook(selections, 10, "正在被修改的书籍详情", tmp_book)};

                switch (choice) {
                    case 0: 
                        if (MessageBox(GetHWnd(), "确认退出修改吗? 修改不会保存", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                            changed = false;
                            circle = 0;
                        }
                        break;
                    case 1: 
                        *book = *tmp_book;
                        changed = true;
                        circle = 0;
                        break;
                    case 2:
                        Input::string(tmp_book->title, "输入书籍名称", "输入");
                        break;
                    case 3:
                        Input::string(tmp_book->isbn, "输入书籍ISBN", "输入");
                        break;
                    case 4:
                        Input::string(tmp_book->author, "输入书籍作者", "输入");
                        break;
                    case 5:
                        Input::string(tmp_book->press, "输入书籍出版社", "输入");
                        break;
                    case 6:
                        bookCategory(tmp_book->category);
                        break;
                    case 7:
                        Input::integer(tmp_book->integrity, "输入书籍完整度(0-100)", "输入");
                        break;
                    case 8:
                        Input::floatPoint(tmp_book->price, "输入价格", "输入");
                        break;
                }

            } while (circle);

            return changed;
        }
    }
}