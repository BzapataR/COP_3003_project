//
// Created by Brian Zapata Resendiz on 3/7/23.
//

#include "functions.h"
/* basic .json format used
 * {
    "address_book": [
        {
            "city": "Paris",
            "last_name": "Doe",
            "name": "John",
            "phone_number": "+123456789",
            "square_feet": "500",
            "street_address": "1st Street"
        },
 */


int main() {
    get_json();
    bool user_done=true;
    while (user_done) {
        main_menu();
        user_done = done_menu();
        cout
                << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}