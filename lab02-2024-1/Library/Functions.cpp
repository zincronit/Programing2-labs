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

void allocate_exact_data(char*** books,
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
        double ignore_price = read_double(fin, true);
        books_count++;
    }
    // initialize
    books = new char**[books_count + 1]{};
    stock = new int*[books_count + 1]{};
    allocate_exact_data(books,
                    stock,
                    static_books,
                    static_stock,
                    books_count);
    fin.close();
}

void print_book_details(std::ofstream& fout,
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
    for (int i = 0; books[i]; i++) print_book_details(fout, books[i], stock[i]);
}

void read_book_code(std::ifstream& fin, char*& book_code)
{
    char buffer[LINE_WIDTH]{};
    fin >> buffer;
    book_code = assign_string(buffer);
}

char** read_data_order(std::ifstream& fin, int& books_count)
{
    char** books = new char*[MAX_BOOKS]{};
    // bool is_end_of_line = false;
    while (true)
    {
        // is_end_of_line = fin.get() == '\n';
        if (fin.get() == '\n') break;
        read_book_code(fin, books[books_count]);
        books_count++;
    }
    // bool has_books = books_count != 0;
    if (books_count == 0) return nullptr;
    return books;
}

bool has_same_dni(int dni, int* customer_record)
{
    return dni == customer_record[0];
}

int find_index_customer(int dni, int** static_orders_by_customer, int customers_count)
{
    for (int i = 0; i < customers_count; i++)
    {
        if (has_same_dni(dni, static_orders_by_customer[i])) return i;
    }
    return NOT_FOUND;
}

void append_new_customer_with_order(int* & static_orders_by_customer,
                                    int dni,
                                    int order_code,
                                    int& customers_count)
{
    static_orders_by_customer = new int[MAX_ORDERS]{};
    static_orders_by_customer[0] = dni;
    static_orders_by_customer[1] = 1;
    static_orders_by_customer[2] = order_code;
    customers_count++;
}

void append_new_order_to_existing_customer(int* static_orders_by_customer, int order_code)
{
    int& orders_count = static_orders_by_customer[1];
    static_orders_by_customer[orders_count + 2] = order_code;
    orders_count++;
}

void update_orders_by_customer(int* static_orders_by_customer, int* & orders_by_customer)
{
    int orders_count = static_orders_by_customer[1];
    orders_by_customer = new int[orders_count + 3]{};
    for (int i = 0; i < orders_count + 2; i++)
    {
        orders_by_customer[i] = static_orders_by_customer[i];
    }
}

void update_books_by_order(char** & books_by_order,
                           char** static_books_by_order,
                           int books_count,
                           bool* & completed_orders)
{
    books_by_order = new char*[books_count + 1]{};
    completed_orders = new bool[books_count + 1]{};
    for (int i = 0; i < books_count; i++)
    {
        books_by_order[i] = static_books_by_order[i];
    }
}

void copy_orders_data(char*** books_by_order,
                      int** orders_by_customer,
                      bool** completed_orders,
                      int customers_count,
                      int orders_count,
                      int* books_count,
                      char*** static_books_by_order,
                      int** static_orders_by_customer)
{
    for (int i = 0; i < customers_count; i++)
    {
        update_orders_by_customer(static_orders_by_customer[i],
                                  orders_by_customer[i]);
        delete [] static_orders_by_customer[i];
    }
    for (int i = 0; i < orders_count; i++)
    {
        update_books_by_order(books_by_order[i],
                              static_books_by_order[i],
                              books_count[i],
                              completed_orders[i]);
        delete [] static_books_by_order[i];
    }
}

void read_orders_file(const char* filepath,
                      char*** & books_by_order,
                      int** & orders_by_customer,
                      bool** & completed_orders,
                      char*** books,
                      int** stock)
{
    std::ifstream fin;
    open_input_file(fin, filepath);
    char** static_books_by_order[MAX_ORDERS]{};
    int* static_orders_by_customer[MAX_CUSTOMERS]{};
    int orders_count = 0, customers_count = 0, books_count[MAX_ORDERS]{}, order_code, dni;
    // bool is_end_of_file = false;
    while (true)
    {
        // 000059,34460612   CRY6839    VYG3594
        order_code = read_int(fin, true);
        // is_end_of_file = fin.eof();
        if (fin.eof()) break;
        fin >> dni;
        static_books_by_order[order_code - 1] = read_data_order(fin, books_count[order_code - 1]);
        char temp[TEXT_LENGTH]{};
        // std::strcpy(temp, books_by_order[order_code - 1][0]);
        orders_count++;
        int index_customer = find_index_customer(dni, static_orders_by_customer, customers_count);
        if (index_customer == NOT_FOUND)
        {
            append_new_customer_with_order(static_orders_by_customer[customers_count],
                                           dni,
                                           order_code,
                                           customers_count);
        }
        else append_new_order_to_existing_customer(static_orders_by_customer[index_customer], order_code);
    }
    // initialize
    books_by_order = new char**[orders_count + 1];
    orders_by_customer = new int*[customers_count + 1];
    completed_orders = new bool*[orders_count + 1];
    copy_orders_data(books_by_order,
                     orders_by_customer,
                     completed_orders,
                     customers_count,
                     orders_count,
                     books_count,
                     static_books_by_order,
                     static_orders_by_customer);
    update_stock(books_by_order, completed_orders, books, stock);
    fin.close();
}

