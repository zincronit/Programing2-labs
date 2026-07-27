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
    fin.open(filepath);
    if (not fin.is_open())
    {
        std::cout << "Error opening file " << filepath << std::endl;
        std::exit(1);
    }
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

int read_date(std::ifstream& fin, bool can_read_character)
{
    int dd, mm, yy;
    char c;
    fin >> dd >> c >> mm >> c >> yy >> c;
    if (can_read_character) fin.get();
    return yy * 10000 + mm * 100 + dd;
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

void print_spaces(std::ofstream& fout, int extra, int width)
{
    for (int i = 0; i < width - extra; i++) fout.put(' ');
}

char** read_static_product(std::ifstream& fin)
{
    char buffer[TEXT_LENGTH];
    fin.getline(buffer, TEXT_LENGTH, ',');
    if (fin.eof()) return nullptr;
    char** product = new char*[2];
    product[0] = assign_string(buffer);
    product[1] = read_dynamic_string(fin, ',');
    return product;
}

void copy_products_data(char*** products,
                        int* stock,
                        double* prices,
                        int products_count,
                        char*** static_products,
                        int* static_stock,
                        double* static_prices)
{
    for (int i = 0; i < products_count; i++)
    {
        products[i] = static_products[i];
        stock[i] = static_stock[i];
        prices[i] = static_prices[i];
    }
}

void read_products_file(const char* filepath,
                        char*** & products,
                        int* & stock,
                        double* & prices)
{
    std::ifstream fin;
    open_input_file(fin, filepath);
    char** static_products[MAX_PRODUCTS]{};
    int static_stock[MAX_PRODUCTS]{};
    double static_prices[MAX_PRODUCTS]{};
    int products_count = 0;
    while (true)
    {
        //BIT-434,Campana Extractora modelo Glass,375.09,10
        static_products[products_count] = read_static_product(fin);
        if (fin.eof()) break;
        static_prices[products_count] = read_double(fin, true);
        static_stock[products_count] = read_int(fin, true);
        products_count++;
    }
    products_count++;
    // initialize
    products = new char**[products_count]{};
    stock = new int[products_count]{};
    prices = new double[products_count]{};
    copy_products_data(products,
                       stock,
                       prices,
                       products_count,
                       static_products,
                       static_stock,
                       static_prices);
    fin.close();
}

void print_values(std::ofstream& fout, char** products, int stock, double prices)
{
    int width = 120 / 3;
    // char buffer[TEXT_LENGTH]{};
    // std::strcpy(buffer, products[0]);
    // std::strcat(buffer, " - ");
    // std::strcat(buffer, products[1]);
    // print_text(fout, buffer, width);
    fout << products[0] << "  " << products[1];
    print_spaces(fout, std::strlen(products[0]) + std::strlen(products[1]), width + 24);
    fout << std::setw(width) << stock << prices << std::endl;
}

void print_test_report_products(const char* filepath,
                                char*** products,
                                int* stock,
                                double* prices)
{
    std::ofstream fout;
    open_output_file(fout, filepath);
    fout << "TEST REPORT" << std::endl;
    print_line(fout, 120, '=');
    int width = 120 / 3;
    print_text(fout, "PRODUCT - DESCRIPTION", width + 27);
    print_text(fout, "STOCK", width);
    print_text(fout, "PRICE", width);
    fout << std::endl << std::fixed << std::setprecision(2);
    print_line(fout, 120, '-');
    for (int i = 0; prices[i]; i++) print_values(fout, products[i], stock[i], prices[i]);
    fout.close();
}

int find_index_date(int* static_orders_date, int date, int dates_count)
{
    for (int i = 0; i < dates_count; i++)
    {
        if (date == static_orders_date[i]) return i;
    }
    return NOT_FOUND;
}

int* assign_data_order(int dni, int number_products)
{
    int* data_order = new int[2];
    data_order[0] = dni;
    data_order[1] = number_products;
    return data_order;
}

void add_order_date(char** & static_orders_code,
                    int** & static_dni_orders_count,
                    int* static_orders_date,
                    int& dates_count,
                    char* order_code,
                    int dni,
                    int number_products,
                    int date,
                    int& orders_count)
{
    // static_orders_date
    static_orders_date[dates_count] = date;
    static_orders_code = new char*[MAX_ORDERS]{};
    static_orders_code[orders_count] = assign_string(order_code);
    static_dni_orders_count = new int*[MAX_ORDERS]{};
    static_dni_orders_count[orders_count] = assign_data_order(dni, number_products);
    orders_count++;
    dates_count++;
}

void add_new_order_to_date(char** & static_orders_code,
                           int** & static_dni_orders_count,
                           char* order_code,
                           int dni,
                           int number_products,
                           int& orders_count)
{
    static_orders_code[orders_count] = assign_string(order_code);
    static_dni_orders_count[orders_count] = assign_data_order(dni, number_products);
    orders_count++;
}

void update_dni_orders_count(int** & dni_orders_count, int** static_dni_orders_count, int orders)
{
    dni_orders_count = new int*[orders + 1];
    for (int i = 0; dni_orders_count[i]; i++)
    {
        dni_orders_count[i] = static_dni_orders_count[i];
    }
}

void update_orders_code(char** & orders_code, char** static_orders_code, int orders)
{
    orders_code = new char*[orders + 1];
    for (int i = 0; orders_code[i]; i++)
    {
        orders_code[i] = static_orders_code[i];
    }
}

void copy_orders_data(char*** orders_code,
                      int*** dni_orders_count,
                      int* orders_date,
                      char*** static_orders_code,
                      int*** static_dni_orders_count,
                      int* static_orders_date,
                      int* orders)
{
    for (int i = 0; orders_date[i]; i++)
    {
        orders_date[i] = static_orders_date[i];
        update_dni_orders_count(dni_orders_count[i],
                                static_dni_orders_count[i],
                                orders[i]);
        update_orders_code(orders_code[i], static_orders_code[i], orders[i]);
    }
}

void read_data_orders_file(const char* filepath,
                           char*** & orders_code,
                           int*** & dni_orders_count,
                           int* & orders_date)
{
    std::ifstream fin;
    open_input_file(fin, filepath);
    char** static_orders_code[MAX_DATES]{};
    int** static_dni_orders_count[MAX_DATES]{};
    int static_orders_date[MAX_DATES]{};
    char order_code[TEXT_LENGTH];
    int dni, number_products, date, dates_count = 0, orders[MAX_DATES]{};
    while (true)
    {
        //JXD-139,50375303,6,24/08/2023
        fin.getline(order_code, TEXT_LENGTH, ',');
        if (fin.eof()) break;
        dni = read_int(fin, true);
        number_products = read_int(fin, true);
        date = read_date(fin, true);
        int index = find_index_date(static_orders_date, date, dates_count);
        if (index == NOT_FOUND)
            add_order_date(static_orders_code[dates_count],
                           static_dni_orders_count[dates_count],
                           static_orders_date,
                           dates_count,
                           order_code,
                           dni,
                           number_products,
                           date,
                           orders[dates_count]);
        else
            add_new_order_to_date(static_orders_code[index],
                                  static_dni_orders_count[index],
                                  order_code,
                                  dni,
                                  number_products,
                                  orders[index]);
    }
    dates_count++;
    // initialize
    orders_code = new char**[dates_count]{};
    dni_orders_count = new int**[dates_count]{};
    orders_date = new int[dates_count]{};
    copy_orders_data(orders_code,
                     dni_orders_count,
                     orders_date,
                     static_orders_code,
                     static_dni_orders_count,
                     static_orders_date,
                     orders);
    fin.close();
}
