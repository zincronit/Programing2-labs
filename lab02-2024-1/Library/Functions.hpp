//
// Created by zincronit on 7/28/26.
//

#ifndef LAB02_2024_1_FUNCTIONS_HPP
#define LAB02_2024_1_FUNCTIONS_HPP

#include "Utils.hpp"

void open_output_file(std::ofstream& fout, const char* filepath);
void open_input_file(std::ifstream& fin, const char* filepath);
void print_line(std::ofstream& fout, int width, char character);
void print_text(std::ofstream& fout, const char* text, int width);
void print_title(std::ofstream& fout, const char* title, int width);
int read_int(std::ifstream& fin, bool can_read_character);
double read_double(std::ifstream& fin, bool can_read_character);
char* read_dynamic_string(std::ifstream& fin, char character);
char* assign_string(const char* buffer);
char** read_data_from_book(std::ifstream& fin);
int* read_stock(std::ifstream& fin);

void allocate_exact_data(char*** books,
                     int** stock,
                     char*** static_books,
                     int** static_stock,
                     int books_count);

void read_books_file(const char* filepath,
                     char*** & books,
                     int** & stock);

void print_book_details(std::ofstream& fout,
                            char** books,
                            int* stock);

void print_data_from_books_file(const char* filepath,
                                char*** books,
                                int** stock);

char** read_data_order(std::ifstream& fin, int& books_count);
bool has_same_dni(int dni, int* customer_record);
int find_index_customer(int dni, int** static_orders_by_customer, int customers_count);

void append_new_customer_with_order(int* & static_orders_by_customer,
                                    int dni,
                                    int order_code,
                                    int& customers_count);

void append_new_order_to_existing_customer(int* static_orders_by_customer, int order_code);
void update_orders_by_customer(int* static_orders_by_customer, int* &orders_by_customer);

void update_books_by_order(char** &books_by_order,
                           char** static_books_by_order,
                           int books_count,
                           bool* &completed_orders);

void copy_orders_data(char*** books_by_order,
                      int** orders_by_customer,
                      bool** completed_orders,
                      int customers_count,
                      int orders_count,
                      int* books_count,
                      char*** static_books_by_order,
                      int** static_orders_by_customer);

void read_orders_file(const char* filepath,
                      char*** & books_by_order,
                      int** & orders_by_customer,
                      bool** & completed_orders,
                      char*** books,
                      int** stock);

bool has_same_code(char* code_book, char** book);
int find_index_book(char* code_book, char*** books);
void complete_order(int* stock, bool& completed_order);

void find_book(char** books_by_order,
              bool* completed_orders,
              char*** books,
              int** stock);

void update_stock(char*** books_by_order,
                  bool** completed_orders,
                  char*** books,
                  int** stock);

void print_header(std::ofstream& fout);
void print_text_right(std::ofstream& fout, const char* text, int width);
void print_dni(std::ofstream& fout, int* customer);

void print_order_information(std::ofstream& fout,
                             char** books_by_order,
                             bool* completed_orders,
                             int number_order);

void print_customers_orders(std::ofstream& fout,
                            char*** books_by_order,
                            int* customer,
                            bool** completed_orders);


void order_delivery_report(const char* filepath,
                            char*** books_by_order,
                            int** orders_by_customer,
                            bool** completed_orders);


#endif //LAB02_2024_1_FUNCTIONS_HPP