bool has_same_code(char* code_book, char** book)
{
    return std::strcmp(code_book, book[0]) == 0;
}

int find_index_book(char* code_book, char*** books)
{
    for (int i = 0; books[i]; i++)
    {
        if (has_same_code(code_book, books[i])) return i;
    }
    return NOT_FOUND;
}

void complete_order(int* stock, bool& completed_order)
{
    stock[0] -= 1;
    if (stock[0] >= 0) completed_order = true;
    else
    {
        stock[0] = 0;
        stock[1] += 1;
        completed_order = false;
    }
}

void find_book(char** books_by_order,
               bool* completed_orders,
               char*** books,
               int** stock)
{
    for (int i = 0; books_by_order[i]; i++)
    {
        int index_book = find_index_book(books_by_order[i], books);
        if (index_book != NOT_FOUND)
        {
            complete_order(stock[index_book], completed_orders[i]);
        }
    }
}

void update_stock(char*** books_by_order,
                  bool** completed_orders,
                  char*** books,
                  int** stock)
{
    for (int i = 0; books_by_order[i]; i++)
    {
        find_book(books_by_order[i], completed_orders[i], books, stock);
    }
}

void print_dni(std::ofstream& fout, int* customer)
{
    fout << "CUSTOMER  " << customer[0] << std::endl;
    print_line(fout, LINE_WIDTH, '=');
}

void print_order_information(std::ofstream& fout,
                             char** books_by_order,
                             bool* completed_orders,
                             int number_order)
{
    int width = LINE_WIDTH / COLUMNS;
    bool is_first_print = true;
    if (is_first_print)
    {
        print_text(fout, " ", width - 24);
        fout << std::right << std::setfill('0') << std::setw(6) << number_order;
        fout << std::setfill(' ');
        print_text_right(fout, books_by_order[0], width + 2);
        if (completed_orders[0] == false) print_text_right(fout, "NOT COMPLETED", width + 4);
        else print_text_right(fout, "COMPLETED", width + 4);
        fout << std::endl;
        is_first_print = false;
    }
    for (int i = 1; books_by_order[i]; i++)
    {
        print_text_right(fout, books_by_order[i], 2 * width - 16);
        if (completed_orders[i] == false) print_text_right(fout, "NOT COMPLETED", width + 4);
        else print_text_right(fout, "COMPLETED", width + 4);
        fout << std::endl;
    }
    print_line(fout, LINE_WIDTH, '-');
}

void print_customers_orders(std::ofstream& fout,
                            char*** books_by_order,
                            int* customer,
                            bool** completed_orders)
{
    int orders_count = customer[1];
    for (int i = 0; i < orders_count; i++)
    {
        print_header(fout);
        int number_order = customer[2 + i];
        print_order_information(fout, books_by_order[number_order - 1],
                                completed_orders[number_order - 1],
                                number_order);
    }
}

void print_header(std::ofstream& fout)
{
    int width = LINE_WIDTH / COLUMNS;
    print_text_right(fout, "Order Number ", width - 15);
    print_text_right(fout, "Book code", width);
    print_text_right(fout, "Status", width);
    fout << std::endl;
    print_line(fout, LINE_WIDTH, '-');
}

void print_text_right(std::ofstream& fout, const char* text, int width)
{
    fout << std::right << std::setw(width) << text;
}


void order_delivery_report(const char* filepath,
                           char*** books_by_order,
                           int** orders_by_customer,
                           bool** completed_orders)
{
    std::ofstream fout;
    open_output_file(fout, filepath);

    print_title(fout, "ORDER DELIVERY REPORT", LINE_WIDTH);
    for (int i = 0; orders_by_customer[i]; i++)
    {
        print_dni(fout, orders_by_customer[i]);
        print_customers_orders(fout,
                               books_by_order,
                               orders_by_customer[i],
                               completed_orders);
    }
    fout.close();
}
