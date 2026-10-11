/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include <iostream>
#include <easyx.h>
#include "menu/menu.hpp"
#include "process/saveandload/saveandload.hpp"
#include "process/login/login.hpp"
#include "process/mainpage/mainpage.hpp"

auto WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) -> int
{
    /* 创建窗口 */
	initgraph(1280, 720);
	setbkcolor(RGB(253, 254, 249));
	cleardevice();
	settextstyle(16, 0, "宋体");
    setbkmode(TRANSPARENT);
	settextcolor(BLACK);
    
    /* 载入 */
    std::list<std::shared_ptr<BK::User>> users {BK::loadUsersFromFile(BK::USERS_FILE_DIR)};
    std::list<std::shared_ptr<BK::Book>> books {BK::loadBooksFromFile(BK::BOOKS_FILE_DIR)};
    std::shared_ptr<BK::User> user {nullptr};


    /* 登录 注册 进入主界面 */
    BK::int_t block_w {200}, block_h {90};
    BK::int_t screen_w {getwidth()}, screen_h {getheight()};
    std::vector<BK::Selection> selections {
        {screen_w / 4 - block_w / 2, screen_h / 3 * 2 - block_h / 2, block_w, block_h, "注册"},
        {screen_w / 2 + (screen_w / 4 - block_w / 2), screen_h / 3 * 2 - block_h / 2, block_w, block_h, "登录"}
    };
    
    int circle {1};
    do {
        circle = 1;
        cleardevice();
        BK::int_t choice {BK::showSelections(selections)};
        switch (choice) {
            case 0: user = BK::regis(users); break;
            case 1: user = BK::login(users); break;
        }
        if (user) BK::mainpage(user, users, books);
    } while (circle);

    return 0;
}