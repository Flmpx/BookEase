/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "buy.hpp"
#include <easyx.h>
#include <vector>
#include <string>
#include "../../menu/menu.hpp"
#include "../../tools/tools.hpp"
#include "../../tools/cmps.hpp"
#include "../saveandload/saveandload.hpp"
#include <cstdio>
#include <ctime>


namespace BK {
    namespace {
        void select(BookCategory& c, BookCmpCondition& cmp_codition) {
            int circle {1};
            do {
                circle = 1;
                cleardevice();
                std::vector<std::string> selections {
                    "重置筛选信息", "书籍类别"
                };
                if (!cmp_codition.isUmlimit(BookCmpCondition::Unlimit::category)) {
                    selections[1] += (": " + getBookCategoryString(c));
                }
                int_t choice {Menu::showNormal("保存并退出", "选择操作", selections, Menu::Layout::NormalGen)};

                switch (choice) {
                    case 0: 
                        circle = 0;
                        break;
                    case 1:
                        cmp_codition.setUnlimit(BookCmpCondition::Unlimit::category);
                        break;
                    case 2:
                        cmp_codition.unsetUnlimit(BookCmpCondition::Unlimit::category);
                        Tools::Change::bookCategory(c);
                        break;
                }

            } while (circle);
        } 

        auto select(std::string& str,  const std::string& selection, BookCmpCondition& cmp_codition, BookCmpCondition::Unlimit u, Range<BK::uint_t> r = Range<BK::uint_t>()) -> void {
            int circle {1};
            do {
                circle = 1;
                cleardevice();
                std::vector<std::string> selections {
                    "重置筛选信息", selection
                };
                if (!cmp_codition.isUmlimit(u)) {
                    selections[1] += (": " + str);
                }
                int_t choice {Menu::showNormal("保存并退出", "选择操作", selections, Menu::Layout::NormalGen)};

                switch (choice) {
                    case 0: 
                        circle = 0;
                        break;
                    case 1:
                        cmp_codition.setUnlimit(u);
                        break;
                    case 2:
                        cmp_codition.unsetUnlimit(u);
                        Tools::Input::element(str, "输入" + selection, "输入", r);
                        break;
                }

            } while (circle);
        } 

        auto select(int_t& i, const std::string& selection, BookCmpCondition& cmp_codition, BookCmpCondition::Unlimit u, Range<BK::int_t> r = Range<BK::int_t>()) -> void {
            int circle {1};
            do {
                circle = 1;
                cleardevice();
                std::vector<std::string> selections {
                    "重置筛选信息", selection
                };
                if (!cmp_codition.isUmlimit(u)) {
                    selections[1] += (": " + std::to_string(i));
                }
                int_t choice {Menu::showNormal("保存并退出", "选择操作", selections, Menu::Layout::NormalGen)};

                switch (choice) {
                    case 0: 
                        circle = 0;
                        break;
                    case 1:
                        cmp_codition.setUnlimit(u);
                        break;
                    case 2:
                        cmp_codition.unsetUnlimit(u);
                        Tools::Input::element(i, "输入" + selection, "输入", r);
                        break;
                }

            } while (circle);
        }

