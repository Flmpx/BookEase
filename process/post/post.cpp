/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "post.hpp"
#include "../../menu/menu.hpp"
#include <ctime>
#include "../saveandload/saveandload.hpp"
#include "../../tools/tools.hpp"

namespace BK {
    auto post(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) -> void {
        auto tmp_book {std::make_shared<Book>()};
        tmp_book->seller_id = user->id;
        tmp_book->id = Book::book_num + 1;


        std::vector<std::string> selections {
            "确认发布", "进行修改"
        };

        int_t circle {1};
        do {
            circle = 1;
            cleardevice();
            int_t choice {Menu::showBook("取消发布", "选择操作", selections, "当前待发布书籍详情", tmp_book, Menu::Layout::BookGen)};

            switch (choice) {
                case 0: 
                    if (MessageBox(GetHWnd(), "确定要取消发布吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
					    circle = 0;
				    }
                    break;
                case 1:
                    tmp_book->publish_time.set(std::time(nullptr));
                    tmp_book->status = BookStatus::on_sale;
                    books.push_back(tmp_book);
                    saveBooksToFile(BOOKS_FILE_DIR, books);
                    Book::book_num++;
                    MessageBox(GetHWnd(), "发布成功", "提示", MB_OK | MB_ICONINFORMATION);
                    circle = 0;
                    break;
                case 2:
                    if (change(tmp_book)) {
                        MessageBox(GetHWnd(), "修改保存成功", "提示", MB_OK | MB_ICONINFORMATION);
                    }
                    break;
            }
        } while (circle);
    }
}