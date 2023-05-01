#include "functions.h"
//
// Created by Brian Zapata Resendiz on 3/7/23.
/* As seen through most of the code when parsing through json files
 * It will use the street address as a unique identifier*/

fs::path json_file_path;
fs:: path dir_path;


void Menus :: get_json (){//to set the current .json file that the rest of the code
    // relies on.
    bool done=true;
    int input;
    std:: string temp_str;
    json_file_path= "";
    // json_file_path="/Users/brianzapataresendiz/Documents/test2.json" example
    while (done){
        cout <<"*****************************************************************\n"
               "*                      Getting .json file...                    *\n"
               "*****************************************************************\n";
        cout<< "[0]- to add already existing file.\n";
        cout<< "[1]- to add a new file\n";
        cout<< "[2]- to find all .json files in specified directory.\n";
        cout<< "*****************************************************************\n\t";
        cin >> input;
        cin.ignore();
        switch(input){
            case 0:
                cout<< "Enter full file path. "
                       "(Format:/Users/brianzapataresendiz/Documents/test.json)\n\t";
                getline(cin, temp_str);
                json_file_path=temp_str;
                done=false;
                break;
            case 1:
                make_file();
                done=false;
                break;
            case 2:
                cout << "Please enter a file path to look or make a .json file"
                "example (Users/User/Documents/)\n\t";
                getline(cin,temp_str);
                cout <<"filepath  is:"<<  temp_str << "\n";
                dir_path = temp_str;
                search_directory();
                done=false;
                break;
            default:
                cout<< "Invalid input please try again.\n\t";
        }
        std:: ifstream test (json_file_path);
        if(!test.is_open()){
            cout<<"Cannot open file, try again.\n";
            done= true;
        }
        test.close();
    }
    cout << "json file is: " << json_file_path << "\n";
    cout<< "*****************************************************************\n";
    milliseconds delay_time(1000);
    sleep_for(delay_time);

}

void Menus :: search_directory() {
    std::vector<fs::path> json_files;
    for (auto& element : fs::recursive_directory_iterator(dir_path)) {
        if (element.is_regular_file() && element.path().extension() == ".json") {
            json_files.push_back(element.path());
        }
    }
    if (json_files.empty()) { // if no .json files are found this if statement will run
        cout<< "*****************************************************************\n";
        cout << "No .json files found in directory. Making new file...\n";
        make_file();
    }
    else { // will print .json files, and you will choose a .json file
        cout<< "*****************************************************************\n";
        cout << "Choose a .json file:" << "\n";
        for (int i = 0; i < json_files.size(); i++) {
            cout << std::setw(3) << i+1 << "." << "\t" << json_files[i] << "\n";
        }
        cout << json_files.size()+1 << ".\tCreate new .json file" << "\n";
        cout<< "*****************************************************************\n";
        int choice;
        cin >> choice;
        if (choice > 0 && choice <= json_files.size()) {
            json_file_path = json_files[choice-1];
        }
            /* last option will give the user the ability to make a new .json file
             int that directory.*/
        else if (choice == json_files.size()+1) {

            make_file();
        }
        else {
            cout << "Invalid choice." << "\n";
        }
    }
}

void Menus :: make_file() {
    //formats the .json into what is should look like(example in beginning of main.cpp)
    cout <<"*****************************************************************\n"
           "*                      Making .json file...                     *\n"
           "*****************************************************************\n";
    std::string file_name;
    cout << "Enter a filename to create a new JSON file: \n";
    cout<< "*****************************************************************\n\t";
    getline(cin,file_name);
    file_name += ".json";
    json_file_path = "../" + file_name;

    std::ofstream outfile(json_file_path);
    while(!outfile.is_open()){
        cout<< "Cannot open file, try again.\n";
        cout <<"*****************************************************************\n";
        cout << "Please enter new name for .txt file.\n\t";
        file_name="";
        getline(cin, file_name);
        file_name+= ".json";
        json_file_path= "../" + file_name;
        outfile.open(json_file_path);
    }

    json address_book = json::array();

    // Create a dictionary with the address book list
    json data = {
            {"address_book", address_book}
    };

    // Write the dictionary to a new .json file

    outfile << data.dump(2); // The 2 is optional, it adds indentation for readability
    outfile.close();

    milliseconds time_delay(1000);
    cout <<"*****************************************************************\n";
    cout<< "Setting as current .json directory....\n" ;
    cout <<"*****************************************************************\n";

    sleep_for(time_delay);
}


