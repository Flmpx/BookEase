/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "login.hpp"
#include "../../tools/tools.hpp"
#include <easyx.h>
#include <ctime>
#include "../saveandload/saveandload.hpp"

namespace BK {

    namespace {
        auto find(std::list<std::shared_ptr<User>>& users, int_t id) -> std::shared_ptr<User> {
            for (auto& it : users) {
                if (it->id == id) {
                    return it;
                }
            }

            return nullptr;
        }

        auto createUser(int_t id) -> std::shared_ptr<User> {
            std::string password {};
            int circle {1};
            std::shared_ptr<User> user {nullptr};
            do {
                circle = 1;
                if (input(password, "请输入密码", "输入用户信息", Range<uint_t>(8, 16))) {
                    user.reset(new User(password));
                    user->id = id;
                    user->register_time.set(std::time(nullptr));
                    circle = 0;
                } else {
                    circle = 0;
                    user = nullptr;
                }
            } while (circle);

            return user;
        }
    }

    /**
     * @brief 登录
     * 
     * @param users 用户链表
     * @return 若登录成功, 返回用户, 否则 nullptr
     */
    auto login(std::list<std::shared_ptr<User>>& users) -> std::shared_ptr<User> {
        int_t id {0};
        int circle {1};
        std::shared_ptr<User> user {nullptr};
        do {
            circle = 1;
            if (input(id, "请输入ID", "请输入用户信息", Range<int_t>(0))) {   // 输入学号
                user = find(users, id);
                if (user != nullptr) {
                    std::string password {};
                    if (authenKey(user->key)) {
                        circle = 0;
                    } else {
                        circle = 1;
                        user = nullptr;
                    }
                } else {
                    MessageBox(GetHWnd(), "用户不存在, 检查是否输入错误或者进行注册", "提示", MB_OK | MB_ICONWARNING);
                    circle = 1;
                }
            } else {
                user = nullptr;
                circle = 0;
            }
        } while (circle);

        return user;
    }

    /**
     * @brief 注册
     * 
     * @param users 用户链表
     * @return 若注册成功, 返回新注册的用户, 否则 nullptr
     */
    auto regis(std::list<std::shared_ptr<User>>& users) -> std::shared_ptr<User> {
        int_t id {0};
        int circle {1};
        std::shared_ptr<User> user {nullptr};
        do {
            circle = 1;
            if (input(id, "请输入学号", "输入用户信息", Range<int_t>(0))) {
                user = find(users, id);
                if (user == nullptr) {
                    user = createUser(id);
                    if (user != nullptr) {
                        users.push_back(user);
                        saveUserToFile(USERS_FILE_DIR, users);
                        MessageBox(GetHWnd(), "注册成功, 请前往登录", "提示", MB_OK | MB_ICONINFORMATION);
                        circle = 0;
                    } else {
                        circle = 1;
                    }
                } else {
                    circle = 0;
                    MessageBox(GetHWnd(), "当前用户已注册, 请前往登录", "提示", MB_OK | MB_ICONINFORMATION);
                    user = nullptr;
                }
            } else {
                circle = 0;
                user = nullptr;
            }
        } while (circle);

        return user;
    } 
}