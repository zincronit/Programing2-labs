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

    read_orders_file("Data/orders.txt",
                     books_by_order,
                     orders_by_customer,
                     completed_orders,
                     books,
                     stock);

    order_delivery_report("Reports/order-delivery-report.txt",
                             books_by_order,
                             orders_by_customer,
                             completed_orders);

    print_data_from_books_file("Reports/update-report-books.txt",
                               books,
                               stock);
    return 0;
}
