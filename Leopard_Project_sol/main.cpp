#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "User.h"
#include "sqlite3.h"

#include <iostream>
#include <string>
#include <stdio.h>

using std::cin;
using std::cout;
using std::string;
using std::endl;

// callback function for SQLite
static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3* db;
    char* messageError;

    int exit;  //  sql exit code
    int choice = 0;  // general variable declaration
    int select = 0;
    int ID = 0;
    string first_name;
    string last_name;


    // person type specfic variables
    // create fill in

    // open the database
    exit = sqlite3_open("leopardDatabase.db", &db);
    if (exit != SQLITE_OK) {
        cout << "Error opening the database." << endl;
        return 1;
    }

    // create the COURSES table
    string table = "CREATE TABLE COURSES("
        "CRN INTEGER PRIMARY KEY, "
        "TITLE TEXT NOT NULL, "
        "DEPARTMENT TEXT NOT NULL, "
        "TIME INTEGER NOT NULL, "
        "DOTW TEXT NOT NULL, "
        "SEMESTER TEXT NOT NULL, "
        "YEAR TEXT NOT NULL, "
        "CREDITS INTEGER NOT NULL);";

    exit = sqlite3_exec(db, table.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cout << "Error creating the table." << endl;
        sqlite3_free(messageError);
        return 1;
    }

    // insert values into the COURSES table
    string sql = "INSERT INTO COURSES VALUES "
        "(101, 'PROGRAMMING', 'ELECTRICAL', 1230, 'MONDAY', 'SUMMER', 'JUNIOR', 3), "
        "(102, 'SIGNALS', 'ELECTRICAL', 200, 'TUESDAY', 'SPRING', 'SENIOR', 4), "
        "(103, 'NETWORKS', 'ELECTRICAL', 100, 'WEDNESDAY', 'FALL', 'FRESHMAN', 4), "
        "(201, 'MULTIVARIABLE', 'MATH', 330, 'THURSDAY', 'FALL', 'SENIOR', 4), "
        "(301, 'ETHICS', 'HSS', 800, 'FRIDAY', 'SPRING', 'FRESHMAN', 3), "
        "(202, 'ECONOMY', 'MATH', 500, 'MONDAY', 'SUMMER', 'JUNIOR', 3), "
        "(401, 'ENGLISH', 'ENGLISH', 330, 'TUESDAY', 'FALL', 'SOPHOMORE', 3);";

    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cout << "Error inserting values into the table." << endl;
        sqlite3_free(messageError);
        return 1;
    }

    // MENU
    while (choice != 7) {
        cout << "========== MENU ==========" << endl;
        cout << "1. Search for records" << endl;
        cout << "2. Insert new records" << endl;
        cout << "3. Print all records from a table" << endl;
        cout << "4. Create a table" << endl;
        cout << "5. Update existing records" << endl;
        cout << "6. Remove records from the database" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {  //  search records based on certain parameter
            cout << "Enter the table name (ADMIN, INSTRUCTOR, STUDENT, COURSES): ";
            string tableName;
            cin >> tableName;
            cout << "Enter the search parameter: ";
            string parameter;
            cin >> parameter;

            //  SQL query
            string searchQuery = "SELECT * FROM " + tableName + " WHERE PARAMETER='" + parameter + "';";
            //  execute search
            exit = sqlite3_exec(db, searchQuery.c_str(), callback, 0, &messageError);
            if (exit != SQLITE_OK) {
                cout << "Error searching for records." << endl;
                sqlite3_free(messageError);
            }

            break;
        }
        case 2: {  //  insert a new record
            cout << "Enter the table name (ADMIN, INSTRUCTOR, STUDENT, COURSES): ";
            string tableName;
            cin >> tableName;
            //  cont. with ability to insert a new record given parameters
            //  cont.

            //  SQL query to insert the record
            string insertQuery = "INSERT INTO " + tableName + " VALUES (...);";
            //  execute insert
            exit = sqlite3_exec(db, insertQuery.c_str(), callback, 0, &messageError);
            if (exit != SQLITE_OK) {
                cout << "Error inserting new record." << endl;
                sqlite3_free(messageError);
            }

            break;
        }
        case 3: {  //  print all records from a table
            cout << "Enter the table name (ADMIN, INSTRUCTOR, STUDENT, COURSES): ";
            string tableName;
            cin >> tableName;

            //  SQL query to retrieve all table records
            string selectQuery = "SELECT * FROM " + tableName + ";";
            //  Execute the select query
            exit = sqlite3_exec(db, selectQuery.c_str(), callback, 0, &messageError);
            if (exit != SQLITE_OK) {
                cout << "Error retrieving records from the table." << endl;
                sqlite3_free(messageError);
            }

            break;
        }
        case 4: {  //  create a table
            //  cont. with req. fields to create a new table given desired sections
            //  cont.

            //  construct the SQL query to create the table
            string createTableQuery = "CREATE TABLE ...";
            //  execute create table query
            exit = sqlite3_exec(db, createTableQuery.c_str(), NULL, 0, &messageError);
            if (exit != SQLITE_OK) {
                cout << "Error creating the table." << endl;
                sqlite3_free(messageError);
            }

            break;
        }
        case 5: {  //  update existing records
            cout << "Enter the table name (ADMIN, INSTRUCTOR, STUDENT, COURSES): ";
            string tableName;
            cin >> tableName;
            //  cont. with req. fields to update the records
            //  cont.

            //  SQL query to update records
            string updateQuery = "UPDATE " + tableName + " SET ... WHERE ...;";
            //  execute the update query
            exit = sqlite3_exec(db, updateQuery.c_str(), NULL, 0, &messageError);
            if (exit != SQLITE_OK) {
                cout << "Error updating records." << endl;
                sqlite3_free(messageError);
            }

            break;
        }
        case 6: {  //  remove records from the database
            cout << "Enter the table name (ADMIN, INSTRUCTOR, STUDENT, COURSES): ";
            string tableName;
            cin >> tableName;
            //  cont. with req. fields to remove the records
            //  ...

            //  SQL query to remove the records
            string removeQuery = "DELETE FROM " + tableName + " WHERE ...;";
            //  execute remove query
            exit = sqlite3_exec(db, removeQuery.c_str(), NULL, 0, &messageError);
            if (exit != SQLITE_OK) {
                cout << "Error removing records." << endl;
                sqlite3_free(messageError);
            }

            break;
        }
        case 7: {
            cout << "Exiting..." << endl;
            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }

    sqlite3_close(db);

    return 0;
}