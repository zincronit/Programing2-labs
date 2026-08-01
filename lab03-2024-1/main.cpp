//
// Created by zincronit on 7/31/26.
//

#include "Library/Functions.hpp"

int main()
{
    char*** books;
    int** stocks;
    read_books_file("Data/books.csv",  books,  stocks);
    print_books_details("Reports/initial-report-books.txt",  books, stocks);

    char*** orders;
    int** customers;
    bool** completed_orders;
    // is book delivered
    return 0;
}