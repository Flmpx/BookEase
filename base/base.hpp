#ifndef BK_BASE_HPP_
#define BK_BASE_HPP_

#include <string>
#include <cstdint>
#include <list>
#include <memory>
#include <limits>

namespace BK {
    inline constexpr const char* BOOKS_FILE_DIR {"./bkdata/books.json"};        // 书籍数据文件地址
    inline constexpr const char* USERS_FILE_DIR {"./bkdata/users.json"};        // 用户数据文件地址

    using int_t = int64_t;                                      // 有符号整数
    using uint_t = uint64_t;                                    // 无符号整数
    using float_t = double;                                     // 浮点数

    constexpr float_t EPS                   {1e-9};             // 浮点数比较所用误差

    constexpr int_t min_integrity           {0};                // 最小书籍完整度
    constexpr int_t max_integrity           {100};              // 最小书籍完整度

    /* 无效值用于判断是否存在, 比如预定者的id为-1, 则为无预定者 */
    namespace invalid {
        constexpr int_t id              {-1};               // 无效Id
        constexpr time_t time           {-1};               // 无效时间
    }
}


namespace BK {
    
    /* 书籍类别 */
    enum class BookCategory : uint_t {
        textbook    = 0x1 << 0,                         // 教材
        fiction     = 0x1 << 1,                         // 小说
        academic    = 0x1 << 2,                         // 学术类
        exam        = 0x1 << 3,                         // 考试类
        other       = 0x1 << 4,                         // 其他
        all         = textbook | fiction | academic | exam | other
    };

    inline auto operator|(BookCategory c1, BookCategory c2) -> BookCategory {
        return static_cast<BookCategory>(static_cast<uint_t>(c1) | static_cast<uint_t>(c2));
    }

    inline auto getBookCategoryString(BookCategory c) -> std::string {
        switch (c) {
            case BookCategory::textbook:    return "教材"; 
            case BookCategory::fiction:     return "小说"; 
            case BookCategory::academic:    return "学术类"; 
            case BookCategory::exam:        return "考试类"; 
            case BookCategory::other:       return "其他"; 
            default:                        return "None";
        }
    }

    enum class BookStatus : uint_t {
        on_sale     = 0x1 << 0,                         // 在售 
        reserved    = 0x1 << 1,                         // 以预约
        sold        = 0x1 << 2,                         // 已售
        removed     = 0x1 << 3,                         // 已下架
        all         = on_sale | reserved | sold | removed
    };

    inline auto operator|(BookStatus s1, BookStatus s2) -> BookStatus {
        return static_cast<BookStatus>(static_cast<uint_t>(s1) | static_cast<uint_t>(s2));
    }

    inline auto getBookStatusString(BookStatus s) -> std::string {
        switch (s) {
            case BookStatus::on_sale:   return "在售";
            case BookStatus::reserved:  return "已预约";
            case BookStatus::sold:      return "已售";
            case BookStatus::removed:   return "已下架";
            default:                    return "None";
        }
    }
}

namespace BK {
    class Key {
        private:
            static constexpr uint_t len_ {16};  // salt和hashkey的最长长度
            std::string salt_;                  // Hash时使用的盐
            std::string hash_key_;              // Hash后的密钥

            auto hash(const std::string& str) const -> uint_t;
            auto generateSalt() -> void;

        public:
            Key(const std::string& password);
            Key(const std::string& salt, const std::string& hash_key);

            auto verify(const std::string& password) const -> bool;
            auto change(const std::string& new_password) -> void;

            auto salt() const -> const std::string&     {return salt_;}
            auto hashKey() const -> const std::string&  {return hash_key_;}
    };
}


namespace BK {
    /* 用于判断用户是否符合所选的比较条件 */
    struct UserCmpCondition {
        enum class Unlimit : uint_t {
            name = 0x1 << 0,
            id = 0x1 << 1
        };

        Unlimit flag {std::numeric_limits<uint_t>::max()};
        std::string name {};      
        int_t id {};      

        /* 设置无限制 */
        auto setUnlimit(Unlimit u) -> void {
            flag = static_cast<Unlimit>(static_cast<uint_t>(flag) | static_cast<uint_t>(u));
        }

