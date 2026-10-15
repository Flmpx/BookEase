/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "../tools.hpp"
#include "../../menu/menu.hpp"
#include <vector>
#include <string>

namespace BK {

    namespace Tools {

        namespace Change {

            /**
             * @brief 修改书籍的类别(必定会被修改)
             * 
             * @param category 类别
             */
            auto bookCategory(BookCategory& category) -> void {
                cleardevice();
                std::vector<std::string> selections {
                    "教材", "小说", "学术类", "考试类", "其他"
                };
                int_t choice {Menu::showNormal("返回", "选择书籍类别", selections, Menu::Layout::NormalGen)};
                switch (choice) {
                    case 1: category = BookCategory::textbook; break;
                    case 2: category = BookCategory::fiction;  break;
                    case 3: category = BookCategory::academic; break;
                    case 4: category = BookCategory::exam;     break;
                    case 5: category = BookCategory::other;    break;
                }
            }
        
        
            /**
             * @brief 修改密钥
             * 
             * @param key 密钥
             * @return 成功修改返回 true
             */
            auto key(Key& key) -> bool {
                if (!Authen::key(key)) {
                    return false;
                }
                std::string new_password {};
                if (Input::element(new_password, "输入新密码(长度为8-16位)", "提示", Range<uint_t>(8, 16))) {
                    key.change(new_password);
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
            auto user(std::shared_ptr<User>& user) -> bool {
                auto tmp_user {std::make_shared<User>(*user)};
                bool changed {false};
        
                std::vector<std::string> selections {
                    "保存修改", "修改用户名", "修改电话", "修改QQ号", "修改微信号"
                };
        
                int circle {1};
                do {
                    circle = 1;
                    cleardevice();
                    int_t choice {Menu::showUser("不保存退出", "选择修改的信息", selections, "正在被修改的用户信息详情", tmp_user, Menu::Layout::UserGen)};
        
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
                            Input::element(tmp_user->name, "输入用户名\n\"一个好的名字能让别人更快的记住你\"", "输入");
                            break;
                        case 3:
                            Input::element(tmp_user->tel, "输入电话", "输入");
                            break;
                        case 4:
                            Input::element(tmp_user->qq, "输入QQ号", "输入");
                            break;
                        case 5:
                            Input::element(tmp_user->wechat, "输入微信号", "输入");
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
            auto book(std::shared_ptr<Book>& book) -> bool {
                auto tmp_book {std::make_shared<Book>(*book)};
                bool changed {false};
        
                std::vector<std::string> selections {
                    "保存修改", "书籍名称", "书籍作者", "书籍出版社", "ISBN", "书籍价格", "书籍完整度", "书籍类别"
                };
        
                int circle {1};
                do {
                    circle = 1;
                    cleardevice();
        
                    Menu::Layout::Book special(Menu::Layout::BookGen);
                    special.normal.select_h = 70;               // 由于选项过多必须修改高度
                    int_t choice {Menu::showBook("不保存退出", "选择修改的信息", selections, "正在被修改的书籍详情", tmp_book, special)};
        
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
                            Input::element(tmp_book->title, "输入书籍名称", "输入");
                            break;
                        case 3:
                            Input::element(tmp_book->author, "输入书籍作者", "输入");
                            break;
                        case 4:
                            Input::element(tmp_book->press, "输入书籍出版社", "输入");
                            break;
                        case 5:
                            Input::element(tmp_book->isbn, "输入书籍ISBN", "输入");
                            break;
                        case 6:
                            Input::element(tmp_book->price, "输入价格", "输入", Range<Price>(Price(0.0)));
                            break;
                        case 7:
                            Input::element(tmp_book->integrity, "输入书籍完整度(0-100)", "输入", Range<int_t>(min_integrity, max_integrity));
                            break;
                        case 8:
                            bookCategory(tmp_book->category);
                            break;
                    }
        
                } while (circle);
        
                return changed;
            }
        }
    }
}