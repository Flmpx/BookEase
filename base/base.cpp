/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#include "base.hpp"

#include <limits>
#include <sstream>


namespace BK {
    
    int_t Book::book_num {0};

    /**
     * @brief 返回书籍的售卖者
     * 
     * @param users 用户链表
     * @return 返回用户指针, 如果不存在该用户, 返回nullptr
     */
    auto Book::seller(std::list<std::shared_ptr<User>>& users) const -> std::shared_ptr<User> {
        for (auto& it : users) {
            if (seller_id == it->id) {
                return it;
            }
        }
        
        return nullptr;
    }

    /**
     * @brief 返回书籍的购买者
     * 
     * @param users 用户链表
     * @return 返回用户指针, 如果不存在该用户, 返回nullptr
     */
    auto Book::buyer(std::list<std::shared_ptr<User>>& users) const -> std::shared_ptr<User> {
        for (auto& it : users) {
            if (buyer_id == it->id) {
                return it;
            }
        }

        return nullptr;
    }

    /**
     * @brief 返回书籍的预定者
     * 
     * @param users 用户链表
     * @return 返回用户指针, 如果不存在该用户, 返回nullptr
     */
    auto Book::reserver(std::list<std::shared_ptr<User>>& users) const -> std::shared_ptr<User> {
        for (auto& it : users) {
            if (reserver_id == it->id) {
                return it;
            }
        }

        return nullptr;
    }

    /**
     * @brief 比较书籍是否符合要求
     * 
     * @param cmp_condition 书籍比较结构体
     */
    auto Book::operator==(const BookCmpCondition& cmp_condition) const -> bool {
        /* 比较书籍ID */
        if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::id) && 
            cmp_condition.id != id) {
            return false;
        }

        /* 比较书籍标题 */
        if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::title) &&
            title.find(cmp_condition.title) == std::string::npos) {
            return false;
        }

        /* 比较ISBN */
        if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::isbn) &&
            isbn.find(cmp_condition.isbn) == std::string::npos) {
            return false;
        }

        /* 比较作者 */
        if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::author) &&
            author.find(cmp_condition.author) == std::string::npos) {
            return false;
        }

        /* 比较出版社 */
        if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::press) && 
            press.find(cmp_condition.press) == std::string::npos) {
            return false;
        }

        /* 比较价格 */
        {
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::down_price) &&
                price < cmp_condition.down_price) {
                return false;
            }
    
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::up_price) &&
                price > cmp_condition.up_price) {
                return false;
            }
        }

        /* 比较书籍完整度 */
        {
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::down_integrity) && 
                integrity < cmp_condition.down_integrity) {
                return false;
            }

            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::up_integrity) && 
                integrity > cmp_condition.up_integrity) {
                return false;
            }

        }
        
        /* 比较发布时间 */
        {
            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::down_publish_time) &&
                publish_time < cmp_condition.down_publish_time) {
                return false;
            }

            if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::up_publish_time) &&
                publish_time > cmp_condition.up_publish_time) {
                return false;
            }

        }
        
        /* 比较类别 */
        if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::category) &&
            !(static_cast<uint_t>(cmp_condition.category) & static_cast<uint_t>(category))) {
            return false;
        }
        
        /* 比较状态 */
        if (!cmp_condition.isUmlimit(BookCmpCondition::Unlimit::status) &&
            !(static_cast<uint_t>(cmp_condition.status) & static_cast<uint_t>(status))) {
            return false;
        }

        return true;
    }
}

namespace BK {


    /**
     * @brief 对字符串进行hash操作
     * 
     * @param str 输入字符串
     * @return 返回无符号整数
     */
    auto Key::hash(const std::string& str) const -> uint_t {
        uint_t res {0};
        for (auto it : str) {
            res = ((res << 5) + res) + it;
        }

        return res;
    }

    /**
     * @brief 生成盐并存储在内部的salt_变量中
     * 
     */
    auto Key::generateSalt() -> void {
        srand(time(nullptr));
        std::stringstream out {};
        const std::string flag("ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()<>{}|");
        
        for (int i = 0; i < len_; i++) {
            out << flag[rand() % flag.size()];
        }

        salt_ = out.str();
    }

    /**
     * @brief 构建一个密钥, 新用户创建时使用
     * 
     * @param password 密钥(账号+密码)
     */
    Key::Key(const std::string& password) {
        generateSalt();
        uint_t res {hash(password + salt_)};
        std::stringstream out {};
        out << std::hex << res;

        hash_key_ = out.str();
    }

    /**
     * @brief 构建一个密钥, 已存在用户使用
     * 
     * @param salt 盐
     * @param hash_key Hash后的密钥 
     */
    Key::Key(const std::string& salt, const std::string& hash_key) {
        salt_ = salt;
        hash_key_ = hash_key;
    }

    /**
     * @brief 验证密码是否正确
     * 
     * @param password 密码
     */
    auto Key::verify(const std::string& password) const -> bool {
        uint_t res {hash(password + salt_)};
        std::stringstream out {};
        out << std::hex << res;

        if (out.str() == hash_key_) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief 修改密码
     * 
     * @param new_password 新密码
     */
    auto Key::change(const std::string& new_password) -> void {
        generateSalt();
        uint_t res {hash(new_password + salt_)};
        std::stringstream out {};
        out << std::hex << res;

        hash_key_ = out.str();
    }
}

namespace BK {

    /**
     * @brief 构造一个新用户
     * 
     * @param password 密钥(用户名+密码)
     */
    User::User(const std::string& password) : key(password) {}

    /**
     * @brief 构建一个已经存在的用户
     * 
     * @param salt 盐
     * @param hash_key Hash后的密钥
     */
    User::User(const std::string salt, const std::string hash_key) : key(salt, hash_key) {}

    /**
     * @brief 比较用户是否符合要求
     * 
     * @param cmp_condition 用户比较条件
     */
    auto User::operator==(const UserCmpCondition& cmp_condition) const -> bool {
        
        /* 比较用户名 */
        if (!cmp_condition.isUmlimit(UserCmpCondition::Unlimit::name) &&
            name.find(cmp_condition.name) == std::string::npos) {
            return false;
        }

        /* 比较ID */
        if (!cmp_condition.isUmlimit(UserCmpCondition::Unlimit::id) &&
            cmp_condition.id != id) {
            return false;
        }
        

        return true;
    }

    /**
     * @brief 按条件获取用户的书籍
     * 
     * @param books 书籍指针链表
     * @param status 书籍状态(默认全部)
     * @param category 书籍类别(默认全部)
     * @return 筛选后的书籍指针链表
     */
    auto User::books(std::list<std::shared_ptr<Book>>& books, BookStatus status, BookCategory category) const -> std::list<std::shared_ptr<Book>> {
        std::list<std::shared_ptr<Book>> ret {};
        for (auto& it : books) {
            if 
            (
                /* 书籍状态符合要求 */
                (static_cast<uint_t>(status) & static_cast<uint_t>(it->status)) &&  

                /* 书籍类别符合要求 */
                (static_cast<uint_t>(category) & static_cast<uint_t>(it->category)) &&      

                /* 书籍的某个id与用户有关(售卖者id永远有效, 预定者id只在预定时候有效, 购买者id只在已购后有效) */
                (it->seller_id == id || (it->status == BookStatus::reserved && it->reserver_id == id) || (it->status == BookStatus::sold && it->buyer_id == id))
                
            ) 
            {
                ret.push_back(it);
            }
        }

        return ret;
    }
}