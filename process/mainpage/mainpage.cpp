/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "mainpage.hpp"
#include "../../menu/menu.hpp"
#include "../buy/buy.hpp"
#include "../my/my.hpp"
#include "../post/post.hpp"
#include "../about/about.hpp"
#include "../settings/settings.hpp"
#include <easyx.h>


namespace BK {

    auto mainpage(std::shared_ptr<User>& user, std::shared_ptr<Settings>& sets, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) -> void {
        int circle {1};
        std::vector<std::string> selections {
            "买书", "卖书", "我的", "设置",
        };

        do {
            circle = 1;
            cleardevice();
            int_t choice {Menu::showNormal("退出登录", "选中操作", selections, Menu::Layout::NormalGen)};
            switch (choice) {
                case 0: 
                    if (MessageBox(GetHWnd(), "确认退出吗?", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                        circle = 0;
                    }
                    break;
                case 1: buy(user, sets, users, books); break;
                case 2: post(user, sets, users, books);   break;
                case 3: my(user, sets, users, books);     break;
                case 4: settings(user, sets, users, books); break;
            }
        } while (circle);
    }
}