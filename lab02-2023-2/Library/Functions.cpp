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

int read_date(std::ifstream& fin)
{
    int dd, mm, yy;
    char c;
    fin >> dd >> c >> mm >> c >> yy >> c;
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

void upload_values_in_arrays(char*** products,
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
    upload_values_in_arrays(products,
                            stock,
                            prices,
                            products_count,
                            static_products,
                            static_stock,
                            static_prices);
    fin.close();
}

void print_tets_report_products(const char* filepath,
                                char*** products,
                                int* stock,
                                double* prices)
{
    std::ofstream fout;
    open_output_file(fout, filepath);
    fout<< "TEST REPORT" << std::endl;
    print_line(fout, LINE_WIDTH , '=');
    print_text(fout, "PRODUCTS", 150);

}
