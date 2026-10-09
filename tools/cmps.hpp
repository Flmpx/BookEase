#ifndef BK_CMPS_HPP_
#define BK_CMPS_HPP_

#include "../base/base.hpp"

namespace BK {
    namespace CmpBook {

        namespace PublishTime {
            inline auto up(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                time_t a {book_a->publish_time}, b {book_b->publish_time};
                return (a > b) - (b < a);
            }
            inline auto down(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                time_t a {book_a->publish_time}, b {book_b->publish_time};
                return (a < b) - (b > a);
            }
        }

        namespace ReservedTime {
            inline auto up(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                time_t a {book_a->reserve_time}, b {book_b->reserve_time};
                return (a > b) - (b < a);
            }
            inline auto down(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                time_t a {book_a->reserve_time}, b {book_b->reserve_time};
                return (a < b) - (b > a);
            }
            
        }

        namespace SoldTime {
            inline auto up(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                time_t a {book_a->buy_time}, b {book_b->buy_time};
                return (a > b) - (b < a);
            }
            inline auto down(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                time_t a {book_a->buy_time}, b {book_b->buy_time};
                return (a < b) - (b > a);
            }
            
        }
        
        namespace Price {
            inline auto up(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                float_t a {book_a->price}, b {book_b->price};
                if (a < b - EPS) {
                    return -1;
                } else if (a > b + EPS) {
                    return 1;
                } else {
                    return 0;
                }
            }
            inline auto down(const std::shared_ptr<Book>& book_a, const std::shared_ptr<Book>& book_b) {
                float_t a {book_a->price}, b {book_b->price};
                if (a > b + EPS) {
                    return -1;
                } else if (a < b - EPS) {
                    return 1;
                } else {
                    return 0;
                }
            }

        }
    }
}

#endif 