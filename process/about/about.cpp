#include "about.hpp"
#include <vector>
#include <string>
#include "../../menu/menu.hpp"
#include <easyx.h>

namespace BK {

    namespace {
        auto about_statistics(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) {
            int_t circle {1};
            std::vector<std::string> selections {
                
            };
            Menu menu(80, 30, "返回", 30, 20, "仅查看", 200, 90);
            do {
                circle = 1;
                cleardevice();
                int_t choice {menu.showStatistics(selections, 10, "统计信息", books, users)};

                switch (choice) {
                    case 0: circle = 0; break;
                }

            } while (circle);
        }
    }

    auto about(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) -> void {
        int_t circle {1};
            
        std::vector<std::string> selections {
            "统计信息"
        };
        Menu menu(80, 30, "返回", 30, 20, "选择操作", 200, 90);
        do {
            circle = 1;
            cleardevice();
            int_t choice {menu.showNormal(selections)};

            switch (choice) {
                case 0: circle = 0; break;
                case 1: 
                    about_statistics(user, users, books);
                    break;
            }
        } while (circle);
    }
}