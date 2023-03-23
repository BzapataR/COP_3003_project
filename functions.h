//
// Created by Brian Zapata Resendiz on 3/7/23.
//

#ifndef COP_3003_PROJECT_FUNCTIONS_H
#define COP_3003_PROJECT_FUNCTIONS_H


#include <iostream>
#include <iomanip>
#include "json.h"
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>


using json = nlohmann::json;
namespace fs = std::filesystem;

void make_file ();
void write_file();
void read_file();
void main_menu ();
bool done_menu();
int option_a_or_b();
void search_directory();
void get_json ();
// int sum_of_house ()todo add cost for each house, also add cost json obj.
//

using std:: cout;
using std:: cin;
using std:: endl;

extern fs::path json_file_path;
extern fs::path dir_path;



class Person {
public:
    std::string name;
    std::string last_name;
    std::string street_address;
    std::string city;
    std::string phone_number;
    std:: string square_feet;



    void get_values() {

        cout << "Enter name: ";
        getline(std::cin, name);
        cout << "Enter last name: ";
        getline(std::cin, last_name);
        cout << "Enter street address: ";
        getline(std::cin, street_address);
        cout << "Enter city: ";
        getline(std::cin, city);
        cout << "Enter phone number: ";
        getline(std::cin, phone_number);
        cout << "Enter square feet: ";
        cin >> square_feet;

        std::cout << "Person added successfully.\n";
    }
//
    json to_json()  {
        return
                {
                        {"name", name},
                        {"last_name", last_name},
                        {"street_address", street_address},
                        {"city", city},
                        {"phone_number", phone_number},
                        {"square_feet", square_feet}
                };
    }


};

void add_person_to_address_book(Person p);

#endif //COP_3003_PROJECT_FUNCTIONS_H