        /* 取消无限制 */
        auto unsetUnlimit(Unlimit u) -> void {
            flag = static_cast<Unlimit>(static_cast<uint_t>(flag) & ~static_cast<uint_t>(u));
        }

        /* 是否为无限制 */
        auto isUmlimit(Unlimit u) const -> bool {
            return static_cast<uint_t>(flag) & static_cast<uint_t>(u);
        }
    };

    class Book;

    /* 用户 */
    struct User {
            /* 基础信息 */
            Key key;
            std::string name     {};        // 用户名 
            int_t id             {};        // 用户id
            int_t tel            {0};       // 电话号码
            int_t qq             {0};       // qq号
            std::string wechat   {};        // 微信号
            time_t register_time {0};       // 注册时间

            User(const std::string& password);
            User(const std::string salt, const std::string hash_key);

            auto operator==(const User& user) const -> bool = default;
            auto operator==(const UserCmpCondition& cmp_condition) const -> bool;

            auto books(std::list<std::shared_ptr<Book>>& books, BookStatus status = BookStatus::all, BookCategory category = BookCategory::all) const -> std::list<std::shared_ptr<Book>>;
    };
}

namespace BK {
    class User;

    /* 用于判断书籍是否符合所选的比较条件 */
    struct BookCmpCondition {
        enum class Unlimit : uint_t {
            id   = 0x1 << 0,
            title = 0x1 << 1,
            isbn  = 0x1 << 2,
            author = 0x1 << 3,
            press = 0x1 << 4,
            down_price = 0x1 << 5,
            up_price = 0x1 << 6,
            down_publish_time = 0x1 << 7,
            up_publish_time = 0x1 << 8,
            down_integrity = 0x1 << 9,
            up_integrity = 0x1 << 10,
            category = 0x1 << 11,
            status = 0x1 << 12
        };

        Unlimit flag {std::numeric_limits<uint_t>::max()}; 
        int_t id  {0};    
        std::string title {};                            
        std::string isbn  {};                                 
        std::string author {};                                
        std::string press {};                                 
        float_t down_price {};
        float_t up_price {};
        time_t down_publish_time {};
        time_t up_publish_time {};
        int_t down_integrity {};     
        int_t up_integrity  {};
        BookCategory category {};           
        BookStatus status {};          

        /* 设置无限制 */
        auto setUnlimit(Unlimit u) -> void {
            flag = static_cast<Unlimit>(static_cast<uint_t>(flag) | static_cast<uint_t>(u));
        }

        /* 取消无限制 */
        auto unsetUnlimit(Unlimit u) -> void {
            flag = static_cast<Unlimit>(static_cast<uint_t>(flag) & ~static_cast<uint_t>(u));
        }
        
        /* 是否为无限制 */
        auto isUmlimit(Unlimit u) const -> bool {
            return static_cast<uint_t>(flag) & static_cast<uint_t>(u);
        }
    };

    /* 书籍 */
    struct Book {
        static int_t book_num;                                      // 书籍总数目, 也是新增书籍id的标准
        int_t id {invalid::id};                                     // 书籍id
        int_t seller_id {invalid::id};                              // 售卖者id
        int_t buyer_id {invalid::id};                               // 购买者id
        int_t reserver_id {invalid::id};                            // 预定者Id

        std::string title {};                                       // 书名
        std::string isbn {};                                        // ISBN
        std::string author {};                                      // 作者
        std::string press {};                                       // 出版社
        std::string other {};                                       // 其他信息
        float_t price {5.20};                                       // 价格
        time_t publish_time {invalid::time};                        // 发布时间
        time_t buy_time {invalid::time};                            // 购买时间
        time_t reserve_time {invalid::time};                        // 预定时间
        BookStatus status {BookStatus::removed};                    // 书籍状态
        int_t integrity {max_integrity};                            // 书籍完整程度
        BookCategory category {BookCategory::other};                // 书籍类别

        auto seller(std::list<std::shared_ptr<User>>& users) const -> std::shared_ptr<User>;
        auto buyer(std::list<std::shared_ptr<User>>& users) const -> std::shared_ptr<User>;
        auto reserver(std::list<std::shared_ptr<User>>& users) const -> std::shared_ptr<User>;

        auto operator==(const Book& book) const -> bool = default;
        auto operator==(const BookCmpCondition& cmp_condition) const -> bool;
    };
}


#endif