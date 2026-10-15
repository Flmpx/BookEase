/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "../tools.hpp"
#include "../../menu/menu.hpp"
#include <string>
#include <vector>
#include <easyx.h>

namespace BK {

    namespace Tools {

        namespace Smart {

            namespace {
    
                /**
                 * 此区域函数由于是分不同情况, self表示user就是other_user, other则表示不是
                 */
    
                /* 展示用户 - 自己 */
                auto showUser_self(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<User>& other_user, const std::string& user_tip) {
                    int_t circle {1};
                
                    std::vector<std::string> selections {
                        "修改基本信息", "修改密码"
                    };
                    do {
                        circle = 1;
                        cleardevice();
                        int_t choice {Menu::showUser("返回", "选择操作", selections, user_tip, user, Menu::Layout::UserGen, true)};
    
                        switch (choice) {
                            case 0: circle = 0; break;
                            case 1: 
                                if (Tools::Change::user(user)) {
                                    Tools::File::saveUsers(USERS_FILE_DIR, users);
                                    MessageBox(GetHWnd(), "修改保存成功", "提示", MB_OK | MB_ICONINFORMATION);
                                }
                                break;
                            case 2:
                                if (Tools::Change::key(user->key)) {
                                    Tools::File::saveUsers(USERS_FILE_DIR, users);
                                    MessageBox(GetHWnd(), "密码修改成功", "提示", MB_OK | MB_ICONINFORMATION);
                                }
                                break;
                        }
                    } while (circle);
                }
    
                /* 展示用户 - 其他人 */
                auto showUser_other(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<User>& other_user, const std::string& user_tip) {
                    int_t circle {1};
                    std::vector<std::string> selections {};
    
                    do {
                        circle = 1;
                        cleardevice();
                        int_t choice {Menu::showUser("返回", "仅查看", selections, user_tip, other_user, Menu::Layout::UserGen)};
    
                        switch (choice) {
                            case 0: circle = 0; break;
                        }
    
                    } while (circle);
                }
            }

            /**
             * @brief 智能显示other_user的信息
             * 
             * @param user 当前登录用户
             * @param users 用户链表
             * @param books 书籍链表
             * @param other_user 待显示的用户
             * @param user_tip 用户详细信息块的内容
             */
            auto showUser(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<User>& other_user, const std::string& user_tip) -> void {
                if (user->id == other_user->id) {
                    showUser_self(user, users, books, other_user, user_tip);
                } else {
                    showUser_other(user, users, books, other_user, user_tip);
                }
            }
    
            namespace {
    
                /**
                 * 此区域的函数由于是分不同情况, 故采用showBook_${书籍状态}_${user属于那个利益方}
                 */

