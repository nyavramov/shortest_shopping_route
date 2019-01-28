#include "database.hpp"

/* 
To run, link against mysql library:
    g++ `mysql_config --include` main.cpp database.cpp `mysql_config --libs` && ./a.out
*/

int main(int argc, char const *argv[]) {

    // Create our database object and connect to the database
    Database database("localhost", "root", "nevergonnagiveyouup");
    database.send_query("USE SHOPRITE");

    // Ask user for input food, then search database for that food's aisle
    printf("Please enter a food you'd like to search for: ");
    
    string food_query;
    cin >> food_query;    
    
    int aisle_number = database.get_food_aisle("food_list", "food", food_query);

    // If we've found the food, we'll print its aisle, else we'll receive -1 to indicate we didn't find anything
    if (aisle_number != -1) {
        printf("%s is in aisle %i.\n", food_query.c_str(), aisle_number);
    } else {
        printf("Couldn't find any items matching that query!\n");
    }

    return 0;

}

