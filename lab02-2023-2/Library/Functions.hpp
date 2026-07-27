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
int read_date(std::ifstream& fin);
void print_line(std::ofstream& fout, int width, char character);
void print_text(std::ofstream& fout, const char* text, int width);
char** read_static_product(std::ifstream& fin);

void upload_values_in_arrays(char*** products,
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


#endif //LAB02_2023_2_FUNCTIONS_HPP
