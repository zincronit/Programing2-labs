//
// Created by zincronit on 7/31/26.
//

#include "Functions.hpp"

void open_output_file(std::ofstream& fout, const char* filepath)
{
    fout.open(filepath, std::ios::out);
    if (not fout.is_open())
    {
        std::cout << "Could not open file " << filepath << std::endl;
        std::exit(1);
    }
}

void open_input_file(std::ifstream& fin, const char* filepath)
{
    fin.open(filepath, std::ios::in);
    if (not fin.is_open())
    {
        std::cout << "Could not open file " << filepath << std::endl;
        std::exit(1);
    }
}

void print_line(std::ofstream& fout, int width, char character)
{
    for (int i = 0; i < width; i++) fout.put(character);
    fout << std::endl;
}

void print_spaces(std::ofstream& fout, int extra, int width)
{
    for (int i = 0; i < width - extra; i++) fout.put(' ');
}

void print_text(std::ofstream& fout, const char* text, int width, bool should_print_left)
{
    if (should_print_left) fout << std::left;
    else fout << std::right;
    fout << std::setw(width) << text;
}

void print_title(std::ofstream& fout, const char* title, int width)
{
    fout << std::right << std::setw((std::strlen(title) + width) / 2) << title << std::endl;
}

int read_int(std::ifstream& fin, bool can_read_character)
{
    int value;
    fin >> value;
    if (can_read_character) fin.get();
    return value;
}

double read_double(std::ifstream& fin, bool can_read_character)
{
    double value;
    fin >> value;
    if (can_read_character) fin.get();
    return value;
}