        template <typename T>
        auto selectRange(T& down_t, T& up_t, const std::string selection, BookCmpCondition& cmp_codition, BookCmpCondition::Unlimit down_u, BookCmpCondition::Unlimit up_u, Range<T> r = Range<T>()) -> void {
            int circle {1};
            int circle_in {1};
            do {
                circle = 1;
                cleardevice();
                std::vector<std::string> selections {
                    "重置筛选信息", selection + "上限", selection + "下限"
                };
                if (cmp_codition.isUmlimit(up_u)) {
                    selections[1] += ": +∞";
                } else {
                    selections[1] += (": " + std::to_string(up_t));
                }
                if (cmp_codition.isUmlimit(down_u)) {
                    selections[2] += ": -∞";
                } else {
                    selections[2] += (": " + std::to_string(down_t));
                }
                int_t choice {Menu::showNormal("保存并退出", "选择操作", selections, Menu::Layout::NormalGen)};
                T tmp_t;

                switch (choice) {
                    case 0: 
                        circle = 0;
                        break;
                    case 1:
                        cmp_codition.setUnlimit(up_u);
                        cmp_codition.setUnlimit(down_u);
                        break;
                    case 2:
                        tmp_t = up_t;
                        do {
                            circle_in = 1;
                            if (Tools::Input::element(tmp_t, "输入" + selection + "上限", "输入", r)) {
                                if (!cmp_codition.isUmlimit(down_u) && !Range<T>(down_t, r.max()).contain(tmp_t)) {
                                    MessageBox(GetHWnd(), "上限不能小于下限", "提示", MB_OK | MB_ICONWARNING);
                                    circle_in = 1;
                                } else {
                                    cmp_codition.unsetUnlimit(up_u);
                                    up_t = tmp_t;
                                    circle_in = 0;
                                }
                            } else {
                                circle_in = 0;
                            }
                        } while (circle_in);
                        break;
                    case 3:
                        tmp_t = down_t;
                        do {
                            circle_in = 1;
                            if (Tools::Input::element(tmp_t, "输入" + selection + "下限", "输入", r)) {
                                if (!cmp_codition.isUmlimit(up_u) && !Range<T>(r.min(), up_t).contain(tmp_t)) {
                                    MessageBox(GetHWnd(), "下限不能大于下限", "提示", MB_OK | MB_ICONWARNING);
                                    circle_in = 1;
                                } else {
                                    cmp_codition.unsetUnlimit(down_u);
                                    down_t = tmp_t;
                                    circle_in = 0;
                                }
                            } else {
                                circle_in = 0;
                            }
                        } while (circle_in);
                        break;       
                }

            } while (circle);
        }

        auto readyToReserve(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book) -> bool {
            int_t circle {1};
            std::vector<std::string> selelctions {
                "预定"
            };
            bool reserved {false};
            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showBook("返回", "选择操作", selelctions, "选中书籍的详情", book, Menu::Layout::BookGen, true)};
                switch (choice) {
                    case 0: circle = 0; break;
                    case 1:
                        if (book->seller_id != user->id) {
                            if (MessageBox(GetHWnd(), "确定要预定吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                                book->reserver_id = user->id;
                                book->reserve_time.set(std::time(nullptr));
                                book->status = BookStatus::reserved;
    
                                saveBooksToFile(BOOKS_FILE_DIR, books);
                                MessageBox(GetHWnd(), "预定成功!\n你可在我的页查看已订详情\n尝试与卖者联系\n", "提示", MB_OK | MB_ICONINFORMATION);
                                circle = 0;
                                reserved = true;
                            } else {
                                circle = 1;
                            }
                        } else {
                            MessageBox(GetHWnd(), "不可以自己预定自己的书哦", "提示", MB_OK | MB_ICONSTOP);
                            circle = 1;
                        }
                }
            } while (circle);
            
            return reserved;
        }