void Menus :: write_file(){ //
    int option;

// add option to add or delete a customer
    cout << "*****************************************************************\n"
            "*                     Writing file function                     *\n"
            "*****************************************************************\n";
    cout << "Please select an option\n";
    cout << "*****************************************************************\n";
    cout<<"[0] - to delete a customer\n";
    cout<<"[1] - to add a customer\n";
    cout << "*****************************************************************\n";
    option = option_a_or_b();


    if (option == 1) {
        cout << "*****************************************************************\n"
                "*                         Adding a Customer...                  *\n"
                "*****************************************************************\n";
        while (true) {
            // Get input from user for new person
            // ...

            // Add new person to address book
            Customer new_person;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            new_person.get_values();
            add_person_to_address_book(new_person);


            // Ask user if they want to stop
            cout<<"*****************************************************************\n";
            cout<<"[0] - to stop adding customers\n";
            cout<<"[1] - to  continue adding customers\n";
            cout<<"*****************************************************************\n";
            int exit = option_a_or_b();
            if (exit==0){
                break;
            }
        }
    }
    else {
        std::ifstream file(json_file_path);
        ordered_json customer_data;
        file >> customer_data;
        file.close();

        while (true) { // deletes EVERYTHING about customer
            std::string address_id;
            cout
            << "*****************************************************************\n"
               "*                         Deleting Customer...                  *\n"
               "*****************************************************************\n";
            read_file();

            cout
            << "Copy and paste the address you want to delete from the file.\n";
            cout
                    << "*****************************************************************\n";
            cin.ignore();
            getline(cin, address_id);
            bool valid_input =false;
            while (!valid_input) {
                if (address_id.find('\"') == std::string::npos) {
                    valid_input = true;
                } else {
                    cout << "NO DOUBLE QUOTES, try again.\n\t";
                    getline(cin, address_id);
                }
            }
            bool found = false;
            auto& address_book = customer_data["address_book"];
            // Looking for person with address id
            for (auto it = address_book.begin(); it != address_book.end(); ++it) {
                if ((*it)["Street address"] == address_id) {
                    found = true;
                    address_book.erase(it);
                    cout << "Deletion complete" << endl;
                    // write the updated JSON file
                    std::ofstream outfile(json_file_path);
                    outfile << customer_data.dump(4);
                    file.close();
                    //(Only one person should have the same street address)
                    //reducing redundancy
                    break;
                }
            }

            if (!found) {
                cout << "Person with street address: " << address_id << " not found." << endl;
            }



            // Ask user if they want to stop
            cout<< "*****************************************************************\n";
            cout<< "[0] - to stop deleting customers\n";
            cout<< "[1] - to  continue deleting customers\n";
            cout<< "*****************************************************************\n";
            int exit = option_a_or_b();
            if (exit == 0) {
                break;
            }

        }
    }
}


