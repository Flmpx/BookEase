/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "my.hpp"
#include <vector>
#include <string>
#include "../../menu/menu.hpp"
#include "../../tools/tools.hpp"
#include "../../tools/cmps.hpp"

namespace BK {

    /**
     * 此区域函数过多, 故采用下划线命名法
     * 比如 my_buy_sold, my_buy_reversed 分别代表我的菜单中的 我的购买 的 已购 和 预定
     * 
     * `*_detail` 函数会返回 bool, 用户判断临时链表是否要删掉传入该函数的书籍, 其他函数返回 void
     */

    namespace {

        /* 我的 > 我的购买 > 购买的书籍 > 书籍详情 > 售卖者信息 */
        auto my_buy_sold_detail_seller(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, const std::shared_ptr<User>& seller) {
            int_t circle {1};
            std::vector<std::string> selections {};

            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showUser("返回", "仅查看", selections, "售卖者信息", seller, Menu::Layout::UserGen)};

                switch (choice) {
                    case 0: circle = 0; break;
                }

            } while (circle);
        }

        /* 我的 > 我的购买 > 购买的书籍 > 书籍详情 */
        auto my_buy_sold_detail(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book) -> bool {
            int_t circle {1};
            
            std::vector<std::string> selections {
                "查看售卖者信息"
            };
            bool changed {false};
            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showBook("返回", "选择操作", selections, "已购书籍详情", book, Menu::Layout::BookGen, true)};

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: 
                        my_buy_sold_detail_seller(user, users, books, book->seller(users));
                        break;
                }
            } while (circle);

            return changed;
        }
        
        /* 我的 > 我的购买 > 购买的书籍 */
        auto my_buy_sold(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::sold)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->buyer_id != user->id;});

            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按购买时间升序", "按购买时间降序"
            };
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "已购买的书籍", now_books, Menu::Layout::BooksGen)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    auto book {std::next(now_books.begin(), idx)};
                    if (my_buy_sold_detail(user, users, books, *book)) {
                        now_books.erase(book);
                    }
                }

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: now_books.sort(CmpBook::Price::up); break;
                    case 2: now_books.sort(CmpBook::Price::down); break;
                    case 3: now_books.sort(CmpBook::SoldTime::up); break;
                    case 4: now_books.sort(CmpBook::SoldTime::down); break;
                }
            } while (circle);
        }

        /* 我的 > 我的购买 > 预定的书籍 > 书籍详情 > 售卖者信息 */
        auto my_buy_reserved_detail_seller(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, const std::shared_ptr<User>& seller) {
            int_t circle {1};
            std::vector<std::string> selections {};

            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showUser("返回", "仅查看", selections, "售卖者信息", seller, Menu::Layout::UserGen)};

                switch (choice) {
                    case 0: circle = 0; break;
                }

            } while (circle);
        }

        /* 我的 > 我的购买 > 预定的书籍 > 书籍详情 */
        auto my_buy_reserved_detail(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book) -> bool {
            int_t circle {1};
            
            std::vector<std::string> selections {
                "取消预定", "查看售卖者信息"
            };
            bool changed {false};
            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showBook("返回", "选择操作", selections, "已预定的书籍详情", book, Menu::Layout::BookGen, true)};
                switch (choice) {
                    case 0: circle = 0; break;
                    case 1:
                        if (MessageBox(GetHWnd(), "确定要取消预定", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                            book->status = BookStatus::on_sale;
                            Tools::File::saveBooks(BOOKS_FILE_DIR, books);
                            MessageBox(GetHWnd(), "已取消预定", "提示", MB_OK | MB_ICONINFORMATION);
                            changed = true;
                            circle = 0;
                        }
                        break;
                    case 2:
                        my_buy_reserved_detail_seller(user, users, books, book->seller(users));
                        break;
                        
                }
            } while (circle);

            return changed;
        }

        /* 我的 > 我的购买 > 预定的书籍 */
        auto my_buy_reserved(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::reserved)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->reserver_id != user->id;});

            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按预定时间升序", "按预定时间降序"
            };
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "已预定的书籍", now_books, Menu::Layout::BooksGen)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    auto book {std::next(now_books.begin(), idx)};
                    if (my_buy_reserved_detail(user, users, books, *book)) {
                        now_books.erase(book);
                    }
                }

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: now_books.sort(CmpBook::Price::up); break;
                    case 2: now_books.sort(CmpBook::Price::down); break;
                    case 3: now_books.sort(CmpBook::ReservedTime::up); break;
                    case 4: now_books.sort(CmpBook::ReservedTime::down); break;
                }
            } while (circle);
        }

        /* 我的 > 我的购买 */
        auto my_buy(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};
            
            std::vector<std::string> selections {
                "已预定", "已购买"
            };
            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showNormal("返回", "选择要查看的内容", selections, Menu::Layout::NormalGen)};

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: my_buy_reserved(user, users, books); break;
                    case 2: my_buy_sold(user, users, books); break;
                }
            } while (circle);
        }

        /* 我的 > 我的发布 > 在售的书籍 > 书籍详情 */
        auto my_post_onsale_detail(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book) -> bool {
            int_t circle {1};
            
            std::vector<std::string> selections {
                "下架书籍"
            };
            bool changed {false};
            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showBook("返回", "选择操作", selections, "在售书籍详情", book, Menu::Layout::BookGen, true)};

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1:
                        if (MessageBox(GetHWnd(), "确定要下架书籍吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                            book->status = BookStatus::removed;
                            book->removed_time.set(std::time(nullptr));
                            Tools::File::saveBooks(BOOKS_FILE_DIR, books);
                            MessageBox(GetHWnd(), "已下架书籍\n可以在下架页找到当前书籍", "提示", MB_OK | MB_ICONINFORMATION);
                            changed = true;
                            circle = 0;
                        }
                        break;
                }
            } while (circle);

            return changed;
        }

        /* 我的 > 我的发布 > 在售的书籍 */
        auto my_post_onsale(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::on_sale)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->seller_id != user->id;});

            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按发布时间升序", "按发布时间降序"
            };
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "在售的书籍", now_books, Menu::Layout::BooksGen)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    auto book {std::next(now_books.begin(), idx)};
                    if (my_post_onsale_detail(user, users, books, *book)) {
                        now_books.erase(book);
                    }
                }

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: now_books.sort(CmpBook::Price::up); break;
                    case 2: now_books.sort(CmpBook::Price::down); break;
                    case 3: now_books.sort(CmpBook::PublishTime::up); break;
                    case 4: now_books.sort(CmpBook::PublishTime::down); break;
                }
            } while (circle);
        }

        
        /* 我的 > 我的发布 > 已被预定的书籍 > 书籍详情 > 预定者信息 */
        auto my_post_reserved_detail_reserver(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, const std::shared_ptr<User>& reserver) {
            int_t circle {1};
            std::vector<std::string> selections {};

            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showUser("返回", "仅查看", selections, "预定者信息", reserver, Menu::Layout::UserGen)};

                switch (choice) {
                    case 0: circle = 0; break;
                }

            } while (circle);
        }

        /* 我的 > 我的发布 > 已被预定的书籍 > 书籍详情 */
        auto my_post_reserved_detail(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book) -> bool {
            int_t circle {1};
            
            std::vector<std::string> selections {
                "转为已售", "查看预定者信息"
            };
            bool changed {false};
            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showBook("返回", "选择操作", selections, "已被预定书籍详情", book, Menu::Layout::BookGen, true)};

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1:
                        if (MessageBox(GetHWnd(), "确定预定方已收到你那本陪伴你诸多岁月的书了吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                            book->status = BookStatus::sold;
                            book->buyer_id = book->reserver_id;
                            book->buy_time.set(std::time(nullptr));
                            Tools::File::saveBooks(BOOKS_FILE_DIR, books);
                            MessageBox(GetHWnd(), "书籍已找到新的落脚点", "提示", MB_OK | MB_ICONINFORMATION);
                            changed = true;
                            circle = 0;
                        }
                        break;
                    case 2:
                        my_post_reserved_detail_reserver(user, users, books, book->reserver(users));
                        break;
                }
            } while (circle);

            return changed;
        }

        /* 我的 > 我的发布 > 已被预定的书籍 */
        auto my_post_reserved(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::reserved)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->seller_id != user->id;});
            
            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按预定时间升序", "按预定时间降序"
            };
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "已被预定的书籍", now_books, Menu::Layout::BooksGen)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    auto book {std::next(now_books.begin(), idx)};
                    if (my_post_reserved_detail(user, users, books, *book)) {
                        now_books.erase(book);
                    }
                }

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: now_books.sort(CmpBook::Price::up); break;
                    case 2: now_books.sort(CmpBook::Price::down); break;
                    case 3: now_books.sort(CmpBook::ReservedTime::up); break;
                    case 4: now_books.sort(CmpBook::ReservedTime::down); break;
                }
            } while (circle);
        }

        /* 我的 > 我的发布 > 已售的书籍 > 书籍详情 > 购买者信息 */
        auto my_post_sold_detail_buyer(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, const std::shared_ptr<User>& buyer) {
            int_t circle {1};
            std::vector<std::string> selections {};

            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showUser("返回", "仅查看", selections, "购买者信息", buyer, Menu::Layout::UserGen)};

                switch (choice) {
                    case 0: circle = 0; break;
                }

            } while (circle);
        }

        /* 我的 > 我的发布 > 已售的书籍 > 书籍详情 */
        auto my_post_sold_detail(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book) -> bool {
            int_t circle {1};
            
            std::vector<std::string> selections {
                "查看购买者信息"
            };
            bool changed {false};
            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showBook("返回", "选择操作", selections, "已被预定书籍详情", book, Menu::Layout::BookGen, true)};

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: 
                        my_post_sold_detail_buyer(user, users, books, book->buyer(users));
                        break;
                }
            } while (circle);

            return changed;
        }

        /* 我的 > 我的发布 > 已售的书籍 */
        auto my_post_sold(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::sold)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->seller_id != user->id;});
            
            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按已购时间升序", "按已购时间降序"
            };
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "已被购买的书籍", now_books, Menu::Layout::BooksGen)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    auto book {std::next(now_books.begin(), idx)};
                    if (my_post_sold_detail(user, users, books, *book)) {
                        now_books.erase(book);
                    }
                }

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: now_books.sort(CmpBook::Price::up); break;
                    case 2: now_books.sort(CmpBook::Price::down); break;
                    case 3: now_books.sort(CmpBook::SoldTime::up); break;
                    case 4: now_books.sort(CmpBook::SoldTime::down); break;
                }
            } while (circle);
        }

        /* 我的 > 我的发布 > 已下架的书籍 > 书籍详情 */
        auto my_post_removed_detail(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book) -> bool {
            int_t circle {1};
            
            std::vector<std::string> selections {
                "重新上架", "修改书籍信息"
            };
            bool changed {false};
            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showBook("返回", "选择操作", selections, "已下架的书籍详情", book, Menu::Layout::BookGen, true)};

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: 
                        if (MessageBox(GetHWnd(), "确定要要重新上架吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                            book->status = BookStatus::on_sale;
                            book->publish_time.set(std::time(nullptr));
                            Tools::File::saveBooks(BOOKS_FILE_DIR, books);
                            MessageBox(GetHWnd(), "重新上架成功", "提示", MB_OK | MB_ICONINFORMATION);
                            changed = true;
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

            return changed;
        }

        /* 我的 > 我的发布 > 已下架的书籍 */
        auto my_post_removed(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::removed)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->seller_id != user->id;});
            
            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按下架时间升序", "按下架时间降序"
            };
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "已下架的书籍", now_books, Menu::Layout::BooksGen)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    auto book {std::next(now_books.begin(), idx)};
                    if (my_post_removed_detail(user, users, books, *book)) {
                        now_books.erase(book);
                    }
                }

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: now_books.sort(CmpBook::Price::up); break;
                    case 2: now_books.sort(CmpBook::Price::down); break;
                    case 3: now_books.sort(CmpBook::RemovedTime::up); break;
                    case 4: now_books.sort(CmpBook::RemovedTime::down); break;
                }
            } while (circle);
        }

        /* 我的 > 我的发布 */
        auto my_post(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};
            
            std::vector<std::string> selections {
                "在售卖", "已被预定", "已被购买", "已下架"
            };
            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showNormal("返回", "选择要查看的内容", selections, Menu::Layout::NormalGen)};

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1: my_post_onsale(user, users, books); break;
                    case 2: my_post_reserved(user, users, books); break;
                    case 3: my_post_sold(user, users, books); break;
                    case 4: my_post_removed(user, users, books); break;
                }
            } while (circle);
        }

        /* 我的 > 我的信息 */
        auto my_info(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};
            
            std::vector<std::string> selections {
                "修改基本信息", "修改密码"
            };
            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showUser("返回", "选择操作", selections, "个人信息", user, Menu::Layout::UserGen, true)};

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

    }

    /* 我的 */
    auto my(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) -> void {
        int_t circle {1};

        std::vector<std::string> selelctions {
            "我的信息", "我的发布", "我的购买"
        };
        do {
            circle = 1;
            cleardevice();
            int_t choice {Menu::showNormal("返回", "选择要查看的内容", selelctions, Menu::Layout::NormalGen)};

            switch (choice) {
                case 0: circle = 0; break;
                case 1: my_info(user, users, books); break;
                case 2: my_post(user, users, books); break;
                case 3: my_buy(user, users, books); break;
            }
        } while (circle);
        
    }
}