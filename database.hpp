#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <mysql/mysql.h>
#include <algorithm>

using namespace std;

class Database {

    public:
        Database(string address, string username, string password);
        void send_query(string query);
        void delete_value_from_database(string table_name, string column_name, string field_name);
        int get_food_aisle(string table_name, string column_name, string food_type); 

    private:
        MYSQL mysql;    
        MYSQL * connection;
        MYSQL_RES * result;
        MYSQL_ROW row;

        void get_connection(string address, string username, string password);
};