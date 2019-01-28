#include "database.hpp"

// Constructor definition
Database::Database(string address, string username, string password) {
    mysql_init(&mysql);
    get_connection(address, username, password);
}

// Accepts credentials and attempts to connect to database
void Database::get_connection(string address, string username, string password){
    connection = mysql_real_connect(&mysql,
                                    address.c_str(),
                                    username.c_str(),
                                    password.c_str(),         
                                    "mysql",
                                    0, 0, 0);

    // Check that we're connect to the database
    if(!connection) {
        printf("Couldn't connect to MySQL database server!\n");
        printf("Error: %s\n", mysql_error(&mysql));
    } else {
        printf("Connected successfully.\n");
    }
}

// Allows us to send a generic query to the database, e.g. USE SHOPRITE, to select the specific database
void Database::send_query(string query) {

    // Send the query and check for error
    if(mysql_query(connection, query.c_str())) {
        printf("Error:  %s\n", mysql_error(connection));
    }
    // Store the result of the query
    result = mysql_store_result(connection);
}

// Search our database for a specific food
int Database::get_food_aisle(string table_name, string column_name, string food_type) {

    // Compose the query string
    string query = "SELECT * from " + table_name + " where " + column_name + "=\"" + food_type + "\"";

    // Free previous query result to prevent out of sync MySQL error
    mysql_free_result(result);

    // Search for the food queried by user
    send_query(query);
    
    // Extract aisle number if row exists. Otherwise, return -1.
    if ((row = mysql_fetch_row(result))) {
        int aisle_number = stoi(row[2]);
        return aisle_number;
    } else {
        return -1;
    } 
}

//Delete a value from the database using provided table, column, and field
void Database::delete_value_from_database(string table_name, string column_name, string field_name){
    // Compose the query string 
    string query = "DELETE from " + table_name + " where " + column_name + "=\"" + field_name + "\"";

    // Free previous query result to prevent out of sync MySQL error
    mysql_free_result(result);

    // Delete the specified row
    send_query(query);
}