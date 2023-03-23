#include "functions.h"
//
// Created by Brian Zapata Resendiz on 3/7/23.
//

fs::path json_file_path;
fs:: path dir_path;


void get_json (){
    std:: string temp_str;
    json_file_path= "";


    // json_file_path="/Users/brianzapataresendiz/Documents/test2.json" example
    cout << "Enter .json file path or hit enter to look for one in "
            "a specific directory.\n";
    getline(cin, temp_str);
    json_file_path=temp_str;

    cout << "json file is: " << json_file_path << endl;
    cout <<
         "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

    if(json_file_path=="")
    {
        cout << "Please enter a file path to look or make a .json file.\n";
        // /Users/brianzapataresendiz/Documents/ example

        getline(cin,temp_str);

        cout <<"file is:"<<  temp_str;
        dir_path = temp_str;
        search_directory();

        cout << "Chosen .json file is : " << json_file_path << "\n";
    }
}

void search_directory() { //finds .jsons and puts it in a vector to select from
    std::vector<fs::path> json_files;

    for (auto& element : fs::recursive_directory_iterator(dir_path)) {
        if (element.is_regular_file() && element.path().extension() == ".json") {
            json_files.push_back(element.path());
        }

    }

    if (json_files.empty()) { // if no .json files are found this if statement will run
        cout <<
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

        make_file();
    }


    else { // will print .json files and you will choose a .json file

        cout <<
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "Choose a .json file:" << endl;
        for (int i = 0; i < json_files.size(); i++) {
            cout << std::setw(3) << i+1 << "." << "\t" << json_files[i] << endl;
        }


        cout << json_files.size()+1 << ".\tCreate new .json file" << endl;
        //cout << json_files.size()+2 << ".\tChange file path." << endl;
        cout <<
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

        int choice;
        std::cin >> choice;
        if (choice > 0 && choice <= json_files.size()) {
            json_file_path = json_files[choice-1];
        }
            /* last option will give the user the ability to make a new .json file
             int that directory.*/
        else if (choice == json_files.size()+1) {

            make_file();
        }
            //else if (choice == json_files.size()+2){
            //}
        else {
            cout << "Invalid choice." << endl;
        }
    }
}

void make_file() {
    //formats the .json into what is should look like(example in beginning)
    std::string file_name;
    cout <<
         "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
    cout << "Enter a filename to create a new JSON file: ";
    cin >> file_name;
    file_name += ".json";
    json_file_path = dir_path / file_name;

    json address_book = json::array();

    // Create a dictionary with the address book list
    json data = {
            {"address_book", address_book}
    };

    // Write the dictionary to a new .json file
    std::ofstream outfile(json_file_path);
    outfile << data.dump(2); // The 2 is optional, it adds indentation for readability
    outfile.close();

}


void write_file(){ //todo split function???
    int option;
    bool valid=false;

    while (!valid) {
        cout <<
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "You have entered write file function.\n" <<
             "Do you want to add or delete a customer?\n" <<
             "Press '1' to add a customer or '0' to delete one. \n";
        option = option_a_or_b();


        if (option == 1) {
            cout << "You have chosen to add a person\n";
            cout <<
                 "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
            char stop_input = 0;
            while (stop_input != 'y') {
                // Get input from user for new person
                // ...

                // Add new person to address book
                Person new_person;
                cin.ignore();
                new_person.get_values();
                add_person_to_address_book(new_person);


                // Ask user if they want to stop
                cin.ignore();
                cout
                        << "Type 'y' to finish adding people, or press"
                           " anything else to continue: ";

                cin >> stop_input;
                std::tolower(stop_input);
            }
            valid= true;
        }

        //delete function. also type address exactly w/o ""
        else if (option == 0) {
            read_file();
            std::ifstream file(json_file_path);
            json customer_data;
            file >> customer_data;


            std:: string address_id;
            cout <<
                 "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
            cout << "You have chosen the delete function.\n";
            cout << "Copy and paste the address you want to delete from the file.\n";
            read_file();
            cin.ignore();
            getline(cin, address_id );

            // find the element with the specified address
            for (auto element = customer_data["address_book"].begin(); element != customer_data["address_book"].end(); ++element) {
                if ((*element)["street_address"] == address_id) {
                    customer_data["address_book"].erase(element);
                    break;
                }
            }

            // write the updated JSON file
            std::ofstream outfile(json_file_path);
            outfile << customer_data.dump(4);
            valid=true;


        }
        else {
            cout << "Invalid option.";
        }
    }
    cout <<
         "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
}


void read_file (){
    cout << "You have entered the read file func.\n";
    json customer_data;
    std::ifstream file
            (json_file_path);


    file >> customer_data;
    for (auto& element : customer_data["address_book"]) {
        cout << "Name: " << element["name"] << endl;
        cout << "Last name: " << element["last_name"] << endl;
        cout << "Street Address: " << element["street_address"] << endl;
        cout << "City: " << element["city"] << std::endl;
        cout << "Phone Number: " << element["phone_number"] << endl;
        cout << "Square feet of the property: "<< element["square_feet"]<< endl;
        cout << endl;
    }

    cout <<"\n\n";
}


void main_menu (){// i guess this should be at the top
    int choice;
    bool pass_loop= true;
    cout <<"******************************************************************\n"
           "*                          Welcome                               *\n"
           "******************************************************************\n";

    cout <<"Please select an option.\n";

    cout <<"******************************************************************\n";
    cout << "[0] - Quit\n";
    cout << "[1] - Read file\n";
    cout << "[2] - Write file\n";
    cout << "[3] - Make new file\n";
    cout << "[4] - Change file\n";
    cout <<"*****************************************************************\n";
    while(pass_loop){
        cin >> choice;
        switch (choice){
            case 0:
                cout << "exiting code, goodbye.";
                std::exit(0);
            case 1:
                read_file();
                pass_loop= false;
                break;
            case 2:
                write_file();
                pass_loop= false;
                break;
            case 3:
                make_file();
                pass_loop= false;
                break;
            case 4:
                cin.ignore();
                get_json();
                pass_loop= false;
                break;
            default:
                cout << "please enter a valid option\n";
        }
    }
}

bool done_menu(){
    int choice;
    bool pass_loop= true;
    cout <<"*****************************************************************\n";
    cout <<"*                      Are you done?                            *\n";
    cout <<"*****************************************************************\n";
    cout << "[0] - Quit(exit the program\n";
    cout << "[1] - No (continue the program)\n";
    cout <<"*****************************************************************\n";
    while(pass_loop) {
        cin >> choice;
        switch (choice){
            case 0:
                cout << "exiting code, goodbye.";
                std::exit(0);
            case 1:
                return pass_loop;
            default:
                cout << "please enter a valid option\n";
        }
    }
}

int option_a_or_b(){
    int choice;
    bool done_bool= true;
    while (done_bool){
        cin >> choice;
        switch (choice){
            case 0:
                done_bool=true;
                return 0;
            case 1:
                done_bool=true;
                return 1;
            default:
                cout << "please enter a valid option\n";
        }
    }
}

void add_person_to_address_book(Person p) {// use the class i initially set up to place info in .json file
    std::ifstream file(json_file_path);
    json j;
    file >> j;
    j["address_book"].push_back(p.to_json());

    std::ofstream outfile(json_file_path);
    outfile << std::setw(4) << j << endl;
}