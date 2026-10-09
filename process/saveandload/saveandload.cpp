#include "saveandload.hpp"
#include <easyx.h>

extern "C" {
    #include <flJson.h>
}

namespace BK {

    namespace {
        /* 将整数添加到对象中 */
        auto objAdd(flJson& obj, const char* key, int_t i) {    // 由于int_t和time_t都是long long类型, 为了避免重复定义, 故只保留int_t
            flJson* ele = flJsonLL_New(i);
            flJsonObject_Add(&obj, key, ele);
            flJson_UnRef(ele);
        }
        /* 将书籍类别添加到对象中 */
        auto objAdd(flJson& obj, const char* key, BookCategory c) {
            flJson* ele = flJsonLL_New(static_cast<long long>(c));
            flJsonObject_Add(&obj, key, ele);
            flJson_UnRef(ele);
        }
        /* 将书籍状态添加到对象中 */
        auto objAdd(flJson& obj, const char* key, BookStatus s) {
            flJson* ele = flJsonLL_New(static_cast<long long>(s));
            flJsonObject_Add(&obj, key, ele);
            flJson_UnRef(ele);
        }
        /* 将浮点数添加到对象中 */
        auto objAdd(flJson& obj, const char* key, float_t f) {
            flJson* ele = flJsonDouble_New(f);
            flJsonObject_Add(&obj, key, ele);
            flJson_UnRef(ele);
        }
        /* 将字符串添加到对象中 */
        auto objAdd(flJson& obj, const char* key, const std::string& str) {
            flJson* ele = flJsonString_New(str.c_str());
            flJsonObject_Add(&obj, key, ele);
            flJson_UnRef(ele);
        }

        /* 通过对象中对应键的值来修改整数 */
        auto objGet(int_t& i, flJson& obj, const char* key) {
            flJson* ele = flJsonObject_Get(&obj, key);
            if (ele) {
                i = *flJsonLL_Get(ele);
            }
        } 
        /* 通过对象中对应键的值来修改书籍类别 */
        auto objGet(BookCategory& c, flJson& obj, const char* key) {
            flJson* ele = flJsonObject_Get(&obj, key);
            if (ele) {
                c = static_cast<BookCategory>(*flJsonLL_Get(ele));
            }
        }
        /* 通过对象中对应键的值来修改书籍状态 */
        auto objGet(BookStatus& s, flJson& obj, const char* key) {
            flJson* ele = flJsonObject_Get(&obj, key);
            if (ele) {
                s = static_cast<BookStatus>(*flJsonLL_Get(ele));
            }
        }
        /* 通过对象中对应键的值来修改浮点数 */
        auto objGet(float_t& f, flJson& obj, const char* key) {
            flJson* ele = flJsonObject_Get(&obj, key);
            if (ele) {
                f = *flJsonDouble_Get(ele);
            }
        } 
        /* 通过对象中对应键的值来修改字符串 */
        auto objGet(std::string& str, flJson& obj, const char* key) {
            flJson* ele = flJsonObject_Get(&obj, key);
            if (ele) {
                str = std::string(flJsonString_Get(ele));
            }
        } 

        /* 将对象中的内容输入到用户中 */
        auto in(std::shared_ptr<User>& user, flJson& obj) {
            objGet(user->id, obj, "id");
            objGet(user->name, obj, "name");
            objGet(user->tel, obj, "tel");
            objGet(user->qq, obj, "qq");
            objGet(user->wechat, obj, "wechat");
            objGet(user->register_time, obj, "registertime");
            std::string salt {}, hash_key {};
            objGet(salt, obj, "salt");
            objGet(hash_key, obj, "hashkey");
            user->key = Key(salt, hash_key);
        }
        
