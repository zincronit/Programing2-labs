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
    fin >> dd >> c >> mm >> c >> yy;
    if (can_read_character) fin.get();
    return yy * 10000 + mm * 100 + dd;
}

void print_date(std::ofstream& fout, int date)
{
    int year = date / 10000;
    int month = date % 10000 / 100;
    int day = date % 100;
    fout << std::right << std::setfill('0') << std::setw(2) << day << '/'
        << std::setw(2) << month << '/'
        << std::setw(4) << year << std::setfill(' ') << std::left;
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

void register_new_date_with_order(char** & static_orders_code,
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

void append_order_to_existing_date(char** & static_orders_code,
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
    dni_orders_count = new int*[orders + 1]{};
    for (int i = 0; i < orders; i++)
    {
        dni_orders_count[i] = static_dni_orders_count[i];
    }
}

void update_orders_code(char** & orders_code, char** static_orders_code, int orders)
{
    orders_code = new char*[orders + 1]{};
    for (int i = 0; i < orders; i++)
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
                      int* orders,
                      int dates_count)
{
    for (int i = 0; i < dates_count; i++)
    {
        orders_date[i] = static_orders_date[i];
        update_dni_orders_count(dni_orders_count[i],
                                static_dni_orders_count[i],
                                orders[i]);
        update_orders_code(orders_code[i], static_orders_code[i], orders[i]);
        delete [] static_orders_code[i];
        delete [] static_dni_orders_count[i];
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
            register_new_date_with_order(static_orders_code[dates_count],
                                         static_dni_orders_count[dates_count],
                                         static_orders_date,
                                         dates_count,
                                         order_code,
                                         dni,
                                         number_products,
                                         date,
                                         orders[dates_count]);
        else
            append_order_to_existing_date(static_orders_code[index],
                                          static_dni_orders_count[index],
                                          order_code,
                                          dni,
                                          number_products,
                                          orders[index]);
    }
    // initialize
    orders_code = new char**[dates_count + 1]{};
    dni_orders_count = new int**[dates_count + 1]{};
    orders_date = new int[dates_count + 1]{};
    copy_orders_data(orders_code,
                     dni_orders_count,
                     orders_date,
                     static_orders_code,
                     static_dni_orders_count,
                     static_orders_date,
                     orders,
                     dates_count);
    fin.close();
}

void print_orders_by_date(std::ofstream& fout, char** orders_code, int** dni_orders_count)
{
    int width = 120 / 3;
    for (int i = 0; orders_code[i]; i++)
    {
        print_text(fout, orders_code[i], width);
        int* temporal_pointer = dni_orders_count[i];
        fout << std::setw(width) << temporal_pointer[0]
            << temporal_pointer[1] << std::endl;
    }
}

void print_data_orders_file(const char* filepath,
                            char*** orders_code,
                            int*** dni_orders_count,
                            int* orders_date)
{
    std::ofstream fout;
    open_output_file(fout, filepath);
    fout << "TEST REPORT" << std::endl;
    for (int i = 0; orders_date[i]; i++)
    {
        print_line(fout, 120, '=');
        fout << "DATE   ";
        print_date(fout, orders_date[i]);
        fout << std::endl;
        print_line(fout, 120, '=');
        int width = 120 / 3;
        print_text(fout, "CODE", width);
        print_text(fout, "DNI", width);
        print_text(fout, "COUNT", width);
        fout << std::endl;
        print_line(fout, 120, '-');
        print_orders_by_date(fout, orders_code[i], dni_orders_count[i]);
    }
    fout.close();
}

void print_title(std::ofstream& fout, const char* title)
{
    fout << std::right << std::setw((std::strlen(title) + LINE_WIDTH) / 2) << title << std::endl;
}

void print_header(std::ofstream& fout, int date)
{
    int width = LINE_WIDTH / COLUMNS;
    print_line(fout, LINE_WIDTH, '=');
    fout << "DATE   ";
    print_date(fout, date);
    fout << std::endl;
    print_text(fout, "No.  DNI", width);
    print_text(fout, "PRODUCT", width + 32);
    print_text(fout, "COUNT", width - 8);
    print_text(fout, "PRICE", width);
    print_text(fout, "TOTAL REVENUE", width);
    fout << std::endl;
    print_line(fout, LINE_WIDTH, '-');
}

bool is_matching_product_code(char** products, char* order_code)
{
    return std::strcmp(products[0], order_code) == 0;
}

int find_index_product(char*** products, char* orders_code)
{
    for (int i = 0; products[i]; i++)
    {
        if (is_matching_product_code(products[i], orders_code)) return i;
    }
    return NOT_FOUND;
}

void process_order_and_print(std::ofstream& fout,
                             char** product,
                             int& stock,
                             double price,
                             int* dni_orders_count,
                             int& total_amount,
                             int& total_amount_out_of_stock)
{
    int width = LINE_WIDTH / COLUMNS;
    fout << std::setw(width - 13) << dni_orders_count[0];
    fout << product[0] << "  " << product[1];
    print_spaces(fout, std::strlen(product[0]) + std::strlen(product[1]), width + 40);
    fout << std::setw(width - 10) << dni_orders_count[1]
        << std::setw(width) << price;
    stock -= dni_orders_count[1];
    bool has_stock = stock > 0;
    if (has_stock)
    {
        fout << price * dni_orders_count[1] << std::endl;
        total_amount += price * dni_orders_count[1];
    }
    else
    {
        fout << "OUT OF STOCK" << std::endl;
        total_amount_out_of_stock += price * dni_orders_count[1];
        stock = 0;
    }
}

void print_order_information(std::ofstream& fout,
                             char*** products,
                             int* stock,
                             double* prices,
                             char** orders_code,
                             int** dni_orders_count)
{
    int total_amount = 0;
    int total_amount_out_of_stock = 0;
    for (int i = 0; orders_code[i]; i++)
    {
        fout << std::right << std::setw(2) << i << std::left << ")  ";
        int index_product = find_index_product(products, orders_code[i]);
        process_order_and_print(fout,
                                products[index_product],
                                stock[index_product],
                                prices[index_product],
                                dni_orders_count[i],
                                total_amount,
                                total_amount_out_of_stock);
    }
    print_line(fout, LINE_WIDTH, '-');
    fout << std::setw(LINE_WIDTH - 26) << "Total amount:" << total_amount << std::endl;
    fout << std::setw(LINE_WIDTH - 26) << "Total amount by out of stock:" << total_amount_out_of_stock << std::endl;
}

void print_final_report(const char* filepath,
                        char*** products,
                        int* stock,
                        double* prices,
                        char*** orders_code,
                        int*** dni_orders_count,
                        int* orders_date)
{
    std::ofstream fout;
    open_output_file(fout, filepath);
    print_title(fout, "ORDER DELIVERY REPORT");
    fout << std::fixed << std::setprecision(2);
    for (int i = 0; orders_date[i]; i++)
    {
        print_header(fout, orders_date[i]);
        print_order_information(fout,
                                products,
                                stock,
                                prices,
                                orders_code[i],
                                dni_orders_count[i]);
    }
}
