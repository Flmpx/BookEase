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
     */

    namespace {

        /* 我的 > 我的购买 > 购买的书籍 */
        auto my_buy_sold(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::sold)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->buyer_id != user->id;});

            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按购买时间升序", "按购买时间降序"
            };
            int_t record_index {0};
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "检索到的书籍", now_books, Menu::Layout::BooksGen, record_index)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    record_index = idx;
                    auto book {std::next(now_books.begin(), idx)};
                    Tools::Smart::showBook(user, users, books, *book, "选定的书籍");
                } else {
                    switch (choice) {
                        case 0: circle = 0; break;
                        case 1: now_books.sort(CmpBook::Price::up); break;
                        case 2: now_books.sort(CmpBook::Price::down); break;
                        case 3: now_books.sort(CmpBook::SoldTime::up); break;
                        case 4: now_books.sort(CmpBook::SoldTime::down); break;
                    }
                    record_index = 0;
                }

            } while (circle);
        }

        /* 我的 > 我的购买 > 预定的书籍 */
        auto my_buy_reserved(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::reserved)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->reserver_id != user->id;});

            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按预定时间升序", "按预定时间降序"
            };
            int record_index {0};
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "检索到的书籍", now_books, Menu::Layout::BooksGen, record_index)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    record_index = idx;
                    auto book {std::next(now_books.begin(), idx)};
                    Tools::Smart::showBook(user, users, books, *book, "选定的书籍");
                } else {
                    switch (choice) {
                        case 0: circle = 0; break;
                        case 1: now_books.sort(CmpBook::Price::up); break;
                        case 2: now_books.sort(CmpBook::Price::down); break;
                        case 3: now_books.sort(CmpBook::ReservedTime::up); break;
                        case 4: now_books.sort(CmpBook::ReservedTime::down); break;
                    }
                    record_index = 0;
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

        /* 我的 > 我的发布 > 在售的书籍 */
        auto my_post_onsale(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::on_sale)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->seller_id != user->id;});

            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按发布时间升序", "按发布时间降序"
            };
            int_t record_index {0};
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "检索到的书籍", now_books, Menu::Layout::BooksGen, record_index)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    record_index = idx;
                    auto book {std::next(now_books.begin(), idx)};
                    Tools::Smart::showBook(user, users, books, *book, "选定的书籍");
                } else {
                    switch (choice) {
                        case 0: circle = 0; break;
                        case 1: now_books.sort(CmpBook::Price::up); break;
                        case 2: now_books.sort(CmpBook::Price::down); break;
                        case 3: now_books.sort(CmpBook::PublishTime::up); break;
                        case 4: now_books.sort(CmpBook::PublishTime::down); break;
                    }
                    record_index = 0;
                }

            } while (circle);
        }

        /* 我的 > 我的发布 > 已被预定的书籍 */
        auto my_post_reserved(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::reserved)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->seller_id != user->id;});
            
            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按预定时间升序", "按预定时间降序"
            };
            int_t record_index {0};
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "检索到的书籍", now_books, Menu::Layout::BooksGen, record_index)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    record_index = idx;
                    auto book {std::next(now_books.begin(), idx)};
                    Tools::Smart::showBook(user, users, books, *book, "选定的书籍");
                } else {
                    switch (choice) {
                        case 0: circle = 0; break;
                        case 1: now_books.sort(CmpBook::Price::up); break;
                        case 2: now_books.sort(CmpBook::Price::down); break;
                        case 3: now_books.sort(CmpBook::ReservedTime::up); break;
                        case 4: now_books.sort(CmpBook::ReservedTime::down); break;
                    }
                    record_index = 0;
                }

            } while (circle);
        }

        /* 我的 > 我的发布 > 已售的书籍 */
        auto my_post_sold(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::sold)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->seller_id != user->id;});
            
            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按已购时间升序", "按已购时间降序"
            };
            int_t record_index {0};
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "检索到的书籍", now_books, Menu::Layout::BooksGen, record_index)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    record_index = idx;
                    auto book {std::next(now_books.begin(), idx)};
                    Tools::Smart::showBook(user, users, books, *book, "选定的书籍");
                } else {
                    switch (choice) {
                        case 0: circle = 0; break;
                        case 1: now_books.sort(CmpBook::Price::up); break;
                        case 2: now_books.sort(CmpBook::Price::down); break;
                        case 3: now_books.sort(CmpBook::SoldTime::up); break;
                        case 4: now_books.sort(CmpBook::SoldTime::down); break;
                    }
                    record_index = 0;
                }

            } while (circle);
        }

        /* 我的 > 我的发布 > 已下架的书籍 */
        auto my_post_removed(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::list<std::shared_ptr<Book>> now_books {user->books(books, BookStatus::removed)};
            now_books.remove_if([&user](const std::shared_ptr<Book>& book) {return book->seller_id != user->id;});
            
            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按下架时间升序", "按下架时间降序"
            };
            int_t record_index {0};
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "检索到的书籍", now_books, Menu::Layout::BooksGen, record_index)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    record_index = idx;
                    auto book {std::next(now_books.begin(), idx)};
                    Tools::Smart::showBook(user, users, books, *book, "选定的书籍");
                } else {
                    switch (choice) {
                        case 0: circle = 0; break;
                        case 1: now_books.sort(CmpBook::Price::up); break;
                        case 2: now_books.sort(CmpBook::Price::down); break;
                        case 3: now_books.sort(CmpBook::RemovedTime::up); break;
                        case 4: now_books.sort(CmpBook::RemovedTime::down); break;
                    }
                    record_index = 0;
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
                case 1: Tools::Smart::showUser(user, users, books, user, "个人信息"); break;
                case 2: my_post(user, users, books); break;
                case 3: my_buy(user, users, books); break;
            }
        } while (circle);
        
    }
}