        /* 将对象中的内容输入到书籍中 */
        auto in(std::shared_ptr<Book>& book, flJson& obj) {
            objGet(book->id, obj, "id");
            objGet(book->seller_id, obj, "sellerid");
            objGet(book->buyer_id, obj, "buyerid");
            objGet(book->reserver_id, obj, "reserverid");
            objGet(book->publish_time, obj, "publishtime");
            objGet(book->buy_time, obj, "buytime");
            objGet(book->reserve_time, obj, "reservetime");
            objGet(book->status, obj, "status");
            objGet(book->integrity, obj, "integrity");
            objGet(book->category, obj, "category");
            objGet(book->price, obj, "price");
            objGet(book->title, obj, "title");
            objGet(book->isbn, obj, "isbn");
            objGet(book->author, obj, "author");
            objGet(book->press, obj, "press");
            objGet(book->other, obj, "other");
        }

        /* 将用户中的内容输出到对象中 */
        auto out(flJson& obj, const std::shared_ptr<User>& user) {
            objAdd(obj, "id", user->id);
            objAdd(obj, "name", user->name);
            objAdd(obj, "tel", user->tel);
            objAdd(obj, "qq", user->qq);
            objAdd(obj, "wechat", user->wechat);
            objAdd(obj, "registertime", user->register_time);
            objAdd(obj, "salt", user->key.salt());
            objAdd(obj, "hashkey", user->key.hashKey());
        }
        
        /* 将书籍中的内容输出到对象中 */
        auto out(flJson& obj, const std::shared_ptr<Book>& book) {
            objAdd(obj, "id", book->id);
            objAdd(obj, "sellerid", book->seller_id);
            objAdd(obj, "buyerid", book->buyer_id);
            objAdd(obj, "reserverid", book->reserver_id);
            objAdd(obj, "publishtime", book->publish_time);
            objAdd(obj, "buytime", book->buy_time);
            objAdd(obj, "reservetime", book->reserve_time);
            objAdd(obj, "status", book->status);
            objAdd(obj, "integrity", book->integrity);
            objAdd(obj, "category", book->category);

            objAdd(obj, "price", book->price);

            objAdd(obj, "title", book->title);
            objAdd(obj, "isbn", book->isbn);
            objAdd(obj, "author", book->author);
            objAdd(obj, "press", book->press);
            objAdd(obj, "other", book->other);
        }
        
    }

    namespace File {

        /**
         * @brief 通过输入文件指针将文件中的用户内容加载到用户链表中
         * 
         * @param fin 输入文件指针
         * @return 用户链表
         */
        auto loadUsersFromFile(std::ifstream& fin) -> std::list<std::shared_ptr<User>> {
            std::list<std::shared_ptr<User>> users {};

            fin.seekg(0, std::ios::end);
            auto size {fin.tellg()};
            fin.seekg(0, std::ios::beg);
            
            std::string str(size, '\0');
            fin.read(&str[0], size);

            flJson* arr = flJson_Parse(str.c_str());

            if (arr) {
                flJsonArrayIter iter;
                flJsonArrayIter_Init(&iter, arr);
                while (flJsonArrayIter_HasCur(&iter)) {
                    flJson* ele = flJsonArrayIter_Cur(&iter);
                    std::shared_ptr<User> user {new User("", "")};
                    in(user, *ele);
                    users.push_back(user);
                    flJsonArrayIter_MoveNext(&iter);
                }
                flJson_UnRef(arr);
            }

            return users;

        }

        /**
         * @brief 通过文件名打开文件, 并将文件中的用户内容加载到用户链表中
         * 
         * @param dir 文件名
         * @return 用户链表
         */
        auto loadUsersFromFile(const char* dir) -> std::list<std::shared_ptr<User>> {
            std::ifstream fin(dir, std::ios::in);
            if (!fin.is_open()) {
                MessageBox(GetHWnd(), "重要文件bkdata/users.json丢失", "异常", MB_OK | MB_ICONSTOP);
                throw std::system_error(errno, std::system_category(), "文件异常" + std::string(dir));
            }
            std::list<std::shared_ptr<User>> ret(loadUsersFromFile(fin));
            fin.close();

            return ret;
        }

        /**
         * @brief 将用户链表的内容保存到文件指针指定的文件中
         * 
         * @param fout 输出文件指针
         * @param users 用户链表
         */
        auto saveUserToFile(std::ofstream& fout, const std::list<std::shared_ptr<User>>& users) -> void {
            flJson* arr = flJsonArray_New();
            for (auto& it : users) {
                flJson* ele = flJsonObject_New();
                out(*ele, it);
                flJsonArray_Add(arr, ele, flJsonArray_Size(arr));
                flJson_UnRef(ele);
            }
            char* arr_str = flJson_Dump(arr);
            fout << arr_str;

            free(arr_str);
            flJson_UnRef(arr);
        }

