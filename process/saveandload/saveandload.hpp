#ifndef BK_SAVEANDLOAD_HPP_
#define BK_SAVEANDLOAD_HPP_

#include <fstream>
#include "../../base/base.hpp"

namespace BK {
    auto loadUsersFromFile(std::ifstream& fin) -> std::list<std::shared_ptr<User>>;
    auto loadUsersFromFile(const char* dir) -> std::list<std::shared_ptr<User>>;
    
    auto saveUserToFile(std::ofstream& fout, const std::list<std::shared_ptr<User>>& users) -> void;
    auto saveUserToFile(const char* dir, const std::list<std::shared_ptr<User>>& users) -> void;

    auto loadBooksFromFile(std::ifstream& fin) -> std::list<std::shared_ptr<Book>>;
    auto loadBooksFromFile(const char* dir) -> std::list<std::shared_ptr<Book>>;

    auto saveBooksToFile(std::ofstream& fout, const std::list<std::shared_ptr<Book>>& books) -> void;
    auto saveBooksToFile(const char* dir, const std::list<std::shared_ptr<Book>>& books) -> void;
}

#endif