char* read_dynamic_string(std::ifstream& fin, char delimiter)
{
    char buffer[TEXT_LENGTH];
    char* string = nullptr;
    fin.getline(buffer, TEXT_LENGTH, delimiter);
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

char** read_book_information(std::ifstream& fin)
{
    char code[TEXT_LENGTH];
    char** book;
    fin.getline(code, TEXT_LENGTH, ',');
    if (fin.eof()) return nullptr;
    book = new char*[3];
    book[0] = assign_string(code);
    book[1] = read_dynamic_string(fin, ',');
    book[2] = read_dynamic_string(fin, ',');
    return book;
}

int* read_stock(std::ifstream& fin)
{
    int* stock = new int[2]{};
    double price;
    stock[0] = read_int(fin, ',');
    stock[1] = 0;
    price = read_double(fin, ',');
    return stock;
}

void append_capacity_for_new_books(char*** & books, int** & stocks, int& books_count, int& capacity)
{
    char*** aux_books;
    int** aux_stocks;
    capacity += INCREASE;
    if (books == nullptr)
    {
        books = new char**[capacity]{};
        stocks = new int*[capacity]{};
        books_count++;
    }
    else
    {
        aux_books = new char**[capacity]{};
        aux_stocks = new int*[capacity]{};
        for (int i = 0; books[i]; i++)
        {
            aux_books[i] = books[i];
            aux_stocks[i] = stocks[i];
        }
        delete [] books;
        delete [] stocks;
        books = aux_books;
        stocks = aux_stocks;
    }
}

void read_books_file(const char* filepath, char*** & books, int** & stocks)
{
    std::ifstream fin;
    open_input_file(fin, filepath);
    books = nullptr;
    stocks = nullptr;
    char** book;
    int* stock;
    int books_count = 0, capacity = 0;
    while (true)
    {
        // IIM5175,Diamantes y pedernales,Jose Maria Arguedas,2,30.23
        book = read_book_information(fin);
        if (fin.eof()) break;
        stock = read_stock(fin);
        if (books_count == capacity)
            append_capacity_for_new_books(books, stocks, books_count, capacity);
        books[books_count - 1] = book;
        stocks[books_count - 1] = stock;
        books_count++;
    }
    fin.close();
}


void print_book_characterist(std::ofstream& fout, int line_width)
{
    int width = line_width / 5;
    print_line(fout, line_width, '=');
    print_text(fout, "CODE", width - 18, true);
    print_text(fout, "NAME", width + 33, true);
    print_text(fout, "AUTHOR", width, true);
    print_text(fout, "STOCK", width - 16, true);
    print_text(fout, "UNSERVED QUANTITY", width, true);
    fout << std::endl;
    print_line(fout, line_width, '-');
}

void print_book_details(std::ofstream& fout, char** book, int* stock, int line_width)
{
    int width = line_width / 5;
    print_text(fout, book[0], width - 18, true);
    print_text(fout, book[1], width + 33, true);
    print_text(fout, book[2], width, true);
    fout << std::setw(width - 16) << stock[0];
    fout << stock[1];
    fout << std::endl;
}

void print_books_details(const char* filepath, char*** books, int** stocks)
{
    std::ofstream fout;
    open_output_file(fout, filepath);
    int line_width = 150;
    int width = line_width / 5;
    print_title(fout, "TEST REPORT", line_width);
    print_book_characterist(fout, line_width);
    for (int i = 0; books[i]; i++)
    {
        print_book_details(fout, books[i], stocks[i], line_width);
    }
    fout.close();
}

void append_capacity_for_new_customers(int** & customers, int& customers_count, int& customers_capacity)
{
    int** aux;
    customers_capacity += INCREASE;
    if (customers == nullptr)
    {
        customers = new int*[customers_count]{};
        customers_count = 1;
    }
    else
    {
        aux = new int*[customers_count]{};
        for (int i = 0; customers[i]; i++)
        {
            aux[i] = customers[i];
        }
        delete [] customers;
    }
    customers = aux;
}

bool has_same_dni(int dni, int* customer_record)
{
    return dni == customer_record[0];
}

int find_index_customer(int dni, int** customers)
{
    for (int i = 0; customers[i]; i++)
    {
        if (has_same_dni(dni, customers[i])) return i;
    }
    return NOT_FOUND;
}

void append_new_customer_with_order(int* & customer_record,
                                    int& customers_count,
                                    int& orders_count_per_customer,
                                    int& orders_capacity_per_customer,
                                    int dni,
                                    int order_number)
{
    append_capacity_for_record_customer(customer_record, orders_capacity_per_customer);
    customer_record[0] = dni;
    customer_record[ORDERS_COUNT]++;
    customer_record[2] = order_number;
    orders_count_per_customer += 3;
    customers_count++;
}

void append_capacity_for_record_customer(int* & customer_record, int& orders_capacity_per_customer)
{
    int* aux_customers_record;
    orders_capacity_per_customer += INCREASE;
    if (customer_record == nullptr)
    {
        customer_record = new int[orders_capacity_per_customer]{};
    }
    else
    {
        aux_customers_record = new int[orders_capacity_per_customer]{};
        for (int i = 0; i < customer_record[ORDERS_COUNT] + 2; i++)
        {
            aux_customers_record[i] = customer_record[i];
        }
        delete [] customer_record;
        customer_record = aux_customers_record;
    }
}

void append_new_orders_to_existing_customers(int* & customer_record,
                                             int& orders_count_per_customer,
                                             int& orders_capacity_per_customer,
                                             int order_number)
{
    if (orders_count_per_customer == orders_capacity_per_customer)
        append_capacity_for_record_customer(customer_record, orders_capacity_per_customer);
    customer_record[orders_count_per_customer] = order_number;
    orders_count_per_customer++;
}

void append_capacity_for_orders(char*** & orders, int& orders_count, int& orders_capacity, bool** & completed_orders)
{
    char*** aux;
    bool** temp;
    orders_capacity += INCREASE;
    if (orders == nullptr)
    {
        orders = new char**[orders_capacity]{};
        completed_orders = new bool*[orders_capacity]{};
        orders_count = 2;
    }
    else
    {
        aux = new char**[orders_capacity]{};
        temp = new bool*[orders_capacity]{};
        for (int i = 0; orders[i]; i++)
        {
            aux[i] = orders[i];
            temp[i] = completed_orders[i];
        }
        delete [] orders;
        delete [] completed_orders;
        orders = aux;
        completed_orders = temp;
    }
}

void append_capacity_for_books_per_order(char** & order,
                                         int& books_count,
                                         int& books_capacity,
                                         bool*& is_book_delivered)
{
    char** aux_order;
    bool* aux;
    books_capacity += INCREASE;
    if (order == nullptr)
    {
        order = new char*[books_capacity]{};
        is_book_delivered = new bool[books_capacity]{};
        books_count = 1;
    }
    else
    {
        aux_order = new char*[books_capacity]{};
        aux = new bool[books_capacity]{};
        for (int i = 0; order[i]; i++)
        {
            aux_order[i] = order[i];
            aux[i] = is_book_delivered[i];
        }
        delete [] order;
        delete [] is_book_delivered;
        order = aux_order;
        is_book_delivered = aux;
    }
}

char** get_order_information(std::ifstream& fin, bool*& is_book_delivered)
{
    char** order;
    int books_count = 0, books_capacity = 0;
    while (true)
    {
        if (books_count == books_capacity)
            append_capacity_for_books_per_order(order,
                                                books_count,
                                                books_capacity,
                                                is_book_delivered);
        char book[TEXT_LENGTH];
        if (fin.eof() or fin.get() == '\n') return nullptr;
        fin >> book;
        order[books_count - 1] = assign_string(book);
        books_count++;
    }
}

void read_orders_file(std::ifstream& fin, char*** & orders, int** & customers, bool** & completed_orders)
{
    int order_number, dni;
    int orders_count = 0, customers_count = 0, orders_count_per_customer[MAX_ORDERS]{};
    int orders_capacity = 0, customers_capacity = 0, orders_capacity_per_customer[MAX_ORDERS]{};
    while (true)
    {
        // 000059,34460612   CRY6839    VYG3594
        order_number = read_int(fin, true);
        if (fin.eof()) break;
        fin >> dni;
        if (customers_count == customers_capacity)
            append_capacity_for_new_customers(customers, customers_count, customers_capacity);
        int index_customer = find_index_customer(dni, customers);
        if (index_customer == NOT_FOUND)
            append_new_customer_with_order(customers[customers_count],
                                           customers_count,
                                           orders_count_per_customer[customers_count],
                                           orders_capacity_per_customer[customers_count],
                                           dni,
                                           order_number);
        else
            append_new_orders_to_existing_customers(customers[index_customer],
                                                    orders_count_per_customer[index_customer],
                                                    orders_capacity_per_customer[index_customer],
                                                    order_number);
        //
        if (orders_count == orders_capacity)
            append_capacity_for_orders(orders, orders_count, orders_capacity, completed_orders);
        orders[order_number - 1] = get_order_information(fin, completed_orders[order_number - 1]);
        orders_count++;
    }
}

void update_completed_orders(char*** books, int** stocks,char*** orders, bool** completed_orders)
{
    // falte actualizor los datos, hacer el reporte, etc
}

void order_processing(const char* filepath,
                      char*** books,
                      int** stocks,
                      char*** & orders,
                      int** & customers,
                      bool** & completed_orders)
{
    std::ifstream fin;
    open_input_file(fin, filepath);
    orders = nullptr;
    customers = nullptr;
    completed_orders = nullptr;
    read_orders_file(fin, orders, customers, completed_orders);

    fin.close();
}
