//
// Created by zincronit on 7/28/26.
//

#include "Library/Functions.hpp"

int main()
{
    char*** books;
    int** stock;
    read_books_file("Data/books.csv",
                    books,
                    stock);

    print_data_from_books_file("Reports/test-report-books.txt",
                               books,
                               stock);

    char*** books_by_order;
    int** orders_by_customer;
    bool** completed_orders;

    // bool hola{};
    // std::cout << hola << std::endl;



    return 0;
}
