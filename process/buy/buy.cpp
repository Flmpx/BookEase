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
        namespace Select {
            void category(BookCategory& c, BookCmpCondition& cmp_codition) {
                int circle {1};
                Menu menu(80, 30, "保存并退出", 30, 20, "选择操作", 200, 90);
                do {
                    circle = 1;
                    cleardevice();
                    std::vector<std::string> selections {
                        "重置筛选信息", "书籍类别"
                    };
                    if (!cmp_codition.isUmlimit(BookCmpCondition::Unlimit::category)) {
                        selections[1] += (": " + getBookCategoryString(c));
                    }
                    int_t choice {menu.showNormal(selections)};

                    switch (choice) {
                        case 0: 
                            circle = 0;
                            break;
                        case 1:
                            cmp_codition.setUnlimit(BookCmpCondition::Unlimit::category);
                            break;
                        case 2:
                            cmp_codition.unsetUnlimit(BookCmpCondition::Unlimit::category);
                            Change::bookCategory(c);
                            break;
                    }

                } while (circle);
            } 

            auto string(std::string& str, const std::string& selection, BookCmpCondition& cmp_codition, BookCmpCondition::Unlimit u) -> void {
                int circle {1};
                Menu menu(80, 30, "保存并退出", 30, 20, "选择操作", 200, 90);
                do {
                    circle = 1;
                    cleardevice();
                    std::vector<std::string> selections {
                        "重置筛选信息", selection
                    };
                    if (!cmp_codition.isUmlimit(u)) {
                        selections[1] += (": " + str);
                    }
                    int_t choice {menu.showNormal(selections)};

                    switch (choice) {
                        case 0: 
                            circle = 0;
                            break;
                        case 1:
                            cmp_codition.setUnlimit(u);
                            break;
                        case 2:
                            cmp_codition.unsetUnlimit(u);
                            Input::string(str, "输入" + selection, "输入");
                            break;
                    }

                } while (circle);
            } 

            auto interger(int_t& i, const std::string& selection, BookCmpCondition& cmp_codition, BookCmpCondition::Unlimit u) -> void {
                int circle {1};
                Menu menu(80, 30, "保存并退出", 30, 20, "选择操作", 200, 90);
                do {
                    circle = 1;
                    cleardevice();
                    std::vector<std::string> selections {
                        "重置筛选信息", selection
                    };
                    if (!cmp_codition.isUmlimit(u)) {
                        selections[1] += (": " + std::to_string(i));
                    }
                    int_t choice {menu.showNormal(selections)};

                    switch (choice) {
                        case 0: 
                            circle = 0;
                            break;
                        case 1:
                            cmp_codition.setUnlimit(u);
                            break;
                        case 2:
                            cmp_codition.unsetUnlimit(u);
                            Input::integer(i, "输入" + selection, "输入");
                            break;
                    }

                } while (circle);
            }

            auto integrityRange(int_t& down_integrity, int_t& up_integrity, BookCmpCondition& cmp_codition) -> void {
                int circle {1};
                int circle_in {1};
                Menu menu(80, 30, "保存并退出", 30, 20, "选择操作", 200, 90);
                do {
                    circle = 1;
                    cleardevice();
                    std::vector<std::string> selections {
                        "重置筛选信息", "完整度上限", "完整度下限"
                    };
                    if (cmp_codition.isUmlimit(BookCmpCondition::Unlimit::up_integrity)) {
                        selections[1] += ": +∞";
                    } else {
                        selections[1] += (": " + std::to_string(up_integrity));
                    }
                    if (cmp_codition.isUmlimit(BookCmpCondition::Unlimit::down_integrity)) {
                        selections[2] += ": -∞";
                    } else {
                        selections[2] += (": " + std::to_string(down_integrity));
                    }
                    int_t choice {menu.showNormal(selections)};
                    int_t tmp_integrity;

                    switch (choice) {
                        case 0: 
                            circle = 0;
                            break;
                        case 1:
                            cmp_codition.setUnlimit(BookCmpCondition::Unlimit::up_integrity);
                            cmp_codition.setUnlimit(BookCmpCondition::Unlimit::down_integrity);
                            break;
                        case 2:
                            tmp_integrity = cmp_codition.up_integrity;
                            do {
                                circle_in = 1;
                                if (Input::integer(tmp_integrity, "输入完整度上限", "输入")) {
                                    if (!cmp_codition.isUmlimit(BookCmpCondition::Unlimit::down_integrity) && tmp_integrity < cmp_codition.down_integrity) {
                                        MessageBox(GetHWnd(), "上限不能小于下限", "提示", MB_OK | MB_ICONWARNING);
                                        circle_in = 1;
                                    } else {
                                        cmp_codition.unsetUnlimit(BookCmpCondition::Unlimit::up_integrity);
                                        cmp_codition.up_integrity = tmp_integrity;
                                        circle_in = 0;
                                    }
                                } else {
                                    circle_in = 0;
                                }
                            } while (circle_in);
                            break;
                        case 3:
                            tmp_integrity = cmp_codition.down_integrity;
                            do {
                                circle_in = 1;
                                if (Input::integer(tmp_integrity, "输入完整度下限", "输入")) {
                                    if (!cmp_codition.isUmlimit(BookCmpCondition::Unlimit::up_integrity) && tmp_integrity > cmp_codition.up_integrity) {
                                        MessageBox(GetHWnd(), "下限不能大于下限", "提示", MB_OK | MB_ICONWARNING);
                                        circle_in = 1;
                                    } else {
                                        cmp_codition.unsetUnlimit(BookCmpCondition::Unlimit::down_integrity);
                                        cmp_codition.down_integrity = tmp_integrity;
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
            
            auto priceRange(float_t& down_price, float_t& up_price, const std::string selection, BookCmpCondition& cmp_codition, BookCmpCondition::Unlimit down_u, BookCmpCondition::Unlimit up_u) -> void {
                int circle {1};
                int circle_in {1};
                Menu menu(80, 30, "保存并退出", 30, 20, "选择操作", 200, 90);
                do {
                    circle = 1;
                    cleardevice();
                    std::vector<std::string> selections {
                        "重置筛选信息", selection + "上限", selection + "下限"
                    };
                    if (cmp_codition.isUmlimit(up_u)) {
                        selections[1] += ": +∞";
                    } else {
                        selections[1] += (": " + std::to_string(up_price));
                    }
                    if (cmp_codition.isUmlimit(down_u)) {
                        selections[2] += ": -∞";
                    } else {
                        selections[2] += (": " + std::to_string(down_price));
                    }
                    int_t choice {menu.showNormal(selections)};
                    float_t tmp_price;

                    switch (choice) {
                        case 0: 
                            circle = 0;
                            break;
                        case 1:
                            cmp_codition.setUnlimit(up_u);
                            cmp_codition.setUnlimit(down_u);
                            break;
                        case 2:
                            tmp_price = up_price;
                            do {
                                circle_in = 1;
                                if (Input::floatPoint(tmp_price, "输入" + selection + "上限", "输入")) {
                                    if (!cmp_codition.isUmlimit(down_u) && tmp_price < cmp_codition.down_price - EPS) {
                                        MessageBox(GetHWnd(), "上限不能小于下限", "提示", MB_OK | MB_ICONWARNING);
                                        circle_in = 1;
                                    } else {
                                        cmp_codition.unsetUnlimit(up_u);
                                        cmp_codition.up_price = tmp_price;
                                        circle_in = 0;
                                    }
                                } else {
                                    circle_in = 0;
                                }
                            } while (circle_in);
                            break;
                        case 3:
                            tmp_price = down_price;
                            do {
                                circle_in = 1;
                                if (Input::floatPoint(tmp_price, "输入" + selection + "下限", "输入")) {
                                    if (!cmp_codition.isUmlimit(up_u) && tmp_price > cmp_codition.up_price + EPS) {
                                        MessageBox(GetHWnd(), "下限不能大于下限", "提示", MB_OK | MB_ICONWARNING);
                                        circle_in = 1;
                                    } else {
                                        cmp_codition.unsetUnlimit(down_u);
                                        cmp_codition.down_price = tmp_price;
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

            auto timeRange(time_t& down_time, time_t& up_time, const std::string selection, BookCmpCondition& cmp_codition, BookCmpCondition::Unlimit down_u, BookCmpCondition::Unlimit up_u) -> void {
                int circle {1};
                int circle_in {1};
                Menu menu(80, 30, "保存并退出", 30, 20, "选择操作", 200, 90);
                char buf[256] {""};
                do {
                    circle = 1;
                    cleardevice();
                    std::vector<std::string> selections {
                        "重置筛选信息", selection + "上限", selection + "下限"
                    };

                    struct tm time;
                    if (cmp_codition.isUmlimit(up_u)) {
                        selections[1] += ": +∞";
                    } else {
                        localtime_s(&time, &up_time);
                        snprintf(buf, 256, "%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
                        selections[1] += (": " + std::string(buf));
                    }
                    if (cmp_codition.isUmlimit(down_u)) {
                        selections[2] += ": -∞";
                    } else {
                        localtime_s(&time, &down_time);
                        snprintf(buf, 256, "%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
                        selections[2] += (": " + std::string(buf));
                    }
                    int_t choice {menu.showNormal(selections)};
                    time_t tmp_time;

                    switch (choice) {
                        case 0: 
                            circle = 0;
                            break;
                        case 1:
                            cmp_codition.setUnlimit(up_u);
                            cmp_codition.setUnlimit(down_u);
                            break;
                        case 2:
                            tmp_time = up_time;
                            do {
                                circle_in = 1;
                                if (Input::date(tmp_time, "输入" + selection + "上限", "输入")) {
                                    if (!cmp_codition.isUmlimit(down_u) && tmp_time < down_time) {
                                        MessageBox(GetHWnd(), "上限不能小于下限", "提示", MB_OK | MB_ICONWARNING);
                                        circle_in = 1;
                                    } else {
                                        cmp_codition.unsetUnlimit(up_u);
                                        up_time = tmp_time;
                                        circle_in = 0;
                                    }
                                } else {
                                    circle_in = 0;
                                }
                            } while (circle_in);
                            break;
                        case 3:
                            tmp_time = down_time;
                            do {
                                circle_in = 1;
                                if (Input::date(tmp_time, "输入" + selection + "下限", "输入")) {
                                    if (!cmp_codition.isUmlimit(up_u) && tmp_time > up_time) {
                                        MessageBox(GetHWnd(), "下限不能大于下限", "提示", MB_OK | MB_ICONWARNING);
                                        circle_in = 1;
                                    } else {
                                        cmp_codition.unsetUnlimit(down_u);
                                        down_time = tmp_time;
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

        }

        auto readyToReserve(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books, std::shared_ptr<Book>& book) -> bool {
            int_t circle {1};
            std::vector<std::string> selelctions {
                "预定"
            };
            bool reserved {false};
            Menu menu(80, 30, "返回", 30, 20, "选择操作", 200, 90);
            do {
                circle = 1;
                int_t choice {menu.showBook(selelctions, 10, "选中书籍的详情", book)};
                switch (choice) {
                    case 0: circle = 0; break;
                    case 1:
                        if (book->seller_id != user->id) {
                            if (MessageBox(GetHWnd(), "确定要预定吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                                book->reserver_id = user->id;
                                book->reserve_time = std::time(nullptr);
                                book->status = BookStatus::reserved;
    
                                File::saveBooksToFile(BOOKS_FILE_DIR, books);
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

            Menu menu(80, 30, "返回", 30, 20, "选择排序方式", 200, 90);
            std::vector<std::string> selections {
                "按价格升序", "按价格降序", "按发布时间升序", "按发布时间降序"
            };
            int_t circle {1};
            do {
                circle = 1;
                int_t choice {menu.showBooks(selections, 40, 40, 10, "当前检索到的所有书籍", 3, 2, now_books)};
                if (choice < 0) {
                    int_t idx {-choice + 1};
                    if (readyToReserve(user, users, books, *std::next(books.begin(), idx))) {
                        now_books.erase(std::next(now_books.begin(), idx));
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
        Menu menu(80, 30, "退出检索", 30, 20, "修改筛选条件", 450, 50);
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

            struct tm time;
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::up_publish_time)) {
                localtime_s(&time, &cmp_condition.down_publish_time);
                snprintf(buf, 256, "%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
                selections[10] += (": [" + std::string(buf));
            } else {
                selections[10] += ": [-∞";
            }
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::up_publish_time)) {
                localtime_s(&time, &cmp_condition.up_publish_time);
                snprintf(buf, 256, "%04d年%02d月%02d日", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
                selections[10] += (", " + std::string(buf)) + "]";
            } else {
                selections[10] += ", +∞]";
            }

            int_t choice {menu.showNormal(selections)};
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
                case 3: Select::interger(cmp_condition.id, "书籍id", cmp_condition, BookCmpCondition::Unlimit::id); break;
                case 4: Select::string(cmp_condition.title, "书名", cmp_condition, BookCmpCondition::Unlimit::title); break;
                case 5: Select::string(cmp_condition.isbn, "ISBN", cmp_condition, BookCmpCondition::Unlimit::isbn); break;
                case 6: Select::string(cmp_condition.author, "书籍作者", cmp_condition, BookCmpCondition::Unlimit::author); break;
                case 7: Select::string(cmp_condition.press, "出版社", cmp_condition, BookCmpCondition::Unlimit::press); break;
                case 8: Select::category(cmp_condition.category, cmp_condition); break;
                case 9: Select::integrityRange(cmp_condition.down_integrity, cmp_condition.up_integrity, cmp_condition); break;
                case 10: Select::priceRange(cmp_condition.down_price, cmp_condition.up_price, "售价", cmp_condition, BookCmpCondition::Unlimit::down_price, BookCmpCondition::Unlimit::up_price); break;
                case 11: Select::timeRange(cmp_condition.down_publish_time, cmp_condition.up_publish_time, "书籍发布时间", cmp_condition, BookCmpCondition::Unlimit::down_publish_time, BookCmpCondition::Unlimit::up_publish_time); break;
            }
        } while (circle);
        
    }
}