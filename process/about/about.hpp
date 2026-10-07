#ifndef BK_ABOUT_HPP_
#define BK_ABOUT_HPP_

#include "../../base/base.hpp"

namespace BK {
    auto about(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) -> void;
}

#endif