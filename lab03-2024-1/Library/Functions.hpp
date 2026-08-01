//
// Created by zincronit on 7/31/26.
//

#ifndef LAB03_2024_1_FUNCTIONS_HPP
#define LAB03_2024_1_FUNCTIONS_HPP

#include "Utils.hpp"

void open_output_file(std::ofstream& fout, const char* filepath);
void open_input_file(std::ifstream& fin, const char* filepath);
void print_line(std::ofstream& fout, int width, char character);
void print_spaces(std::ofstream& fout, int extra, int width);
void print_text(std::ofstream& fout, const char* text, int width, bool should_print_left);
void print_title(std::ofstream& fout, const char* title, int width);
int read_int(std::ifstream& fin, bool can_read_character);
double read_double(std::ifstream& fin, bool can_read_character);
char* read_dynamic_string(std::ifstream& fin, char delimiter);
char* assign_string(const char* buffer);

//
char** read_book_information(std::ifstream& fin);
int* read_stock(std::ifstream& fin);
void append_capacity_for_new_books(char*** & books, int** & stocks, int& books_count, int& capacity);
void read_books_file(const char* filepath, char*** & books, int** & stock);
//
void print_book_characterist(std::ofstream& fout, int line_width);
void print_book_details(std::ofstream& fout, char** book, int* stock, int line_width);
void print_books_details(const char* filepath, char*** books, int** stocks);
//


bool has_same_dni(int dni, int* customer_record);
int find_index_customer(int dni, int** customers);
void append_capacity_for_new_customers(int** & customers, int& customers_count, int& customers_capacity);
void append_new_customer_with_order(int* customer_record,
                                    int& customers_count,
                                    int* orders_count_per_customer,
                                    int* orders_capacity_per_customer,
                                    int dni,
                                    int order_number);

void read_orders_file(std::ifstream& fin, char*** & orders, int** & customers, bool** & completed_orders);
void order_processing(const char* filepath,
                      char*** books,
                      int** stocks,
                      char*** orders,
                      int** customers,
                      bool** completed_orders);

#endif //LAB03_2024_1_FUNCTIONS_HPP