void Menus :: read_file (){// prints file instantly
    cout << "*****************************************************************\n"
            "*                          Reading file...                      *\n"
            "*****************************************************************\n";
    json customer_data;
    std::ifstream file(json_file_path);


    file >> customer_data;
    for (auto& element : customer_data["address_book"]) {
        cout << "Name: " << element["Name"] << "\n";
        cout << "Last name: " << element["Last name"] << "\n";
        cout << "Street Address: " << element["Street address"] << "\n";
        cout << "City: " << element["City"] << "\n";
        cout << "Zip code: " << element["Zip code"] << "\n";
        cout << "Phone Number: " << element["Phone number"] << "\n";
        cout << "Square feet of the property: "<< element["Square-feet"]<< "\n";
        cout << "Jobs/Costs:" << element["Jobs"] << "\n";
        cout << "Total cost with tax: " << element["Total w/tax"]<< "\n\n";

    }
    cout <<"*****************************************************************\n";
}
void Menus :: read_file( milliseconds time_delay){// prints with time delay
    //between entry so it doesn't overwhelm reader all at once
    cout << "*****************************************************************\n"
            "*                          Reading file...                      *\n"
            "*****************************************************************\n";
    json customer_data;
    std::ifstream file(json_file_path);


    file >> customer_data;
    for (auto& element : customer_data["address_book"]) {
        cout << "Name: " << element["Name"] << "\n";
        cout << "Last name: " << element["Last name"] << "\n";
        cout << "Street Address: " << element["Street address"] << "\n";
        cout << "City: " << element["City"] << "\n";
        cout << "Zip code: " << element["Zip code"] << "\n";
        cout << "Phone Number: " << element["Phone number"] << "\n";
        cout << "Square feet of the property: "<< element["Square-feet"]<< "\n";
        cout << "Jobs/Costs:" << element["Jobs"] << "\n";
        cout << "Total cost with tax: " << element["Total w/tax"]<< "\n\n";
        sleep_for(time_delay);
    }
    cout <<"*****************************************************************\n";
}


void  Menus :: main_menu (Files file){// main branch of program
    int choice;
    cout << "\n \n \n \n \n";
    bool done_loop=true;
    cout <<"*****************************************************************\n"
           "*                         Welcome                               *\n"
           "*****************************************************************\n";

    cout <<"Please select an option.\n";

    cout <<"*****************************************************************\n";
    cout << "[0] - Quit\n";//quits program early
    cout << "[1] - Read file\n";//prints json file
    cout << "[2] - Write file\n";//adds or deletes customers
    cout << "[3] - Make new file\n";// Makes new file and sets it as current .json
    cout << "[4] - Change file\n";// change current .json file
    cout << "[5] - Edit jobs\n";//adds or deletes jobs on one customer
    cout << "[6] - Make invoice\n";// makes a .txt file of invoice
    cout <<"*****************************************************************\n\t";

    while(done_loop){
        cin >> choice;
        cout<<"*****************************************************************"
              "\n\t";
        switch (choice){
            case 0:
                cout << "Exiting code, goodbye.";
                std::exit(0);
            case 1:
                cout << "\n \n \n \n \n";
                read_file(milliseconds (500));
                done_loop=false;
                cout << "\n \n \n \n \n";
                break;
            case 2:
                cout << "\n \n \n \n \n";
                write_file();
                done_loop=false;
                cout << "\n \n \n \n \n";
                break;
            case 3:
                cout << "\n \n \n \n \n";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                make_file();
                done_loop=false;
                cout << "\n \n \n \n \n";
                break;
            case 4:
                cout << "\n \n \n \n \n";
                cin.ignore();
                get_json();
                done_loop=false;
                cout << "\n \n \n \n \n";
                break;
            case 5:
                cout << "\n \n \n \n \n";
                edit_jobs();
                done_loop=false;
                cout << "\n \n \n \n \n";
                break;
            case 6:
                cout<< "\n \n \n \n \n";
                file.make_invoice();
                done_loop=false;
                cout << "\n \n \n \n \n";
                break;
            default:
                cout << "please enter a valid option menu\n";
        }
    }
}

bool Menus ::  done_menu(){
    std::cout.flush();
    int exit_choice;
    bool pass_loop= true;
    cout <<"*****************************************************************\n";
    cout <<"*                      Are you done?                            *\n";
    cout <<"*****************************************************************\n";
    cout << "[0] - Quit(exit the program\n";
    cout << "[1] - No (continue the program)\n";
    cout <<"*****************************************************************\n";
    while(true) {
        cin >> exit_choice;
        switch (exit_choice){
            case 0:
                pass_loop=false;
                return pass_loop;
            case 1:
                return pass_loop;
            default:
                cout << exit_choice;
                cout << "Please enter a valid option done menu\n";
        }
    }
}

