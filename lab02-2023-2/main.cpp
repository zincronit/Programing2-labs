//
// Created by zincronit on 7/26/26.
//

#include "Library/Functions.hpp"

int main()
{
    char*** products;
    int* stock;
    double* prices;

    read_products_file("Data/products.csv",
                       products,
                       stock,
                       prices);

    print_test_report_products("Reports/test-report-products.csv",
                               products,
                               stock,
                               prices);

    int*** dni_orders_count;
    int* orders_date;
    char*** orders_code;

    read_data_orders_file("Data/orders.csv",
                          orders_code,
                          dni_orders_count,
                          orders_date);

    // std::cout << orders_date[0] << std::endl;
    // std::cout << orders_code[0][2][2] << std:: endl;
    print_data_orders_file("Reports/test-report-orders.csv",
                             orders_code,
                            dni_orders_count,
                             orders_date);

    print_final_report("Reports/final-report.csv",
                         products,
                         stock,
                         prices,
                         orders_code,
                         dni_orders_count,
                        orders_date);

    print_test_report_products("Reports/final-report-products.csv",
                               products,
                               stock,
                               prices);



    return 0;
}
