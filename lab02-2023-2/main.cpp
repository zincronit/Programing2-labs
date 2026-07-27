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

    return 0;
}