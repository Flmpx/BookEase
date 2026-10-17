/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "../tools.hpp"

#include <easyx.h>

namespace BK {

    namespace Tools {

        namespace Authen {
            /**
             * @brief 验证密钥
             * 
             * @param key 密钥
             */
            auto key(const Key& key) -> bool {
                int circle {0};
                std::string password {};
                bool res {false};
                do {
                    circle = 1;
                    if (Input::element(password, "请输入密码(长度为8-16位)", "验证密钥", Range<uint_t>(8, 16))) {
                        if (key.verify(password)) {
                            circle = 0;
                            res = true;
                            MessageBox(GetHWnd(), "认证成功", "提示", MB_OK | MB_ICONINFORMATION);
                        } else {
                            circle = 1;
                            MessageBox(GetHWnd(), "认证失败, 请重试", "提示", MB_OK | MB_ICONWARNING);
                        }
        
                    } else {
                        circle = 0;
                        res = false;
                    }
                } while (circle);
        
                return res;
            }
        }
    }
}