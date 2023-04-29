#include "functions.h"
//
// Created by Brian Zapata Resendiz on 3/7/23.
//

fs::path json_file_path;
fs:: path dir_path;


void Menus :: get_json (){
    bool done=true;
    int input;
    std:: string temp_str;
    json_file_path= "";
    // json_file_path="/Users/brianzapataresendiz/Documents/test2.json" example
    cout <<"*****************************************************************\n"
           "*                      Getting .json file...                    *\n"
           "*****************************************************************\n";
    cout<< "[0]- to add already existing file.\n";
    cout<< "[1]- to add a new file\n";
    cout<< "[2]- to find all .json files in specified directory.\n";
    cout<< "*****************************************************************\n\t";
    while (done){
        cin >> input;
        cin.ignore();
        switch(input){
            case 0:
                cout<< "Enter full file path. "
                       "(Format:/Users/brianzapataresendiz/Documents/test.json)\n\t";
                getline(cin, temp_str);
                done=false;
                json_file_path=temp_str;
                break;
            case 1:
                make_file();
                done=false;
                break;
            case 2:
                cout << "Please enter a file path to look or make a .json file.\n\t";
                // /Users/brianzapataresendiz/Documents/example
                getline(cin,temp_str);
                cout <<"filepath  is:"<<  temp_str << "\n";
                dir_path = temp_str;
                search_directory();
                done=false;
                break;
            default:
                cout<< "Invalid input please try again.\n\t";
        }
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
    else { // will print .json files and you will choose a .json file
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
        //else if (choice == json_files.size()+2){
        //}
        else {
            cout << "Invalid choice." << "\n";
        }
    }
}

void Menus :: make_file() {
    //formats the .json into what is should look like(example in beginning)
    std::string file_name;
    cout<< "*****************************************************************\n";
    cout << "Enter a filename to create a new JSON file: ";
    getline(cin,file_name);
    file_name += ".json";
    json_file_path = "../" + file_name;

    json address_book = json::array();

    // Create a dictionary with the address book list
    json data = {
            {"address_book", address_book}
    };

    // Write the dictionary to a new .json file
    std::ofstream outfile(json_file_path);
    outfile << data.dump(2); // The 2 is optional, it adds indentation for readability
    outfile.close();

    cout<< "Setting as current .json directory....\n" ;
}


void Menus :: write_file(){ //
    int option;


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
        json customer_data;
        file >> customer_data;

        while (true) {
            std::string address_id;
            cout
            << "*****************************************************************\n"
               "*                         Deleting Customer...                  *\n"
               "*****************************************************************\n";
            cout << "Please select an option\n";
            cout
            << "*****************************************************************\n";
            read_file();
            cout
                    << "Copy and paste the address you want to delete from the file.\n";
            cin.ignore();
            getline(cin, address_id);

            // find the element with the specified address
            for (auto element = customer_data["address_book"].begin();
                 element != customer_data["address_book"].end(); ++element) {
                if ((*element)["street_address"] == address_id) {
                    customer_data["address_book"].erase(element);
                    break;
                }
            }

            // write the updated JSON file
            std::ofstream outfile(json_file_path);
            outfile << customer_data.dump(4);
            file.close();
            // Ask user if they want to stop
            cout<< "*****************************************************************\n";
            cout<< "[0] - to stop deleting customers\n";
            cout<< "[1] - to  continue deleting customers\n";
            cout<< "*****************************************************************\n";
            int exit = option_a_or_b();
            if (exit == 1) {
                break;
            }

        }
    }
}


void Menus :: read_file (){
    cout << "*****************************************************************\n"
            "*                          Reading file...                      *\n"
            "*****************************************************************\n";
    json customer_data;
    std::ifstream file(json_file_path);


    file >> customer_data;
    for (auto& element : customer_data["address_book"]) {
        cout << "Name: " << element["name"] << "\n";
        cout << "Last name: " << element["last_name"] << "\n";
        cout << "Street Address: " << element["street_address"] << "\n";
        cout << "City: " << element["city"] << "\n";
        cout << "Phone Number: " << element["phone_number"] << "\n";
        cout << "Square feet of the property: "<< element["square_feet"]<< "\n";
        cout << "Jobs/Costs:" << element["jobs"] << "\n";
        cout << "Total cost with tax: " << element["Total w/tax"]<< "\n\n";

    }
    cout <<"*****************************************************************\n";
}
void Menus :: read_file( milliseconds time_delay){
    cout << "*****************************************************************\n"
            "*                          Reading file...                      *\n"
            "*****************************************************************\n";
    json customer_data;
    std::ifstream file(json_file_path);


    file >> customer_data;
    for (auto& element : customer_data["address_book"]) {
        cout << "Name: " << element["name"] << "\n";
        cout << "Last name: " << element["last_name"] << "\n";
        cout << "Street Address: " << element["street_address"] << "\n";
        cout << "City: " << element["city"] << "\n";
        cout << "Phone Number: " << element["phone_number"] << "\n";
        cout << "Square feet of the property: "<< element["square_feet"]<< "\n";
        cout << "Jobs/Costs:" << element["jobs"] << "\n";
        cout << "Total cost with tax: " << element["Total w/tax"]<< "\n\n";
        sleep_for(time_delay);
    }
    cout <<"*****************************************************************\n";
}


