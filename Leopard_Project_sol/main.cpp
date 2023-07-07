#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "User.h"
#include "displays.h"
#include "sqlite3.h"

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

// callback function for SQLite
static int login(void* data, int argc, char** argv, char** azColName)
{
    // retrieve ID and password from the correct row
    int id = atoi(argv[0]);  // convert retreieved string to integer ID
    string password = argv[3];  // retrive password

    // Check the table name provided in the data pointer
    string tableName = static_cast<const char*>(data);
    if (tableName == "STUDENT") {
        // Create a Student object
        string firstName = argv[1];
        string lastName = argv[2];
        User* student = new User(firstName, lastName, id);  // created 
    }
    else if (tableName == "INSTRUCTOR") {
        // Create an Instructor object
        string firstName = argv[1];
        string lastName = argv[2];
        User* instructor = new User(firstName, lastName, id);
    }
    else if (tableName == "ADMIN") {
        // Create an Admin object
        string firstName = argv[1];
        string lastName = argv[2];
        User* admin = new User(firstName, lastName, id);
    }

    return 0;
}

int main() {
    sqlite3* db;
    int exit;  // exit sqlite value
    int choice = 0;  // general variable declaration
    int select = 0;
    int ID = 0;  // id and password varaible (password is ID)
    string username;  // email without email extention
    string first_name;
    string last_name;

    // person type specfic variables
    // create fill in

    // open the database, *match* to database close (*)
    exit = sqlite3_open("leopardDatabase.db", &db);
    if (exit != SQLITE_OK) {
        cout << "Error opening the database." << endl;
        return 1;
    }

    // ------------------------------------------ [START] LOG IN --------------------------------------------
    // Get the ID and password from the user
    cout << "Enter ID (email name): ";
    cin >> username;
    cout << "Enter Password (user ID): ";
    cin >> ID;

    // Execute the query for the STUDENT table
    string query = "SELECT ID, NAME, SURNAME FROM STUDENT WHERE EMAIL=" + username + " AND ID='" + to_string(ID) + "'";
    exit = sqlite3_exec(db, query.c_str(), login, (void*)"STUDENT", nullptr);
    if (exit != SQLITE_OK) {
        cout << "Error executing query for STUDENT table: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return exit;
    }

    // search INSTRUCTOR table if not found in STUDENT table
    if (exit == SQLITE_OK) {
        query = "SELECT ID, NAME, SURNAME FROM INSTRUCTOR WHERE EMAIL=" + username + " AND ID='" + to_string(ID) + "'";
        exit = sqlite3_exec(db, query.c_str(), login, (void*)"INSTRUCTOR", nullptr);
        if (exit != SQLITE_OK) {
            cout << "Error executing query for INSTRUCTOR table: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return exit;
        }
    }

    // search ADMIN table if not found in either
    if (exit == SQLITE_OK) {
        query = "SELECT ID, NAME, SURNAME FROM ADMIN WHERE EMAIL=" + username + " AND ID='" + to_string(ID) + "'";
        exit = sqlite3_exec(db, query.c_str(), login, (void*)"ADMIN", nullptr);
        if (exit != SQLITE_OK) {
            cout << "Error executing query for ADMIN table: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return exit;
        }
    }
    // -------------------------------------------- [END] LOG IN --------------------------------------------

    sqlite3_close(db);  // *match* to database open (*)

    return 0;
}