int Menus :: option_a_or_b(){// just for some simplification
    int choice;
    while (true){
        cin >> choice;
        switch (choice){
            case 0:
                return 0;
            case 1:
                return 1;
            default:
                cout << "Please enter a valid option option a or b\n";
        }
    }
}


void Menus :: add_person_to_address_book(Customer p) {//adds json object to file
    std::ifstream file(json_file_path);
    ordered_json j;
    file >> j;
    j["address_book"].push_back(p.to_json());

    std::ofstream outfile(json_file_path);
    outfile << std::setw(4) << j << "\n";
}


void Menus :: edit_jobs() {//Not to be confused with the method this allows the
    // user to parse through a .json and delete or add jobs while the method in
    // the person class just adds jobs
    cout <<"*****************************************************************\n";
    cout <<"*                   Entering edit job function.                 *\n";
    cout <<"*****************************************************************\n";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::ifstream file(json_file_path);
        read_file();
        bool valid_input=false;
        ordered_json customer_data;
        file >> customer_data;
        std:: string address_id;

        cout << "Please select the address you want to edit (No quotation marks)\n"
            "*****************************************************************\n\t";
        getline(cin, address_id );

        while (!valid_input) {
            if (address_id.find('\"') == std::string::npos) {
                valid_input = true;
            } else {
                cout << "NO DOUBLE QUOTES, try again.\n\t";
                getline(cin, address_id);
            }
        }


        bool found_person = false;
        for (auto& person : customer_data["address_book"]) {
            if (person["Street address"] == address_id) {
                found_person = true;


                cout  << "Please select an option\n";
                cout<< "*******************************************************"
                       "**********\n";
                cout <<"[0]- for deleting a customer's job\n";
                cout <<"[1]- for adding or editing a customer's jobs\n";
                cout<< "*******************************************************"
                       "**********\n\t";
                // Ask the user for the job to edit and the new cost of the job
                int edit_opt=option_a_or_b();
                cin.ignore(std::numeric_limits<std::streamsize>::max(),
                           '\n');
                cout<<"************************************************"
                      "*****************\n";


                if (edit_opt == 0) {
                    string job_name;

                    while (true) {
                        cout << "Type the job you want to delete or type "
                                "Done to quit.\n\t";
                        getline(cin, job_name);
                        job_name[0]=static_cast<char>(toupper(job_name[0]));
                        if (job_name=="Done"){
                            break;
                        }
                        bool found_job=false;
                        for(auto &jobs: person ["Jobs"][0].items()) {
                            if (jobs.key() == job_name) {
                                found_job = true;

                                // Delete the job from the person's job array
                                person["Jobs"][0].erase(job_name);
                                // Update the total cost of jobs for the person
                                double total_cost = 0.0;
                                for (const auto &job: person["Jobs"][0]) {
                                    total_cost += job.get<double>();
                                }
                                person["Total cost of jobs"] = total_cost;
                                person["Total w/tax"] =
                                        std::round(total_cost * 1.07 * 100) /
                                        100;

                                // Write the updated JSON file
                                std::ofstream outfile(json_file_path);
                                outfile << customer_data.dump(4);

                                cout << "Job deleted successfully.\n";
                                outfile.close();
                                break;
                            }
                        }

                        if(!found_job){
                            cout << "Job: "<< job_name << "not found try again."
                                  "\n";
                            cout<<"******************************************"
                                  "***********************\n";
                        }
                    }
                }


                else {
                    while (true) {
                        string job_name;
                        double new_job_cost;
                        cout << "Enter the name of the job you want to edit or"
                                " type 'Done to quit. \n\t";
                        getline(cin, job_name);
                        job_name[0]=static_cast<char>(toupper(job_name[0]));
                        if (job_name == "Done") {
                            break;
                        }
                        cout << "Enter the new cost of the job:\n\t";
                        cin >> new_job_cost;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                   '\n');
                        new_job_cost = std::round(new_job_cost * 100.0) / 100.0;


                        // Update the job cost for the specified job
                        person["Jobs"][0][job_name] = new_job_cost;

                        //updates the total cost parameters.
                        double total_cost = 0.0;
                        for (const auto &job: person["Jobs"][0]) {
                            total_cost += job.get<double>();
                        }
                        person["Total cost of jobs"] = total_cost;
                        person["Total w/tax"] =
                                std::round(total_cost * 1.07 * 100) / 100;

                        // Write the updated JSON object back to the file
                        std::ofstream outfile(json_file_path);
                        outfile << customer_data.dump(4);

                        cout << "Job array for person with street address "
                             << address_id << " updated successfully.\n";
                        cout
                                << "****************************************************"
                                   "*************\n";
                        outfile.close();
                    }
                    break;
                }

            }

        }
        if (!found_person) {//error case
            std::cout << "Customer with street address " << address_id
                      << " not found.\n";
        }

        //looping if user wants to then change form one option to the other.
        cout << "Please select an option\n";
        cout<< "*****************************************************************\n";
        cout<<"[0] - to stop\n";
        cout<<"[1] - to edit another customer\n";
        cout << "*****************************************************************\n";
        if (option_a_or_b() == 0) {
            break;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

Menus:: Menus(){//constructor that is the basis of whole code(order of logic
    // of whole code)
    get_json();
    bool done=true;
    while(done) {
        Files file;
        main_menu(file);
        done=done_menu();
    }
}



//Customer Methods
void Customer::get_values() {
    cout << "Enter name: ";
    getline(std::cin, name);
    cout << "Enter last name: ";
    getline(std::cin, last_name);
    cout << "Enter street address: ";
    getline(std::cin, street_address);
    cout << "Enter city: ";
    getline(std::cin, city);
    cout << "Enter zip code: ";
    getline(cin, zip_code);
    cout << "Enter phone number: ";
    getline(std::cin, phone_number);
    cout << "Enter square-feet: ";
    cin >> square_feet;
    get_job();

}

ordered_json Customer::to_json() {
    //sets up array object for jobs
    json jobs_array = json::array();

    for (const auto & job : jobs){
        jobs_array.push_back(job);
    }
    //adds the map to the json object array

    return
            {
                    {"Name", name},
                    {"Last name", last_name},
                    {"Street address", street_address},
                    {"City", city},
                    {"Phone number", phone_number},
                    {"Zip code", zip_code},
                    {"Square-feet", square_feet},
                    {"Jobs", jobs_array},
                    {"Total cost of jobs", cost_of_jobs},
                    {"Total w/tax", total_cost_with_tax}
            };
}

void Customer::get_job() {// again not be confused with the Menus version
    // this is used while getting all the data for one person during
    // the menu option of "add customer" basically the same but is for the current
    // customer being added.
    std::map <string, double> temp_job_map;
    cost_of_jobs=0;
    total_cost_with_tax=0;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {


        string job_name;
        double job_price;
        cout << "Please enter job name, or 'Done' to quit.\n\t";
        getline(cin, job_name);
        job_name[0]=static_cast<char>(toupper(job_name[0]));
        if (job_name == "Done") {
            break;
        }
        cout << "Please enter the price of the job.\n\t";
        cin >> job_price;
        job_price=std::round(job_price * 100.0) / 100.0;
        cost_of_jobs+= job_price;
        temp_job_map.insert({job_name,job_price});
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
//math part and rounding to dollars
    cost_of_jobs=std::round(cost_of_jobs * 100.0) / 100.0;
    jobs.push_back(temp_job_map);
    total_cost_with_tax= cost_of_jobs * tax_rate;
    total_cost_with_tax= std::round(total_cost_with_tax * 100.0) / 100.0;


    cout << "The customer total will be: " << cost_of_jobs
         << " And the total plus tax: " << total_cost_with_tax<< "\n";

}
string  Files :: set_todays_date(){
    // Get the current time
    auto now = std::chrono::system_clock::now();

    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    // Format the date string mm/dd/yyyy
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << tm.tm_mon + 1 << '/'
       << std::setfill('0') << std::setw(2) << tm.tm_mday << '/'
       << tm.tm_year + 1900;
    return ss.str();
}
Files::Files() {
    todays_date=set_todays_date();

}
void Files ::make_invoice() {// the making of a .txt invoice
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    string txt_file_name="../";
    string temp_string;
    string address_id;
    std::ifstream jsonfile(json_file_path);
    json customer_data;
    jsonfile >> customer_data;

    print_file(json_file_path);
    cout << "*****************************************************************\n"
            "*                          Making invoice                       *\n"
            "*****************************************************************\n";
    cout << "Please select the address you want to edit (No quotation marks)\n";
    cout <<"*****************************************************************\n\t";
    getline(cin, address_id );
    bool valid_input=false;
    while (!valid_input) {
        if (address_id.find('\"') == std::string::npos) {
            valid_input = true;
        } else {
            cout << "NO DOUBLE QUOTES, try again.\n\t";
            getline(cin, address_id);
        }
    }


    cout <<"*****************************************************************\n";
    cout << "Please enter new name for .txt file.\n\t";// naming of txt file
    getline(cin, temp_string);
    temp_string+= ".txt";
    txt_file_name+=temp_string;
    std::ofstream outputFile(txt_file_name); // create file output stream
    while(!outputFile.is_open()){ // fail case
        cout<< "Cannot open file, try again.";
        cout <<"*****************************************************************\n";
        cout << "Please enter new name for .txt file.\n\t";
        temp_string="";
        getline(cin, temp_string);
        temp_string+= ".txt";
        txt_file_name+=temp_string;
        outputFile.open(txt_file_name);
    }
    //looking through json file
    bool found_person = false;
    for (auto &person: customer_data["address_book"]) {
        if (person["Street address"].get<string>() == address_id) {
            found_person = true;

            //setting strings to print
            string fullname;
            string first_line_address;
            string second_line_address;
            string phone_number;

            fullname = person["Name"].get<std::string>() + " " +
                       person["Last name"].get<std::string>();

            first_line_address = person["Street address"].get<string>();
            second_line_address = person["City"].get<string>() + ",FL";
            phone_number=person["Phone number"];



            // Output header
            outputFile << std::left<< std::setw(20) << company_name
                       << std::setw(20) << "\t" << fullname << "\n"
                       << std::setw(20) << company_email
                       << std::setw(20) << "\t" << phone_number << "\n"
                       << std::setw(20) << company_address
                       << std::setw(20) << "\t" << first_line_address << "\n"
                       << std::setw(20) << company_second_line_address
                       << std::setw(20) << "\t" << second_line_address
                       << "\n\n";

            outputFile << std::setw(20) << "Job Name"
                       << std::setw(20) << "Price"
                       << std:: setw(20) << todays_date << "\n";
            outputFile << string(60, '-') << "\n";

            // Output job information, looking through the jobs and getting
            //paired values.
            for (const auto &job: person["Jobs"]) {
                for (auto i = job.begin(); i != job.end(); ++i) {
                    outputFile << std::setw(20) << i.key()
                               << std::setw(20) << i.value()
                               << "\n";
                }
            }
            // Output footer
            outputFile << std::string(60, '-') << "\n"
                       << std::setw(20)<< " " << "Total Balance \n"
                       << std::setw(20)<< " " << person["Total w/tax"];

            outputFile.close(); // close file output stream
            cout << "*****************************************************************\n"
                    "*                          Invoice made!                        *\n"
                    "*****************************************************************\n";
            milliseconds time_delay(1000);
            sleep_for(time_delay);
            break;
        }
    }
    jsonfile.close();
    if(!found_person){
        cout<< "Person with address: " << address_id << " not found.\n";
    }
}
void Files :: print_file(const string& filename){//read file is similar but this
    // is more for a broad use simply reading all types of files line by line
    // useful more future purposes.
    vector<string> lines;
    std:: ifstream r_file;
    string line;

    r_file.open(filename);
    if (r_file.is_open()) {
        while (getline(r_file, line)) {
            cout << line << '\n';
            lines.push_back(line);
        }
        r_file.close();
    }
    else {
        cout << "unable to open file";
    }
}
