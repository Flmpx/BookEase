/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "about.hpp"
#include "../../menu/menu.hpp"

#include <vector>
#include <string>
#include <easyx.h>


namespace BK {

    namespace {
        
        /* 关于 > 统计信息 */
        auto about_statistics(std::shared_ptr<User>& user, std::shared_ptr<Settings>& sets, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};

            std::vector<std::string> selections {};

            do {
                circle = 1;
                cleardevice();
                int_t choice {Menu::showStatistics("返回", "仅查看", selections, "统计信息", books, users, Menu::Layout::StatisticsGen)};
                
                switch (choice) {
                    case 0: circle = 0; break;
                }

            } while (circle);
        }
    }

    /* 关于 */
    auto about(std::shared_ptr<User>& user, std::shared_ptr<Settings>& sets, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) -> void {
        int_t circle {1};
            
        std::vector<std::string> selections {
            "统计信息"
        };
        do {
            circle = 1;
            cleardevice();
            int_t choice {Menu::showNormal("返回", "选择操作", selections, Menu::Layout::NormalGen)};

            switch (choice) {
                case 0: circle = 0; break;
                case 1: 
                    about_statistics(user, sets, users, books);
                    break;
            }
        } while (circle);
    }
}