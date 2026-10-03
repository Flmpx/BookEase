#ifndef BK_BASE_HPP_
#define BK_BASE_HPP_

#include <string>
#include <cstdint>
#include <list>
#include <memory>

namespace BK {
    using int_t = int64_t;                                      // 有符号整数
    using uint_t = uint64_t;                                    // 无符号整数
    using float_t = double;                                     // 浮点数

    constexpr float_t EPS                   {1e-9};             // 浮点数比较所用误差

    constexpr int_t min_integrity           {0};                // 最小书籍完整度
    constexpr int_t max_integrity           {100};              // 最小书籍完整度

    /* 无效值(全部为负数)在窗口中一律不显示, 和空字符串一样 */
    namespace invalid {
        constexpr int_t integrity       {-1};               // 无效完整度
        constexpr int_t id              {-1};               // 无效Id
        constexpr int_t tel             {-1};               // 无效电话
        constexpr int_t qq              {-1};               // 无效qq
        constexpr float_t price         {-1.0};             // 无效价格(本质上是负数为无效)
        constexpr time_t time           {-1};               // 无效时间
        constexpr int_t category        {-1};               // 无效类别
        constexpr int_t status          {-1};               // 无效状态
    }
}


namespace BK {
    
    /* 书籍类别 */
    enum class BookCategory {
        textbook    = 0x1 << 0,                         // 教材
        fiction     = 0x1 << 1,                         // 小说
        academic    = 0x1 << 2,                         // 学术类
        exam        = 0x1 << 3,                         // 考试类
        other       = 0x1 << 4,                         // 其他
        all         = textbook | fiction | academic | exam | other
    };

    inline auto operator|(BookCategory c1, BookCategory c2) -> BookCategory {
        return static_cast<BookCategory>(static_cast<int_t>(c1) | static_cast<int_t>(c2));
    }

    enum class BookStatus {
        on_sale     = 0x1 << 0,                         // 在售 
        reserved    = 0x1 << 1,                         // 以预约
        sold        = 0x1 << 2,                         // 已售
        removed     = 0x1 << 3,                         // 已下架
        all         = on_sale | reserved | sold | removed
    };

    inline auto operator|(BookStatus s1, BookStatus s2) -> BookStatus {
        return static_cast<BookStatus>(static_cast<int_t>(s1) | static_cast<int_t>(s2));
    }
}


namespace BK {
    template <typename T>
    class range {
        private:
            T min_;
            T max_;
        public:
            /* 负数代表无限制 */
            range(T t1, T t2) : min_(t1), max_(t2) {}

            /* 是否在当前范围内 */
            auto include(T t) const -> bool {
                return (max_ < 0 || t <= max_) && ( min_ < 0 || t >= min_);
            }

            /* 强制改成范围内 */
            auto forceInclude(T& t) const -> void {
                if (min_ >= 0 && t < min_) t = min_;
                if (max_ >= 0 && t > max_) t = max_;
            }
    };

    template <>
    inline auto range<double>::include(double t) const -> bool {
        return (t < -EPS || t <= max_ + EPS) && (t < -EPS || t >= min_ - EPS);
    }
    
    template <>
    inline auto range<double>::forceInclude(double& t) const -> void {
        if (min_ >= EPS && t < min_ - EPS) t = min_;
        if (min_ >= EPS && t > max_ + EPS) t = max_;
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
        std::string name    {};                 // 用户名的比较条件
        int_t id            {invalid::id};      // 用户id的比较条件
    };

    class Book;

    /* 用户 */
    struct User {
            /* 基础信息 */
            Key key;
            std::string name        {};                     // 用户名 
            int_t id                {invalid::id};          // 用户id
            int_t tel               {invalid::tel};         // 电话号码
            int_t qq                {invalid::qq};          // qq号
            std::string wechat      {};                     // 微信号
            time_t register_time    {invalid::time};        // 注册时间

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
        int_t id                                {invalid::id};                      // 书籍id比较条件
        std::string title                       {};                                 // 书籍标题比较条件
        std::string isbn                        {};                                 // ISBN比较条件
        std::string author                      {};                                 // 作者名称
        std::string press                       {};                                 // 出版社
        range<double> price_range               {invalid::price, invalid::price};   // 价格区间
        range<time_t> publish_time_range        {invalid::time, invalid::time};     // 发布时间区间
        range<time_t> buy_time_range            {invalid::time, invalid::time};     // 购买时间区间
        range<time_t> reserve_time_range        {invalid::time, invalid::time};     // 预定时间区间
        range<int_t> integrity_range            {min_integrity, max_integrity};     // 书籍完整程度
        int_t category                          {invalid::category};                // 书籍种类
        int_t status                            {invalid::status};                  // 书籍状态
    };

    /* 书籍 */
    struct Book {
        static int_t book_num;                          // 书籍总数目, 也是新增书籍id的标准
        int_t id                {invalid::id};          // 书籍id
        int_t seller_id         {invalid::id};          // 售卖者id
        int_t buyer_id          {invalid::id};          // 购买者id
        int_t reserver_id       {invalid::id};          // 预定者Id

        std::string title       {};                     // 书名
        std::string isbn        {};                     // ISBN
        std::string author      {};                     // 作者
        std::string press       {};                     // 出版社
        std::string other       {};                     // 其他信息
        float_t price           {invalid::price};       // 价格
        time_t publish_time     {invalid::time};        // 发布时间
        time_t buy_time         {invalid::time};        // 购买时间
        time_t reserve_time     {invalid::time};        // 预定时间
        int_t status            {invalid::status};      // 书籍状态
        int_t integrity         {invalid::integrity};   // 书籍完整程度
        int_t category          {invalid::category};    // 书籍类别

        auto seller(std::list<std::shared_ptr<User>>& users) const -> std::shared_ptr<User>;
        auto buyer(std::list<std::shared_ptr<User>>& users) const -> std::shared_ptr<User>;
        auto reserver(std::list<std::shared_ptr<User>>& users) const -> std::shared_ptr<User>;

        auto operator==(const Book& book) const -> bool = default;
        auto operator==(const BookCmpCondition& cmp_condition) const -> bool;
    };
}


#endif