/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#ifndef BK_SETTINGS_HPP_
#define BK_SETTINGS_HPP_

#include "../../base/base.hpp"

namespace BK {
    auto settings(std::shared_ptr<User>& user, std::shared_ptr<Settings>& sets, std::list<std::shared_ptr<User>>& users, std::list<std::shared_ptr<Book>>& books) -> void;
}

#endif