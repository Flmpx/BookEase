/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#ifndef BK_BASE_HPP_
#define BK_BASE_HPP_

#include <string>
#include <cstdint>
#include <list>
#include <memory>
#include <limits>
#include <ctime>
#include <array>
#include <iomanip>

namespace BK {
    inline constexpr const char* BOOKS_FILE_DIR {"./bkdata/books.json"};        // 书籍数据文件地址
    inline constexpr const char* USERS_FILE_DIR {"./bkdata/users.json"};        // 用户数据文件地址

    using int_t = int64_t;                                      // 有符号整数
    using uint_t = uint64_t;                                    // 无符号整数
    using float_t = double;                                     // 浮点数

    constexpr float_t EPS                   {1e-9};             // 浮点数比较所用误差
    constexpr uint_t BUF_SIZE               {256};              // 输入时缓冲区的大小

    constexpr int_t min_integrity           {0};                // 最小书籍完整度
    constexpr int_t max_integrity           {100};              // 最小书籍完整度

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

    template <typename T>
    class Range {
        private:
            T min_;
            T max_;
        public:     

            Range(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max())
            : min_(min), max_(max)
            {}


            /* 是否包括 */
            auto contain(T ele) const -> bool {
                return (ele <= max_ && ele >= min_);
            }

            /* 强制包括 */
            auto forceContain(T& ele) const -> void {
                if (ele > max_) ele = max_;
                if (ele < min_) ele = min_;
            }

            auto min() -> T {
                return min_;
            }
            auto max() -> T {
                return max_;
            }
    };

    template <>
    class Range<float_t> {
        private:
            float_t min_;
            float_t max_;
        public:     

            Range(float_t min = std::numeric_limits<float_t>::lowest(), float_t max = std::numeric_limits<float_t>::max())
            : min_(min), max_(max)
            {}


            /* 是否包括 */
            auto contain(float_t ele) const -> bool {
                return (ele <= max_ + EPS && ele >= min_ - EPS);
            }

            /* 强制包括 */
            auto forceContain(float_t& ele) const -> void {
                if (ele > max_ + EPS) ele = max_;
                if (ele < min_ + EPS) ele = min_;
            }

            auto min() -> float_t {
                return min_;
            }
            auto max() -> float_t {
                return max_;
            }
    };


    class Time {
        private:
            static constexpr int_t max_time_sec_ {32503679999};
            static constexpr int_t min_time_sec_ {0};
            static constexpr std::array<int_t, 12> days_every_mouth_ {
                31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
            };
            time_t time_sec_;
            struct tm time_struct_;

            auto is_leap_year(int_t year) const -> bool {
                return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            }
        public:
        
            Time() {
                time_sec_ = 0;
                localtime_s(&time_struct_, &time_sec_);
            };

            /* 通过年月日设置时间 */
            auto set(int_t year, int_t month, int_t day) {
                Range<int_t>(1970, 2999).forceContain(year);
                Range<int_t>(1, 12).forceContain(month);

                if (month == 2) {
                    if (is_leap_year(year)) {
                        Range<int_t>(1, 29).forceContain(day);
                    } else {
                        Range<int_t>(1, 28).forceContain(day);
                    }
                } else {
                    Range<int_t>(1, days_every_mouth_[month - 1]).forceContain(day);
                }

                time_struct_.tm_year = year - 1900;
                time_struct_.tm_mon = month - 1;
                time_struct_.tm_mday = day;

                time_sec_ = std::mktime(&time_struct_);

            }

            /* 通过结构体设置时间 */
            auto set(struct tm* time) {
                time_struct_ = *time;
                time_sec_ = std::mktime(&time_struct_);
            }

            /* 通过 */
            auto set(time_t t) {
                Range<int_t>(min_time_sec_, max_time_sec_).forceContain(t);
                time_sec_ = t;
                localtime_s(&time_struct_, &time_sec_);
            }

            auto year() const -> int_t {return time_struct_.tm_year + 1900;}
            auto month() const -> int_t {return time_struct_.tm_mon + 1;}
            auto day() const -> int_t {return time_struct_.tm_mday;}
            auto time() const -> time_t {return time_sec_;}
            
            auto operator<=>(const Time& t) const -> std::strong_ordering {
                return time_sec_ <=> t.time_sec_;
            }

            friend auto operator<<(std::ostream& os, const Time& t) -> std::ostream& {
                os << t.year()  << "年" 
                   << t.month() << "月" 
                   << t.day()   << "日";

                return os;
            }

    };
}

namespace std {
    template <>
    class numeric_limits<BK::Time> {
        public:
            static auto min() -> BK::Time {
                BK::Time t {};
                t.set(time_t(0));
                return t;
            }

            static auto max() -> BK::Time {
                BK::Time t {};
                t.set(2999, 12, 31);
                return t;
            }
            
            static auto lowest() -> BK::Time {
                return min();
            }
    };

    inline auto to_string(const BK::Time& t) -> string {
        stringstream ret {};
        ret << t.year()  << "年" 
            << t.month() << "月" 
            << t.day()   << "日";

        return ret.str();
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
            Key(const std::string& password = "");
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
            Key key;                        // 密钥
            std::string name     {};        // 用户名 
            int_t id             {};        // 用户id
            int_t tel            {0};       // 电话号码
            int_t qq             {0};       // qq号
            std::string wechat   {};        // 微信号
            Time register_time   {};        // 注册时间
            User(const std::string& password = "");
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
        Time down_publish_time {};
        Time up_publish_time {};
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
        int_t id {};                                                // 书籍id
        int_t seller_id {};                                         // 售卖者id
        int_t buyer_id {};                                          // 购买者id
        int_t reserver_id {};                                       // 预定者Id

        std::string title {};                                       // 书名
        std::string isbn {};                                        // ISBN
        std::string author {};                                      // 作者
        std::string press {};                                       // 出版社
        std::string other {};                                       // 其他信息
        float_t price {5.20};                                       // 价格
        Time publish_time {};                                       // 发布时间
        Time buy_time {};                                           // 购买时间
        Time reserve_time {};                                       // 预定时间
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