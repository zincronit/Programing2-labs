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

void copy_data_books(char*** books,
                     int** stock,
                     char*** static_books,
                     int** static_stock,
                     int books_count);

void read_books_file(const char* filepath,
                     char*** & books,
                     int** & stock);

void print_information_book(std::ofstream& fout,
                            char** books,
                            int* stock);

void print_data_from_books_file(const char* filepath,
                                char*** books,
                                int** stock);

void read_orders_file(const char* filepath,
                      char*** & books_by_order,
                      int** & orders_by_customer,
                      bool** & completed_orders);


#endif //LAB02_2024_1_FUNCTIONS_HPP