                /* 展示在售的书籍 给 其他人 */
                auto showBook_onsale_other(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book, const std::string& book_tip) {
                    int_t circle {1};
                    std::vector<std::string> selelctions {
                        "预定", "查看售卖者信息"
                    };
                    do {
                        circle = 1;
                        cleardevice();
                        int_t choice {Menu::showBook("返回", "选择操作", selelctions, "选中书籍的详情", book, Menu::Layout::BookGen, true)};
                        switch (choice) {
                            case 0: circle = 0; break;
                            case 1:
                                if (MessageBox(GetHWnd(), "确定要预定吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                                    book->reserver_id = user->id;
                                    book->reserve_time.set(std::time(nullptr));
                                    book->status = BookStatus::reserved;
        
                                    Tools::File::saveBooks(BOOKS_FILE_DIR, books);
                                    MessageBox(GetHWnd(), "预定成功!!!", "提示", MB_OK | MB_ICONINFORMATION);
                                    circle = 0;
                                } else {
                                    circle = 1;
                                }
                                break;
                            case 2: 
                                auto seller {book->seller(users)};
                                showUser(user, users, books, seller, "售卖者信息");
                                break;
                        }
                    } while (circle);
                }
                
                /* 展示在售的书籍 给 售卖者 */
                auto showBook_onsale_seller(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book, const std::string& book_tip) {
                    int_t circle {1};
                
                    std::vector<std::string> selections {
                        "下架书籍"
                    };
                    do {
                        circle = 1;
                        cleardevice();
                        int_t choice {Menu::showBook("返回", "选择操作", selections, book_tip, book, Menu::Layout::BookGen, true)};
    
                        switch (choice) {
                            case 0: circle = 0; break;
                            case 1:
                                if (MessageBox(GetHWnd(), "确定要下架书籍吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                                    book->status = BookStatus::removed;
                                    book->removed_time.set(std::time(nullptr));
                                    Tools::File::saveBooks(BOOKS_FILE_DIR, books);
                                    MessageBox(GetHWnd(), "已下架书籍!!!", "提示", MB_OK | MB_ICONINFORMATION);
                                    circle = 0;
                                }
                                break;
                        }
                    } while (circle);
                }
    
                /* 展示已被预定的书籍 给 售卖者 */
                auto showBook_reserved_seller(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book, const std::string& book_tip) {
                    int_t circle {1};
                
                    std::vector<std::string> selections {
                        "转为已售", "查看预定者信息"
                    };
                    do {
                        circle = 1;
                        cleardevice();
                        int_t choice {Menu::showBook("返回", "选择操作", selections, book_tip, book, Menu::Layout::BookGen, true)};
    
                        switch (choice) {
                            case 0: circle = 0; break;
                            case 1:
                                if (MessageBox(GetHWnd(), "确定预定方已收到你发布的书籍了吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                                    book->status = BookStatus::sold;
                                    book->buyer_id = book->reserver_id;
                                    book->buy_time.set(std::time(nullptr));
                                    Tools::File::saveBooks(BOOKS_FILE_DIR, books);
                                    MessageBox(GetHWnd(), "交易完成", "提示", MB_OK | MB_ICONINFORMATION);
                                    circle = 0;
                                }
                                break;
                            case 2:
                                auto reserver {book->reserver(users)};
                                showUser_other(user, users, books, reserver, "预定者信息");
                                break;
                        }
                    } while (circle);
                }

                /* 展示预定的书籍 给 预定者 */
                auto showBook_reserved_reserver(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book, const std::string& book_tip) {
                    int_t circle {1};
            
                    std::vector<std::string> selections {
                        "取消预定", "查看售卖者信息"
                    };
                    do {
                        circle = 1;
                        cleardevice();
                        int_t choice {Menu::showBook("返回", "选择操作", selections, book_tip, book, Menu::Layout::BookGen, true)};
                        switch (choice) {
                            case 0: circle = 0; break;
                            case 1:
                                if (MessageBox(GetHWnd(), "确定要取消预定", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                                    book->status = BookStatus::on_sale;
                                    Tools::File::saveBooks(BOOKS_FILE_DIR, books);
                                    MessageBox(GetHWnd(), "已取消预定", "提示", MB_OK | MB_ICONINFORMATION);
                                    circle = 0;
                                }
                                break;
                            case 2:
                                auto seller {book->seller(users)};
                                showUser(user, users, books, seller, "售卖者信息");
                                break;
                                
                        }
                    } while (circle);
                }

                /* 展示已售的书籍 给 售卖者 */
                auto showBook_sold_seller(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book, const std::string& book_tip) {
                    int_t circle {1};
            
                    std::vector<std::string> selections {
                        "查看购买者信息"
                    };
                    do {
                        circle = 1;
                        cleardevice();
                        int_t choice {Menu::showBook("返回", "选择操作", selections, book_tip, book, Menu::Layout::BookGen, true)};

                        switch (choice) {
                            case 0: circle = 0; break;
                            case 1: 
                                auto buyer {book->buyer(users)};
                                showUser(user, users, books, buyer, "购买者信息");
                                break;
                        }
                    } while (circle);
                }

                /* 展示已售的书籍 给 购买者 */
                auto showBook_sold_buyer(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book, const std::string& book_tip) {
                    int_t circle {1};
            
                    std::vector<std::string> selections {
                        "查看售卖者信息"
                    };
                    do {
                        circle = 1;
                        cleardevice();
                        int_t choice {Menu::showBook("返回", "选择操作", selections, book_tip, book, Menu::Layout::BookGen, true)};

                        switch (choice) {
                            case 0: circle = 0; break;
                            case 1: 
                                auto seller {book->seller(users)};
                                showUser(user, users, books, seller, "售卖者信息");
                                break;
                        }
                    } while (circle);
                }

                /* 展示已下架的书籍 给 售卖者 */
                auto showBook_removed_seller(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book, const std::string& book_tip) {
                    int_t circle {1};
            
                    std::vector<std::string> selections {
                        "重新上架", "修改书籍信息"
                    };
                    do {
                        circle = 1;
                        cleardevice();
                        int_t choice {Menu::showBook("返回", "选择操作", selections, book_tip, book, Menu::Layout::BookGen, true)};

                        switch (choice) {
                            case 0: circle = 0; break;
                            case 1: 
                                if (MessageBox(GetHWnd(), "确定要要重新上架吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                                    book->status = BookStatus::on_sale;
                                    book->publish_time.set(std::time(nullptr));
                                    Tools::File::saveBooks(BOOKS_FILE_DIR, books);
                                    MessageBox(GetHWnd(), "重新上架成功", "提示", MB_OK | MB_ICONINFORMATION);
                                    circle = 0;
                                }
                                break;
                            case 2:
                                if (Tools::Change::book(book)) {
                                    Tools::File::saveBooks(BOOKS_FILE_DIR, books);
                                    MessageBox(GetHWnd(), "修改保存成功", "提示", MB_OK | MB_ICONINFORMATION);
                                }
                                break;
                        }
                    } while (circle);
                }

                /* 展示书籍 给 其他人(异常) */
                auto showBook_other(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book, const std::string& book_tip) {
                    int_t circle {1};
            
                    std::vector<std::string> selections {};
                    do {
                        circle = 1;
                        cleardevice();
                        int_t choice {Menu::showBook("返回", "仅查看", selections, "已下架的书籍详情", book, Menu::Layout::BookGen, true)};

                        switch (choice) {
                            case 0: circle = 0; break;
                        }
                    } while (circle);
                }
            
            }

            /**
             * @brief 智能显示书籍信息
             * 
             * @param user 当前登录用户
             * @param users 用户链表
             * @param books 书籍链表
             * @param book 待显示的书籍
             * @param book_tip 书籍详细信息块的内容
             */
            auto showBook(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book, const std::string& book_tip) -> void {
                switch (book->status) {
                    case BookStatus::on_sale:
                        if (book->seller_id == user->id) {
                            showBook_onsale_seller(user, users, books, book, book_tip);
                        } else {
                            showBook_onsale_other(user, users, books, book, book_tip);
                        }
                        break;
                    case BookStatus::reserved:
                        if (book->reserver_id == user->id) {
                            showBook_reserved_reserver(user, users, books, book, book_tip);
                        } else if (book->seller_id == user->id) {
                            showBook_reserved_seller(user, users, books, book, book_tip);
                        } else {
                            showBook_other(user, users, books, book, book_tip);
                        }
                        break;
                    case BookStatus::sold:
                        if (book->buyer_id == user->id) {
                            showBook_sold_buyer(user, users, books, book, book_tip);
                        } else if (book->seller_id == user->id) {
                            showBook_sold_seller(user, users, books, book, book_tip);
                        } else {
                            showBook_other(user, users, books, book, book_tip);
                        }
                        break;
                    case BookStatus::removed:
                        if (book->seller_id == user->id) {
                            showBook_removed_seller(user, users, books, book, book_tip);
                        }
                        break;
                    default:
                        showBook_other(user, users, books, book, book_tip);
                }
            }
        }
    }
}