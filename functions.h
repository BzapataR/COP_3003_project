//
// Created by Brian Zapata Resendiz on 3/7/23.
//

#ifndef COP_3003_PROJECT_FUNCTIONS_H
#define COP_3003_PROJECT_FUNCTIONS_H


#include <iostream>
#include <iomanip>
#include "json.hpp"
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <map>
#include <thread>
#include <chrono>
#include <cctype>


using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;
namespace fs = std::filesystem;
using std:: cout;
using std:: cin;
using std:: endl;
using std:: string;
using std:: vector;
using std:: chrono::milliseconds;
using std:: this_thread::sleep_for;





extern fs::path json_file_path;
extern fs::path dir_path;


class Files{ //here for .txt uses maybe more in future
private:
    string file=json_file_path;
public:
    const string company_name= "J&A lawn care";
    const string company_email="j&alawncare@something";
    const string company_address="1111 j&a HQ";
    const string company_second_line_address = "Naples, FL xxxxx";
    string todays_date;
    string invoice_ID;
    const double tax_rate= 1.07;
    static string set_todays_date();
    Files();
    void make_invoice();
    static void print_file(const string& filename);
};


class Customer : public Files {//.json oriented
public:
    void get_values();
    ordered_json to_json();
private:
    string name;
    string last_name;
    string street_address;
    string city;
    string zip_code;
    string phone_number;
    string square_feet;
    vector<std::map<string,double>> jobs;
    double cost_of_jobs;
    double total_cost_with_tax;
    void get_job ();
};

//void add_person_to_address_book(Customer p);

class Menus {// all menu options
public:
    Menus();
    static void main_menu(Files file);
    static void read_file();
    static void read_file(milliseconds time_delay);
    static void make_file();
    static void write_file();
    static void get_json();
    static void search_directory();
    static int option_a_or_b();
    static bool done_menu();
    static void edit_jobs();
    static void add_person_to_address_book(Customer p);

};

#endif //COP_3003_PROJECT_FUNCTIONS_H
