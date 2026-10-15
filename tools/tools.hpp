/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#ifndef BK_TOOLS_HPP_
#define BK_TOOLS_HPP_

#include "../base/base.hpp"
#include <fstream>

namespace BK {

    /* 工具函数 */
    namespace Tools {
        
        /* 输入内容到窗口 */
        namespace Print {
            auto user(const std::shared_ptr<User>& user, int_t l, int_t t, int_t w, int_t h, bool reveal_time = false) -> void;
            auto book(const std::shared_ptr<Book>& book, int_t l, int_t t, int_t w, int_t h, bool reveal_time = false) -> void;
            auto statistics(const std::list<std::shared_ptr<Book>>& books, const std::list<std::shared_ptr<User>>& users, int_t l, int_t t, int_t w, int_t h) -> void;
        }
    
        /* 绘制图形到窗口 */
        namespace Draw {
            auto rectangleBlock(const std::string& text, int_t l, int_t t, int_t w, int_t h) -> void;
            auto roundRectleBlock(const std::string& text, int_t l, int_t t, int_t w, int_t h) -> void;
        }
        
        /* 输入内容 */
        namespace Input {
            auto element(std::string& s, const std::string& info, const std::string tip, const Range<uint_t> r = Range<uint_t>()) -> bool;
            auto element(int_t& i, const std::string& info, const std::string& tip, const Range<int_t> r = Range<int_t>()) -> bool;
            auto element(float_t& f, const std::string& info, const std::string& tip, const Range<float_t> r = Range<float_t>()) -> bool;
            auto element(Time& t, const std::string& info, const std::string& tip, const Range<Time> r = Range<Time>()) -> bool;
            auto element(Price& p, const std::string& info, const std::string& tip, const Range<Price> r = Range<Price>()) -> bool;
        }
    
        /* 修改内容 */
        namespace Change {
            auto bookCategory(BookCategory& categroy) -> void;
            auto key(Key& key) -> bool;
            auto user(std::shared_ptr<User>& user) -> bool;
            auto book(std::shared_ptr<Book>& book) -> bool;
        }

        /* 验证信息 */
        namespace Authen {
            auto key(const Key& user) -> bool;
        }

        /* 文件读写 */
        namespace File {
            auto loadUsers(std::ifstream& fin) -> std::list<std::shared_ptr<User>>;
            auto loadUsers(const char* dir) -> std::list<std::shared_ptr<User>>;
            
            auto saveUsers(std::ofstream& fout, const std::list<std::shared_ptr<User>>& users) -> void;
            auto saveUsers(const char* dir, const std::list<std::shared_ptr<User>>& users) -> void;

            auto loadBooks(std::ifstream& fin) -> std::list<std::shared_ptr<Book>>;
            auto loadBooks(const char* dir) -> std::list<std::shared_ptr<Book>>;

            auto saveBooks(std::ofstream& fout, const std::list<std::shared_ptr<Book>>& books) -> void;
            auto saveBooks(const char* dir, const std::list<std::shared_ptr<Book>>& books) -> void;
        }

    }
}


#endif