        /**
         * @brief 将用户链表的内容保存到文件名所指定的文件中
         * 
         * @param dir 文件名
         * @param users 用户链表
         */
        auto saveUserToFile(const char* dir, const std::list<std::shared_ptr<User>>& users) -> void {
            std::ofstream fout(dir, std::ios::out);
            if (!fout.is_open()) {
                MessageBox(GetHWnd(), "重要文件bkdata/users.json丢失", "异常", MB_OK | MB_ICONSTOP);
                throw std::system_error(errno, std::system_category(), "文件异常" + std::string(dir));
            }

            saveUserToFile(fout, users);
            fout.close();
        }

        /**
         * @brief 通过输入文件指针将文件中的书籍内容加载到书籍链表中
         * 
         * @param fin 输入文件指针
         * @return 书籍链表
         */
        auto loadBooksFromFile(std::ifstream& fin) -> std::list<std::shared_ptr<Book>> {
            std::list<std::shared_ptr<Book>> books {};
            
            fin.seekg(0, std::ios::end);
            auto size {fin.tellg()};
            fin.seekg(0, std::ios::beg);

            std::string str(size, '\0');
            fin.read(&str[0], size);

            flJson* arr = flJson_Parse(str.c_str());

            if (arr) {
                flJsonArrayIter iter;
                flJsonArrayIter_Init(&iter, arr);
                while (flJsonArrayIter_HasCur(&iter)) {
                    flJson* ele = flJsonArrayIter_Cur(&iter);
                    std::shared_ptr<Book> book {new Book};
                    in(book, *ele);
                    books.push_back(book);
                    Book::book_num++;
                    flJsonArrayIter_MoveNext(&iter);
                }
                flJson_UnRef(arr);
            }

            return books;
        }

        /**
         * @brief 通过文件名打开文件, 并将文件中的书籍内容加载到书籍链表中
         * 
         * @param dir 文件名
         * @return 书籍链表
         */
        auto loadBooksFromFile(const char* dir) -> std::list<std::shared_ptr<Book>> {
            std::ifstream fin(dir, std::ios::in);
            if (!fin.is_open()) {
                MessageBox(GetHWnd(), "重要文件bkdata/books.json丢失", "异常", MB_OK | MB_ICONSTOP);
                throw std::system_error(errno, std::system_category(), "文件异常" + std::string(dir));
            }
            std::list<std::shared_ptr<Book>> ret(loadBooksFromFile(fin));
            fin.close();

            return ret;
        }

        /**
         * @brief 将书籍链表的内容保存到文件指针指定的文件中
         * 
         * @param fout 输出文件指针
         * @param books 书籍链表
         */
        auto saveBooksToFile(std::ofstream& fout, const std::list<std::shared_ptr<Book>>& books) -> void {
            flJson* arr = flJsonArray_New();
            for (auto& it : books) {
                flJson* ele = flJsonObject_New();
                out(*ele, it);
                flJsonArray_Add(arr, ele, flJsonArray_Size(arr));
                flJson_UnRef(ele);
            }
            char* arr_str = flJson_Dump(arr);
            fout << arr_str;

            free(arr_str);
            flJson_UnRef(arr);
        }

        /**
         * @brief 将书籍链表的内容保存到文件名所指定的文件中
         * 
         * @param dir 文件名
         * @param books 用户链表
         */
        auto saveBooksToFile(const char* dir, const std::list<std::shared_ptr<Book>>& books) -> void {
            std::ofstream fout(dir, std::ios::out);
            if (!fout.is_open()) {
                MessageBox(GetHWnd(), "重要文件bkdata/books.json丢失", "异常", MB_OK | MB_ICONSTOP);
                throw std::system_error(errno, std::system_category(), "文件异常" + std::string(dir));
            }
            
            saveBooksToFile(fout, books);
            fout.close();
        }
    }
}