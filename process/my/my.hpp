#ifndef BK_MY_HPP_
#define BK_MY_HPP_

#include "../../base/base.hpp"

namespace BK {
    auto my(std::shared_ptr<User>& user, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) -> void;
}

#endif