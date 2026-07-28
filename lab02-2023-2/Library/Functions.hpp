//
// Created by zincronit on 7/26/26.
//

#ifndef LAB02_2023_2_FUNCTIONS_HPP
#define LAB02_2023_2_FUNCTIONS_HPP

#include "Utils.hpp"

void open_output_file(std::ofstream& fout, const char* filepath);
void open_input_file(std::ifstream& fin, const char* filepath);
int read_int(std::ifstream& fin, bool can_read_character);
double read_double(std::ifstream& fin, bool can_read_character);
char* read_dynamic_string(std::ifstream& fin, char delimiter);
char* assign_string(const char* buffer);
int read_date(std::ifstream& fin, bool can_read_character);
void print_line(std::ofstream& fout, int width, char character);
void print_text(std::ofstream& fout, const char* text, int width);
void print_spaces(std::ofstream& fout, int extra , int width);
char** read_static_product(std::ifstream& fin);

void copy_products_data(char*** products,
                             int* stock,
                             double* prices,
                             int products_count,
                             char*** static_products,
                             int* static_stock,
                             double* static_prices);

void read_products_file(const char* filepath,
                        char*** & products,
                        int* & stock,
                        double* & prices);

void print_test_report_products(const char* filepath,
                                char*** products,
                                int* stock,
                                double* prices);

int find_index_date(int* static_orders_date, int date , int dates_count);
int* assign_data_order(int dni, int number_products);

void register_new_date_with_order(char** & static_orders_code,
                    int** & static_dni_orders_count,
                    int* static_orders_date,
                    int& dates_count,
                    char* order_code,
                    int dni,
                    int number_products,
                    int date,
                    int& orders_count);

void append_order_to_existing_date(char** & static_orders_code,
                           int** & static_dni_orders_count,
                           char* order_code,
                           int dni,
                           int number_products,
                           int& orders_count);

void update_dni_orders_count(int** & dni_orders_count, int** static_dni_orders_count, int orders);
void update_orders_code(char** & orders_code, char** static_orders_code, int orders);

void copy_orders_data(char*** orders_code,
                      int*** dni_orders_count,
                      int* orders_date,
                      char*** static_orders_code,
                      int*** static_dni_orders_count,
                      int* static_orders_date,
                      int* orders,
                      int dates_count);

void read_data_orders_file(const char* filepath,
                           char*** & orders_code,
                           int*** & dni_orders_count,
                           int* & orders_date);

void print_orders_by_date(std::ofstream& fout, char** orders_code, int** dni_orders_count);
void print_data_orders_file(const char* filepath,
                            char*** orders_code,
                            int*** dni_orders_count,
                            int* orders_date);

void print_title(std::ofstream& fout, const char* title);
void print_header(std::ofstream& fout, int date);
bool is_matching_product_code(char** products, char* order_code);
int find_index_product(char*** products, char* orders_code);

void process_order_and_print(std::ofstream& fout,
                char** product,
                int& stock,
                double price,
                int* dni_orders_count,
                int& total_amount,
                int& total_amount_out_of_stock);


void print_order_information(std::ofstream& fout,
                             char*** products,
                             int* stock,
                             double* prices,
                             char** orders_code,
                             int** dni_orders_count);

void print_final_report(const char* filepath,
                        char*** products,
                        int* stock,
                        double* prices,
                        char*** orders_code,
                        int*** dni_orders_count,
                        int* orders_date);

#endif //LAB02_2023_2_FUNCTIONS_HPP
