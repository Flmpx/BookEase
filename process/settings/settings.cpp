/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "settings.hpp"
#include "../../menu/menu.hpp"
#include "../../tools/tools.hpp"
#include "../about/about.hpp"

namespace BK {

    namespace {

        /* 设置 > 多书籍界面 > 行列数 */
        auto settings_bookspage_rc(std::shared_ptr<User>& user, std::shared_ptr<Settings>& sets, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int circle {1};
            
            do {
                circle = 1;
                cleardevice();

                std::vector<std::string> selections {
                    "行数", "列数"
                };

                selections[0] += (": " + std::to_string(sets->bookspage.row));
                selections[1] += (": " + std::to_string(sets->bookspage.col));

                int_t choice {Menu::showNormal("返回", "选择内容", selections, Menu::Layout::NormalGen)};

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1:
                        if (Tools::Input::element(sets->bookspage.row, "输入行数(1-4)", "输入", Range<int_t>(1, 4))) {
                            Tools::File::saveSettings(SETTINGS_FILE_DIR, sets);
                        }
                        break;
                    case 2:
                        if (Tools::Input::element(sets->bookspage.col, "输入列数(1-6)", "输入", Range<int_t>(1, 6))) {
                            Tools::File::saveSettings(SETTINGS_FILE_DIR, sets);
                        }
                        break;
                }

            } while (circle);
        }

        /* 设置 > 多书籍界面 */
        auto settings_bookspage(std::shared_ptr<User>& user, std::shared_ptr<Settings>& sets, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int circle {1};
            std::vector<std::string> selections {
                "行列数"
            };

            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showNormal("返回", "选择内容", selections, Menu::Layout::NormalGen)};

                switch (choice) {
                    case 0: circle = 0; break;
                    case 1:
                        settings_bookspage_rc(user, sets, users, books);
                        break;
                }

            } while (circle);
        }

    }

    /* 设置 */
    auto settings(std::shared_ptr<User>& user, std::shared_ptr<Settings>& sets, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) -> void {
        int circle {1};
        std::vector<std::string> selections {
            "多书籍界面", "关于"
        };

        do {
            circle = 1;
            cleardevice();
            int_t choice {Menu::showNormal("返回", "选择内容", selections, Menu::Layout::NormalGen)};

            switch (choice) {
                case 0: circle = 0; break;
                case 1:
                    settings_bookspage(user, sets, users, books);
                    break;
                case 2:
                    about(user, sets, users, books);
                    break;
            }

        } while (circle);

    }
}