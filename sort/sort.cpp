#include "sort.h"
#include <time.h>

int sort_publish_date_up(Book* book_a, Book* book_b) {
	time_t a = book_a->publishTime, b = book_b->publishTime;
	if (a < b) {
		return -1;
	} else if (a > b) {
		return 1;
	} else {
		return 0;
	}
}

int sort_publish_date_down(Book* book_a, Book* book_b) {
	time_t a = book_a->publishTime, b = book_b->publishTime;
	if (a > b) {
		return -1;
	} else if (a < b) {
		return 1;
	} else {
		return 0;
	}
}
int sort_reserved_date_up(Book* book_a, Book* book_b) {
	time_t a = book_a->publishTime, b = book_b->publishTime;
	if (a < b) {
		return -1;
	} else if (a > b) {
		return 1;
	} else {
		return 0;
	}
}

int sort_reserved_date_down(Book* book_a, Book* book_b) {
	time_t a = book_a->publishTime, b = book_b->publishTime;
	if (a > b) {
		return -1;
	} else if (a < b) {
		return 1;
	} else {
		return 0;
	}
}
int sort_sold_date_up(Book* book_a, Book* book_b) {
	time_t a = book_a->publishTime, b = book_b->publishTime;
	if (a < b) {
		return -1;
	} else if (a > b) {
		return 1;
	} else {
		return 0;
	}
}

int sort_sold_date_down(Book* book_a, Book* book_b) {
	time_t a = book_a->publishTime, b = book_b->publishTime;
	if (a > b) {
		return -1;
	} else if (a < b) {
		return 1;
	} else {
		return 0;
	}
}


int sort_price_up(Book* book_a, Book* book_b) {
	double a = book_a->price, b = book_b->price;
	if (a < b - EPS) {
		return -1;
	} else if (b < a - EPS) {
		return 1;
	} else {
		return 0;
	}
}


int sort_price_down(Book* book_a, Book* book_b) {
	double a = book_a->price, b = book_b->price;
	if (a > b + EPS) {
		return -1;
	} else if (b > a + EPS) {
		return 1;
	} else {
		return 0;
	}
}