void  Menus :: main_menu (Files file){
    int choice;
    cout << "\n \n \n \n \n";
    bool done_loop=true;
    cout <<"*****************************************************************\n"
           "*                         Welcome                               *\n"
           "*****************************************************************\n";

    cout <<"Please select an option.\n";

    cout <<"*****************************************************************\n";
    cout << "[0] - Quit\n";
    cout << "[1] - Read file\n";
    cout << "[2] - Write file\n";
    cout << "[3] - Make new file\n";
    cout << "[4] - Change file\n";
    cout << "[5] - Add jobs\n";
    cout << "[6] - Make invoice\n";
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
                cout << "please enter a valid option done menu\n";
        }
    }
}

int Menus :: option_a_or_b(){
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


void Menus :: add_person_to_address_book(Customer p) {
    std::ifstream file(json_file_path);
    json j;
    file >> j;
    j["address_book"].push_back(p.to_json());

    std::ofstream outfile(json_file_path);
    outfile << std::setw(4) << j << "\n";
}


void Menus :: edit_jobs() {       //Not to be confused with the method this allows the user to parse through a .json and delete or add jobs while the method in the person class just adds jobs
    std::ifstream file(json_file_path);
    cout <<"*****************************************************************\n";
    cout <<"*                   Entering edit job function.                 *\n";
    cout <<"*****************************************************************\n";

    while (true) {
        read_file();
        bool valid_input=false;
        json customer_data;
        file >> customer_data;
        std:: string address_id;

        cout <<"*****************************************************************\n";
        cout << "Please select the address you want to edit (No quotation marks)\n\t";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
            if (person["street_address"] == address_id) {
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

                        // Delete the job from the person's job array
                        person["jobs"][0].erase(job_name);
                        // Update the total cost of jobs for the person
                        double total_cost = 0.0;
                        for (const auto &job: person["jobs"][0]) {
                            total_cost += job.get<double>();
                        }
                        person["Total cost of jobs"] = total_cost;
                        person["Total w/tax"]=
                                std::round(total_cost * 1.07 * 100) / 100;

                        // Write the updated JSON file
                        std::ofstream outfile(json_file_path);
                        outfile << customer_data.dump(4);

                        cout << "Job deleted successfully.\n";
                        outfile.close();
                    }
                    break;
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
                        person["jobs"][0][job_name] = new_job_cost;

                        //updates the cost parameters.
                        double total_cost = 0.0;
                        for (const auto &job: person["jobs"][0]) {
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
        if (!found_person) {
            std::cout << "Customer with street address " << address_id
                      << " not found.\n";
        }

        //looping if user wants to then change form one option to the other.
        cout << "Please select an option\n";
        cout<< "*****************************************************************\n";
        cout<<"[0] - to edit another customer\n";
        cout<<"[1] - to stop\n";
        cout << "*****************************************************************\n";
        if (option_a_or_b() == 1) {
            break;
        }
    }
}

Menus:: Menus(){
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
    cout << "Enter phone number: ";
    getline(std::cin, phone_number);
    cout << "Enter square feet: ";
    cin >> square_feet;
    get_job();

}

json Customer::to_json() {
    json jobs_array = json::array();

    for (const auto & job : jobs){
        jobs_array.push_back(job);
    }

    return
            {
                    {"name", name},
                    {"last_name", last_name},
                    {"street_address", street_address},
                    {"city", city},
                    {"phone_number", phone_number},
                    {"square_feet", square_feet},
                    {"jobs", jobs_array},
                    {"Total cost of jobs", cost_of_jobs},
                    {"Total w/tax", total_cost_with_tax}
            };
}

void Customer::get_job() {
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

    // Format the date string
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << tm.tm_mon + 1 << '/'
       << std::setfill('0') << std::setw(2) << tm.tm_mday << '/'
       << tm.tm_year + 1900;
    return ss.str();
}
Files::Files() {
    todays_date=set_todays_date();

}
void Files ::make_invoice() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    string txt_file_name="../";
    string temp_string;
    string address_id;
    std::ifstream jsonfile(json_file_path);
    json customer_data;
    jsonfile >> customer_data;

    cout << "*****************************************************************\n"
            "*                          Making invoice                       *\n"
            "*****************************************************************\n";
    print_file(json_file_path);
    cout <<"*****************************************************************\n";
    cout << "Please select the address you want to edit (No quotation marks)\n\t";
    getline(cin, address_id );
    bool valid_input=false;


    cout << address_id;
    cout <<"*****************************************************************\n";
    cout << "Please enter new name for .txt file.\n\t";
    getline(cin, temp_string);
    temp_string+= ".txt";
    txt_file_name+=temp_string;

    bool found_person = false;
    for (auto &person: customer_data["address_book"]) {
        if (person["street_address"].get<string>() == address_id) {
            found_person = true;

            //setting strings to print
            string fullname;
            string first_line_address;
            string second_line_address;
            string phone_number;

            fullname = person["name"].get<std::string>() + " " +
                       person["last_name"].get<std::string>();

            first_line_address = person["street_address"].get<string>();
            second_line_address = person["city"].get<string>() + ",FL";
            phone_number=person["phone_number"];


            std::ofstream outputFile(txt_file_name); // create file output stream

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
            //pared values.
            for (const auto &job: person["jobs"]) {
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
            break;
        }
    }
    jsonfile.close();
    if(!found_person){
        cout<< "Person with address: " << address_id << " not found.\n";
    }
}
void Files :: print_file(const string& filename){
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