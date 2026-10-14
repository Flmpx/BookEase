/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/

#ifndef BK_CMPS_HPP_
#define BK_CMPS_HPP_

#include "../base/base.hpp"

namespace BK {
    namespace CmpBook {

        /* 发布时间 */
        namespace PublishTime {
            inline auto up(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                Time a {book_a->publish_time}, b {book_b->publish_time};
                if (a < b) return true;
                else return false;
            }
            inline auto down(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                Time a {book_a->publish_time}, b {book_b->publish_time};
                if (a > b) return true;
                else return false;
            }
        }

        /* 下架时间 */
        namespace RemovedTime {
            inline auto up(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                Time a {book_a->removed_time}, b {book_b->removed_time};
                if (a < b) return true;
                else return false;
            }
            inline auto down(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                Time a {book_a->removed_time}, b {book_b->removed_time};
                if (a > b) return true;
                else return false;
            }
        }

        /* 预定时间 */
        namespace ReservedTime {
            inline auto up(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                Time a {book_a->reserve_time}, b {book_b->reserve_time};
                if (a > b) return true;
                else return false;
            }
            inline auto down(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                Time a {book_a->reserve_time}, b {book_b->reserve_time};
                if (a > b) return true;
                else return false;
            }
            
        }

        /* 购买时间 */
        namespace SoldTime {
            inline auto up(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                Time a {book_a->buy_time}, b {book_b->buy_time};
                if (a > b) return true;
                else return false;
            }
            inline auto down(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                Time a {book_a->buy_time}, b {book_b->buy_time};
                if (a > b) return true;
                else return false;
            }
            
        }
        
        /* 价格 */
        namespace Price {
            inline auto up(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                float_t a {book_a->price}, b {book_b->price};
                if (a < b - EPS) return true;
                else return false;
            }

            inline auto down(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                float_t a {book_a->price}, b {book_b->price};
                if (a > b + EPS) return true;
                else return false;
            }

        }
    }
}

#endif 