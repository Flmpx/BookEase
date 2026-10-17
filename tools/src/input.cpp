/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "../tools.hpp"

#include <cstring>
#include <easyx.h>


namespace BK {

    namespace Tools {

        namespace Input {
            /**
             * @brief 输入字符串(可设置长度范围)
             * 
             * @param s 待输入的字符串
             * @param info 显示信息
             * @param tip 信息类型
             * @return 成功输入返回true, 取消输入返回false
             */
            auto element(std::string& s, const std::string& info, const std::string tip, const Range<uint_t> r) -> bool {
                bool changed {false};
                int circle {1};
        
                char buf[BUF_SIZE] {""};
                std::snprintf(buf, BUF_SIZE, "%s", s.c_str());
                do {
                    circle = 1;
                    if (InputBox(buf, BUF_SIZE, info.c_str(), tip.c_str(), buf, 0, 0, false)) {
                        if (r.contain(std::strlen(buf))) {
                            s = buf;
                            changed = true;
                            circle = 0;
                        } else {
                            MessageBox(GetHWnd(), "输入长度错误", "提示", MB_OK | MB_ICONWARNING);
                            circle = 1;
                        }
                    } else {
                        circle = 0;
                        changed = false;
                    }
                } while (circle);
        
                return changed;
            }
        
            /**
             * @brief 输入整数
             * 
             * @param i 待输入的整数
             * @param info 显示信息
             * @param tip 信息类型
             * @return 成功输入返回 true, 取消输入返回 false
             */
            auto element(int_t& i, const std::string& info, const std::string& tip, const Range<int_t> r) -> bool {
                bool changed {false};
                int circle {1};
        
                int_t tmp_num {0};
                char buf[BUF_SIZE] {""};
                std::snprintf(buf, BUF_SIZE, "%lld", i);
                do {
                    circle = 1;
                    if (InputBox(buf, BUF_SIZE, info.c_str(), tip.c_str(), buf, 0, 0, false)) {
                        int_t n {0};
                        if (std::sscanf(buf, "%lld%n", &tmp_num, &n) == 1 && buf[n] == '\0') {
                            if (r.contain(tmp_num)) {
                                i = tmp_num;
                                circle = 0;
                                changed = true; 
                            } else {
                                MessageBox(GetHWnd(), "输入数据范围错误", "提示", MB_OK | MB_ICONWARNING);
                                circle = 1;
                            }
                        } else {
                            MessageBox(GetHWnd(), "输入数据异常", "提示", MB_OK | MB_ICONWARNING);
                            circle = 1;
                        }
                    } else {
                        circle = 0;
                        changed = false;
                    }
                } while (circle);
        
                return changed;
            }
        
            /**
             * @brief 输入浮点数
             * 
             * @param i 待输入的浮点数
             * @param info 显示信息
             * @param tip 信息类型
             * @return 成功输入返回 true, 取消输入返回 false
             */
            auto element(float_t& f, const std::string& info, const std::string& tip, const Range<float_t> r) -> bool {
                bool changed {false};
                int circle {1};
        
                float_t tmp_num {0};
                char buf[BUF_SIZE] {""};
                std::snprintf(buf, BUF_SIZE, "%lf", f);
                do {
                    circle = 1;
                    if (InputBox(buf, BUF_SIZE, info.c_str(), tip.c_str(), buf, 0, 0, false)) {
                        int_t n {0};
                        if (std::sscanf(buf, "%lf%n", &tmp_num, &n) == 1 && buf[n] == '\0') {
                            if (r.contain(tmp_num)) {
                                f = tmp_num;
                                circle = 0;
                                changed = true;
                            } else {
                                MessageBox(GetHWnd(), "输入数据范围错误", "提示", MB_OK | MB_ICONWARNING);
                                circle = 1;
                            }
                        } else {
                            MessageBox(GetHWnd(), "输入数据异常", "提示", MB_OK | MB_ICONWARNING);
                            circle = 1;
                        }
                    } else {
                        circle = 0;
                        changed = false;
                    }
                } while (circle);
        
                return changed;
            }
        
            /**
             * @brief 输入日期
             * 
             * @param i 待输入的日期
             * @param info 显示信息
             * @param tip 信息类型
             * @return 成功输入返回 true, 取消输入返回 false
             */
            auto element(Time& t, const std::string& info, const std::string& tip, const Range<Time> r) -> bool {
                bool changed {false};
                int circle {1};
        
                int y {0}, m {0}, d {0};
                Time tmp_time {};
                char buf[BUF_SIZE] {""};
                std::snprintf(buf, BUF_SIZE, "%d %d %d", t.year(), t.month(), t.day());
                do {
                    circle = 1;
                    if (InputBox(buf, BUF_SIZE, info.c_str(), tip.c_str(), buf, 0, 0, false)) {
                        int_t n {0};
                        if (std::sscanf(buf, "%d%d%d%n", &y, &m, &d, &n) == 3 && buf[n] == '\0') {
                            tmp_time.set(y, m, d);
                            if (r.contain(tmp_time)) {
                                t = tmp_time;
                                circle = 0;
                                changed = true;
                            } else {
                                MessageBox(GetHWnd(), "输入数据范围错误", "提示", MB_OK | MB_ICONWARNING);
                                circle = 1;
                            }
                        } else {
                            MessageBox(GetHWnd(), "输入数据异常", "提示", MB_OK | MB_ICONWARNING);
                            circle = 1;
                        }
                    } else {
                        circle = 0;
                        changed = false;
                    }
                } while (circle);
        
                return changed;
            }

            /**
             * @brief 输入价格
             * 
             * @param p 待输入的价格
             * @param info 显示信息
             * @param tip 信息类型
             * @return 成功输入返回 true, 取消输入返回 false
             */
            auto element(Price& p, const std::string& info, const std::string& tip, const Range<Price> r) -> bool {
                bool changed {false};
                int circle {1};
        
                float_t tmp_num {0.0};
                Price tmp_price(p);
                char buf[BUF_SIZE] {""};
                std::snprintf(buf, BUF_SIZE, "%s", std::to_string(tmp_price).c_str());

                do {
                    circle = 1;
                    if (InputBox(buf, BUF_SIZE, info.c_str(), tip.c_str(), buf, 0, 0, false)) {
                        int_t n {0};
                        if (std::sscanf(buf, "%lf%n", &tmp_num, &n) == 1 && buf[n] == '\0') {
                            tmp_price.set(tmp_num);
                            if (r.contain(tmp_price)) {
                                p = tmp_price;
                                circle = 0;
                                changed = true;
                            } else {
                                MessageBox(GetHWnd(), "输入数据范围错误", "提示", MB_OK | MB_ICONWARNING);
                                circle = 1;
                            }
                        } else {
                            MessageBox(GetHWnd(), "输入数据异常", "提示", MB_OK | MB_ICONWARNING);
                            circle = 1;
                        }
                    } else {
                        circle = 0;
                        changed = false;
                    }
                } while (circle);

                return changed;
            }
        }
    }
}