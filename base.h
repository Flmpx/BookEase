#ifndef BASE_H
#define BASE_H
#include <stdbool.h>
#include <time.h>

const time_t releaseTime = 1778935434;

extern char BookStatusStr[4][101];
extern char BookConditionStr[4][101];
extern char BookCategoryStr[5][101];

#define EPS 1e-9							//浮点数比较所用误差

#define Invalid_Num 0LL						//无效数字, 可用于id, tel等

#define Invalid_Str "#"						//无效字段, 可用于name, title等

#define Invalid_FloatNum -1.0				//无效浮点数, 可用于书籍价格




#define PRESS_MAX_LEN 64					//出版社名字最长长度

#define WECHAR_MAX_LEN 48					//微信号最长长度

#define ISBN_MAX_LEN 48						//ISBN最长长度

#define TITLE_MAX_LEN 64					//书籍标题最长长度

#define AUTHOR_MAX_LEN 64					//书籍作者名字最长长度

#define NAME_MAX_LEN 32						//用户名最长长度

#define SALT_LEN 16							//盐最长长度

#define HASHKEY_LEN 24						//密码最长长度



typedef unsigned long long ull;
typedef long long ll;

extern ll MaxBookId;						//所有书籍的id的最大值, 主要是新发布书籍的时候会创建一个唯一的id


typedef enum {
	Min = -1,
	Same = 0,
	Max = 1,
} CmpResult;

/// @brief 操作状态返回值
typedef enum {
	Warning = -1,							//操作失败
	None = 0,								//操作无效
	Success = 1,							//操作成功
} InfoOfReturn;

typedef enum {
	Invalid_BookCategory = -1,				//无效书籍类别
	TEXTBOOK,								//教材
	FICTION,								//小说与文学
	ACADEMIC,								//学术类
	EXAM,									//考试类
	OTHER									//其他
} BookCategory;


typedef enum {
	Invalid_BookCondition = -1,				//无效的书籍新旧条件
	NEW = 0,								//几乎全新
	LIKE_NEW = 1,							//有点破损或书上笔记有点多
	GOOD = 2,								//还能用
	ACCEPTABLE = 3							//可接受
} BookCondition;

typedef enum {
	Invalid_BookStatus = -1,				//无效状态
	ON_SALE = 0,							//在售
	RESERVED = 1,							//已预约
	SOLD = 2,								//已售
	REMOVED = 3,							//已下架
} BookStatus;

typedef struct UserCmpCondition {
	char name[NAME_MAX_LEN];				//用户名的比较条件
	ll id;									//比较用户id
} UserCmpCondition;

typedef struct UserInfo {
	char name[NAME_MAX_LEN];				//用户名

	ll id;									//用户id, 用户学号为唯一身份认证

	ll tel;									//用户电话

	ll QQ;									//QQ号

	char WeChat[WECHAR_MAX_LEN];			//微信号

	time_t registerTime;					//用户注册时间
	
	char salt[SALT_LEN];					//验证密码使用的盐

	char hashKey[HASHKEY_LEN];				//hash后的密码
} UserInfo;

typedef struct BookCmpCondition {
	UserCmpCondition seller;				//售卖者的比较条件
	
	UserCmpCondition reserver;				//预定者的比较条件
	
	UserCmpCondition buyer;					//购买者的比较条件
	
	ll id;									//比较书籍id
	
	char title[TITLE_MAX_LEN];				//比较书名
	
	char isbn[ISBN_MAX_LEN];				//比较isbn
	
	char author[AUTHOR_MAX_LEN];			//比较书籍作者
	
	double downPrice;						//比较最低价
	
	double upPrice;							//比较最高价
	
	time_t downTime;						//比较发布时间下限
	
	time_t upTime;							//比较发布时间上限
	
	BookCondition condition;				//比较书籍新旧程度
	
	BookStatus status;						//比较书籍状态

	BookCategory category;					//比较书籍类别

} BookCmpCondition;

typedef struct Book {
	UserInfo* seller;						//售卖者信息
	ll sellerId;							//售卖者id, 主要用于程序开始加载时


	UserInfo* buyer;						//购买者信息
	ll buyerId;								//购买者id, 主要用于程序开始加载时

	UserInfo* reserver;						//预定者信息
	ll reserverId;							//预定在Id

	ll id;									//书籍唯一id(会自增)

	char title[TITLE_MAX_LEN];				//书籍标题

	char ISBN[ISBN_MAX_LEN];				//书籍ISBN

	char author[AUTHOR_MAX_LEN];			//书籍作者

	char press[PRESS_MAX_LEN];				//出版社

	double price;							//书籍价格

	time_t publishTime;						//发布时间
	time_t buyTime;							//交易时间
	time_t reserveTime;						//预定时间


	BookStatus status;						//书籍状态

	BookCondition condition;				//书籍新旧程度

	BookCategory category;					//书籍类别
} Book;







/**
 * 定义书籍比较函数类型指针.
 */
typedef int (*cmpBook)(Book* book_a, Book* book_b);		























/// @brief 得到空用户信息, 内部什么都没有
/// @return 空用户信息
extern UserInfo getEmptyUserInfo();

/// @brief 得到空书籍信息, 内部什么都没有
/// @return 空书籍信息
extern Book getEmptyBook();


/// @brief 这个用户是否符合要求
/// @param user 用户
/// @param userCondition 用户要求 
/// @return 比较结果
extern bool isSimilarUserInfo(UserInfo* user, UserCmpCondition* userCondition);

/// @brief 这本书是否符合要求
/// @param book 书籍 
/// @param bookCondition 书籍要求 
/// @return 比较结果
extern bool isSimilarBook(Book* book, BookCmpCondition* bookCondition);

/// @brief 得到无要求的用户要求条件, 可以更更改部分条件后进行比较
/// @return 用户要求条件
extern UserCmpCondition getEmptyUserInfoCmpCondition();

/// @brief 得到无要求的书籍要求条件, 可以更更改部分条件后进行比较
/// @return 书籍要求条件
extern BookCmpCondition getEmptyBookCmpCondition();



#endif