        auto revealSearchRes(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, const BookCmpCondition& cmp_condition) -> void {
            std::list<std::shared_ptr<Book>> now_books {};
            for (auto& it : books) {
                if (*it == cmp_condition) {
                    now_books.push_back(it);
                }
            }

            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按发布时间升序", "按发布时间降序"
            };
            int_t circle {1};
            do {
                circle = 1;
                int_t choice {Menu::showBooks("返回", "选择排序方式", selections, "当前检索到的所有书籍", now_books, Menu::Layout::BooksGen)};

                if (choice < 0) {
                    int_t idx {-choice - 1};
                    auto book {std::next(now_books.begin(), idx)};
                    if (readyToReserve(user, users, books, *book)) {
                        now_books.erase(book);
                    }
                    continue;
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
    }



    auto buy(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) -> void {
        BookCmpCondition cmp_condition {};
        cmp_condition.unsetUnlimit(BookCmpCondition::Unlimit::status);
        cmp_condition.status = BookStatus::on_sale;

        int_t circle {1};
        char buf[256] {""};
        do {
            circle = 1;
            cleardevice();
            std::vector<std::string> selections {
                "开始检索", "重置所有条件", "书籍id", "书名", "ISBN", "书籍作者", "出版社", "书籍类别", "书籍完整度",  "价格区间", "时间区间"
            };

            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::id)) {
                selections[2] += (": " + std::to_string(cmp_condition.id));
            }

            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::title)) {
                selections[3] += (": " + cmp_condition.title);
            }
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::isbn)) {
                selections[4] += (": " + cmp_condition.isbn);
            }
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::author)) {
                selections[5] += (": " + cmp_condition.author);
            }
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::press)) {
                selections[6] += (": " + cmp_condition.press);
            }
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::category)) {
                selections[7] += (": " + getBookCategoryString(cmp_condition.category));
            }

            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::down_integrity)) {
                selections[8] += (": [" + std::to_string(cmp_condition.down_integrity));
            } else {
                selections[8] += ": [-∞";
            }
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::up_integrity)) {
                selections[8] += (", " + std::to_string(cmp_condition.up_integrity)) + "]";
            } else {
                selections[8] += ", +∞]";
            }

            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::down_price)) {
                selections[9] += (": [" + std::to_string(cmp_condition.down_price));
            } else {
                selections[9] += ": [-∞";
            }
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::up_price)) {
                selections[9] += (", " + std::to_string(cmp_condition.up_price)) + "]";
            } else {
                selections[9] += ", +∞]";
            }

            Time time {cmp_condition.up_publish_time};
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::up_publish_time)) {
                snprintf(buf, 256, "%04lld年%02lld月%02lld日", time.year(), time.month(), time.day());
                selections[10] += (": [" + std::string(buf));
            } else {
                selections[10] += ": [-∞";
            }

            time = cmp_condition.down_publish_time;
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::up_publish_time)) {
                snprintf(buf, 256, "%04lld年%02lld月%02lld日", time.year(), time.month(), time.day());
                selections[10] += (", " + std::string(buf)) + "]";
            } else {
                selections[10] += ", +∞]";
            }

            Menu::Layout::Normal special(Menu::Layout::NormalGen);
            special.select_h = 50;                          // 由于选项过多必须修改高度
            special.select_w = 450;                         // 由于内容过多必须修改宽度
            int_t choice {Menu::showNormal("退出检索", "修改筛选条件", selections, special)};

            switch (choice) {
                case 0:
                    if (MessageBox(GetHWnd(), "退出检索将会丢失所写条件, 确认退出吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
					    circle = 0;
				    }
                    break;
                case 1:
                    revealSearchRes(user, users, books, cmp_condition);
                    break;
                case 2:
                    if (MessageBox(GetHWnd(), "确定要全部重置吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
					    cmp_condition = BookCmpCondition();
                        cmp_condition.unsetUnlimit(BookCmpCondition::Unlimit::status);
                        cmp_condition.status = BookStatus::on_sale;
				    }
                    break;
                case 3: select(cmp_condition.id, "书籍id", cmp_condition, BookCmpCondition::Unlimit::id); break;
                case 4: select(cmp_condition.title, "书名", cmp_condition, BookCmpCondition::Unlimit::title); break;
                case 5: select(cmp_condition.isbn, "ISBN", cmp_condition, BookCmpCondition::Unlimit::isbn); break;
                case 6: select(cmp_condition.author, "书籍作者", cmp_condition, BookCmpCondition::Unlimit::author); break;
                case 7: select(cmp_condition.press, "出版社", cmp_condition, BookCmpCondition::Unlimit::press); break;
                case 8: select(cmp_condition.category, cmp_condition); break;
                case 9: selectRange(cmp_condition.down_integrity, cmp_condition.up_integrity, "完整度", cmp_condition, BookCmpCondition::Unlimit::down_integrity, BookCmpCondition::Unlimit::up_integrity, Range<int_t>(min_integrity, max_integrity)); break;
                case 10: selectRange(cmp_condition.down_price, cmp_condition.up_price, "售价", cmp_condition, BookCmpCondition::Unlimit::down_price, BookCmpCondition::Unlimit::up_price, Range<float_t>(0.0)); break;
                case 11: selectRange(cmp_condition.down_publish_time, cmp_condition.up_publish_time, "时间", cmp_condition, BookCmpCondition::Unlimit::down_publish_time, BookCmpCondition::Unlimit::up_publish_time, Range<Time>()); break;
            }
        } while (circle);

    }
}