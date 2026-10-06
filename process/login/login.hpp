#ifndef BK_LOGIN_HPP_
#define BK_LOGIN_HPP_

#include "../../base/base.hpp"

namespace BK {
    auto authenUser(std::shared_ptr<User>& user) -> bool;
    auto login(std::list<std::shared_ptr<User>>& users) -> std::shared_ptr<User> ;
    auto regis(std::list<std::shared_ptr<User>>& users) -> std::shared_ptr<User>;
}

#endif