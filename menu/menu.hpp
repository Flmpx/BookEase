#ifndef BK_MENU_HPP_
#define BK_MENU_HPP_

#include <easyx.h>
#include "../base/base.hpp"
#include <list>
#include <vector>
#include <string>

namespace BK {

    /* 菜单 */
    class Menu {
        private:
            int_t back_w_;
            int_t back_h_;
            std::string back_content_;

            int_t grap_back_instru_;

            int_t instru_h_;
            std::string instru_;

            int_t select_w_;
            int_t select_h_;

        public:
            Menu(int_t back_w, int_t back_h, const std::string& back_content, int_t grap_back_instru, int_t instru_h, const std::string& instru, int_t select_w, int_t select_h);
            auto showNormal(const std::vector<std::string>& selections) const -> int_t;
            auto showBook(const std::vector<std::string>& selections, int_t grap_select_book, const std::string& book_tip, const std::shared_ptr<Book>& book) const -> int_t;
            auto showUser(const std::vector<std::string>& selections, int_t grap_select_user, const std::string& user_tip, const std::shared_ptr<User>& user) const -> int_t;
            auto showStatistics(const std::vector<std::string>& selections, int_t grap_select_statistics, const std::string& statistics_tip, const std::list<std::shared_ptr<Book>>& books, const std::list<std::shared_ptr<User>>& users) const -> int_t;
            auto showBooks(const std::vector<std::string>& selections, int_t diction_w, int_t diction_h, int_t grap_select_books, const std::string& books_tip, int_t row, int col, const std::list<std::shared_ptr<Book>>& books) const -> int_t;
    };

    /* 块式选项 */
    struct Selection {
        int_t l, t;
        int_t w, h;
        std::string tip;

        auto draw() const -> void;
        auto isClick(const ExMessage& msg) const -> bool;
        auto isHover(const ExMessage& msg) const -> bool;
    };

    auto showSelections(const std::vector<Selection>& blocks) -> int_t;
}
#endif