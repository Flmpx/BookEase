/*
* Copyright (c) 2026 Flmpx
* Licensed under MIT (see LICENSE).
*/
#ifndef SORT_H
#define SORT_H
#include "../base.h"


extern int sort_publish_date_up(Book* book_a, Book* book_b);
extern int sort_publish_date_down(Book* book_a, Book* book_b);

extern int sort_reserved_date_up(Book* book_a, Book* book_b);
extern int sort_reserved_date_down(Book* book_a, Book* book_b);


extern int sort_sold_date_up(Book* book_a, Book* book_b);
extern int sort_sold_date_down(Book* book_a, Book* book_b);

extern int sort_price_up(Book* book_a, Book* book_b);
extern int sort_price_down(Book* book_a, Book* book_b);



#endif
