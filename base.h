#ifndef BASE_H
#define BASE_H
#include <stdbool.h>
#include <time.h>
#define EPS 1e-9
extern char BookStatusStr[4][101];
extern char BookConditionStr[4][101];

//无效数字, 可用于id, tel等
#define Invalid_Num 0LL


//无效字段, 可用于name, title等
#define Invalid_Str "#"



//无效浮点数, 可用于书籍价格
#define Invalid_FloatNum -1.0






//微信号最长长度
#define WECHAR_MAX_LEN 24


//ISBN最长长度
#define ISBN_MAX_LEN 24

//书籍标题最长长度
#define BOOK_TITLE_MAX_LEN 64

//书籍作者名字最长长度
#define BOOK_AUTHOR_MAX_LEN 16

//用户名最长长度
#define USERNAME_MAX_LEN 16

//其他信息最长长度
#define OTHERS_MAX_LEN 128

//盐最长长度
#define SALT_LEN 16

//密码最长长度
#define HASHKEY_LEN 24



typedef unsigned long long ull;
typedef long long ll;



typedef enum {
	Min = -1,
	Same = 0,
	Max = 1,
} CmpResult;

//typedef CmpResult (*_cmp) (const void* a, const void* b);

/// @brief 操作状态返回值
typedef enum {
	Warning = -1,							//操作失败
	None = 0,								//操作无效
	Success = 1,							//操作成功
} InfoOfReturn;

typedef enum {
	Invalid_BookCondition = -1,				//无效的书籍新旧条件
	NEW = 0,								//几乎全新
	LIKE_NEW = 1,							//有点破损或书上笔记有点多
	GOOD = 2,								//还能用
	ACCEPTABLE = 4							//可接受
} BookCondition;

typedef enum {
	Invalid_BookStatus = -1,
	ON_SALE = 0,							//在售
	RESERVED = 1,							//已预约
	SOLD = 2,								//已售
	REMOVED = 3,							//已下架
} BookStatus;

typedef struct UserInfoCmpCondition {
	char name[USERNAME_MAX_LEN];
	ll id;
} UserInfoCmpCondition;

typedef struct UserInfo {
	char name[USERNAME_MAX_LEN];			//用户名

	//用户学号为唯一身份认证
	ll id;									//用户id
	ll tel;									//用户电话
	ll QQ;									//QQ号
	char WeChat[WECHAR_MAX_LEN];			//微信号
	//char others[OTHERS_MAX_LEN];			//其他联系信息
	time_t registerTime;					//用户注册时间
	
	char salt[SALT_LEN];					//验证密码使用的盐
	char hashKey[HASHKEY_LEN];				//密码
} UserInfo;

typedef struct BookCmpCondition {
	UserInfoCmpCondition seller;
	ll id;
	char title[BOOK_TITLE_MAX_LEN];
	char isbn[ISBN_MAX_LEN];
	char author[BOOK_AUTHOR_MAX_LEN];
	double downPrice;
	double upPrice;
	time_t downTime;
	time_t upTime;
	BookCondition condition;
} BookCmpCondition;

typedef struct Book {
	UserInfo* seller;						//售卖者信息
	ll sellerId;							//售卖者id, 主要用于程序开始加载时


	UserInfo* buyer;						//购买者信息
	ll buyerId;								//购买者id, 主要用于程序开始加载时

	UserInfo* reserver;						//预定者信息
	ll reserverId;							//预定在Id

	ll id;									//书籍唯一id(会自增)

	char title[BOOK_TITLE_MAX_LEN];			//书籍标题

	char ISBN[ISBN_MAX_LEN];				//书籍ISBN

	char author[BOOK_AUTHOR_MAX_LEN];		//书籍作者

	double price;							//书籍价格

	time_t publishTime;						//发布时间
	time_t buyTime;							//交易时间
	time_t reserveTime;						//预定时间


	BookStatus status;						//书籍状态

	BookCondition condition;				//书籍新旧程度
	//char others[OTHERS_MAX_LEN];			//书籍其他介绍

} Book;




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
extern bool isSimilarUserInfo(UserInfo* user, UserInfoCmpCondition* userCondition);

/// @brief 这本书是否符合要求
/// @param book 书籍 
/// @param bookCondition 书籍要求 
/// @return 比较结果
extern bool isSimilarBook(Book* book, BookCmpCondition* bookCondition);

/// @brief 得到无要求的用户要求条件, 可以更更改部分条件后进行比较
/// @return 用户要求条件
extern UserInfoCmpCondition getEmptyUserInfoCmpCondition();

/// @brief 得到无要求的书籍要求条件, 可以更更改部分条件后进行比较
/// @return 书籍要求条件
extern BookCmpCondition getEmptyBookCmpCondition();

#endif
