//
// Created by zincronit on 7/28/26.
//

#include "Functions.hpp"

void open_output_file(std::ofstream& fout, const char* filepath)
{
    fout.open(filepath, std::ios::out);
    if (not fout.is_open())
    {
        std::cout << "Error opening file " << filepath << std::endl;
        std::exit(1);
    }
}

void open_input_file(std::ifstream& fin, const char* filepath)
{
    fin.open(filepath, std::ios::in);
    if (not fin.is_open())
    {
        std::cout << "Error opening file " << filepath << std::endl;
        std::exit(1);
    }
}

void print_line(std::ofstream& fout, int width, char character)
{
    for (int i = 0; i < width; i++) fout.put(character);
    fout << std::endl;
}

void print_text(std::ofstream& fout, const char* text, int width)
{
    fout << std::left << std::setw(width) << text;
}

void print_title(std::ofstream& fout, const char* title, int width)
{
    fout << std::right << std::setw((std::strlen(title) + width) / 2) << title << std::endl;
    print_line(fout, width, '=');
}

int read_int(std::ifstream& fin, bool can_read_character)
{
    int value = 0;
    fin >> value;
    if (can_read_character) fin.get();
    return value;
}

double read_double(std::ifstream& fin, bool can_read_character)
{
    double value = 0;
    fin >> value;
    if (can_read_character) fin.get();
    return value;
}

char* read_dynamic_string(std::ifstream& fin, char character)
{
    char buffer[TEXT_LENGTH];
    char* string = nullptr;
    fin.getline(buffer, TEXT_LENGTH, character);
    if (fin.eof()) return string;
    string = new char[std::strlen(buffer) + 1];
    std::strcpy(string, buffer);
    return string;
}

char* assign_string(const char* buffer)
{
    char* string = new char[std::strlen(buffer) + 1];
    std::strcpy(string, buffer);
    return string;
}

char** read_data_from_book(std::ifstream& fin)
{
    char code[TEXT_LENGTH];
    fin.getline(code, TEXT_LENGTH, ',');
    if (fin.eof()) return nullptr;
    char** data_book = new char*[3]{};
    data_book[0] = assign_string(code);
    data_book[1] = read_dynamic_string(fin, ',');
    data_book[2] = read_dynamic_string(fin, ',');

    return data_book;
}

int* read_stock(std::ifstream& fin)
{
    int* stock = new int [2]{};
    stock[0] = read_int(fin, ',');
    stock[1] = 0;
    return stock;
}

void copy_data_books(char*** books,
                     int** stock,
                     char*** static_books,
                     int** static_stock,
                     int books_count)
{
    for (int i = 0; i < books_count; i++)
    {
        books[i] = static_books[i];
        stock[i] = static_stock[i];
    }
}

void read_books_file(const char* filepath,
                     char*** & books,
                     int** & stock)
{
    std::ifstream fin;
    open_input_file(fin, filepath);
    char** static_books[MAX_BOOKS];
    int* static_stock[MAX_BOOKS];
    int books_count = 0;
    while (true)
    {
        // IIM5175,Diamantes y pedernales,Jose Maria Arguedas,2,30.23
        static_books[books_count] = read_data_from_book(fin);
        if (fin.eof()) break;
        static_stock[books_count] = read_stock(fin);
        double trosh = read_double(fin, true);
        books_count++;
    }
    // initialize
    books = new char**[books_count + 1]{};
    stock = new int*[books_count + 1]{};
    copy_data_books(books,
                    stock,
                    static_books,
                    static_stock,
                    books_count);
    fin.close();
}

void print_information_book(std::ofstream& fout,
                            char** books,
                            int* stock)
{
    int width = 150 / 5;
    print_text(fout, books[0], width - 18);
    print_text(fout, books[1], width + 30);
    print_text(fout, books[2], width + 4);
    fout << std::setw(width) << stock[0];
    fout << stock[1] << std::endl;
}

void print_data_from_books_file(const char* filepath,
                                char*** books,
                                int** stock)
{
    std::ofstream fout;
    open_output_file(fout, filepath);
    print_title(fout, "TEST REPORT", 150);
    int width = 150 / 5;
    print_text(fout, "CODE", width - 10);
    print_text(fout, "NAME", width + 24);
    print_text(fout, "AUTHOR", width);
    print_text(fout, "STOCK", width - 10);
    print_text(fout, "UNSERVED QUANTITY", width);
    fout << std::endl;
    print_line(fout, 150, '-');
    for (int i = 0; books[i]; i++) print_information_book(fout, books[i], stock[i]);
}
