#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "User.h"
#include "displays.h"
#include "sqlite3.h"

#include <iostream>
#include <string>
#include <stdio.h>


// callback1 function for SQLite: print information
static int callback1(void* data, int argc, char** argv, char** azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// Callback function for SQLite
static int callback2(void* data, int argc, char** argv, char** azColName)
{
    // Extract the ID and password from the retrieved row
    int id = argv[0];
    string password = argv[3];

    // Check the table name provided in the data pointer
    string tableName = static_cast<const char*>(data);
    if (tableName == "STUDENT") {
        // Create a Student object
        string firstName = argv[1];
        string lastName = argv[2];
        User student(firstName, lastName, id);  // created 
    }
    else if (tableName == "INSTRUCTOR") {
        // Create an Instructor object
        string firstName = argv[1];
        string lastName = argv[2];
        User instructor(firstName, lastName, id);
    }
    else if (tableName == "ADMIN") {
        // Create an Admin object
        string firstName = argv[1];
        string lastName = argv[2];
        User admin(firstName, lastName, id);
    }

    return 0;
}

int main() {

    int exit;  // exit sqlite value
    int choice = 0;  // general variable declaration
    int select = 0;
    int ID = 0;
    int password = 0;
    string username;
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
    cin >> password;

    // Execute the query for the STUDENT table
    string query = "SELECT ID, firstName, lastName, password FROM STUDENT WHERE ID=" + ID + " AND password='" + password + "'";
    exit = sqlite3_exec(db, query.c_str(), callback2, (void*)"STUDENT", nullptr);
    if (exit != SQLITE_OK) {
        cout << "Error executing query for STUDENT table: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return exit;
    }

    // search INSTRUCTOR table if not found in STUDENT table
    if (exit == SQLITE_OK) {
        query = "SELECT ID, firstName, lastName, password FROM INSTRUCTOR WHERE ID=" + ID + " AND password='" + password + "'";
        exit = sqlite3_exec(db, query.c_str(), callback2, (void*)"INSTRUCTOR", nullptr);
        if (exit != SQLITE_OK) {
            cout << "Error executing query for INSTRUCTOR table: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return exit;
        }
    }

    // search ADMIN table if not found in either
    if (exit == SQLITE_OK) {
        query = "SELECT ID, firstName, lastName, password FROM ADMIN WHERE ID=" + ID + " AND password='" + password + "'";
        exit = sqlite3_exec(db, query.c_str(), callback2, (void*)"ADMIN", nullptr);
        if (exit != SQLITE_OK) {
            cout << "Error executing query for ADMIN table: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return exit;
        }
    }
    // -------------------------------------------- [END] LOG IN --------------------------------------------


    // --------------------------------------------- ASSIGNMENT 3 ---------------------------------------------
    /*
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
        cout << "Error creating the table." << endl;  // error message
        sqlite3_free(messageError);
        return 1;
    }

    // insert values into the COURSES table
    string sql = "INSERT INTO COURSES VALUES "
        "(101, 'DIGITAL', 'BSEE', 1230, 'M', 'SUM', 'FRESH', 4), "
        "(141, 'SIGNALS', 'BSEE', 1400, 'T', 'SPR', 'SENIOR', 4), "
        "(211, 'DIGITAL', 'BSCO', 1300, 'W', 'FAL', 'FRESHMAN', 4), "
        "(231, 'MULTIVARIABLE', 'BSAS', 1530, 'R', 'FAL', 'JUNIOR', 4), "
        "(331, 'DATA', 'BSCO', 800, 'T', 'SPR', 'JUNIOR', 3), "
        "(501, 'CINEMA', 'HUSS', 1700, 'M', 'SUM', 'ALL', 3), "
        "(601, 'DESIGN', 'HUSS', 800, 'F', 'SPR', 'ALL', 3);";

    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cout << "Error inserting values into the table." << endl;
        sqlite3_free(messageError);
        return 1;
    }

    // ------------------------------------- MENU for assignment 3 ----------------------------------------
    while (choice != 7) {
        assign3();  // print menu for assignment 3 options
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
            exit = sqlite3_exec(db, searchQuery.c_str(), callback1, 0, &messageError);
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
            exit = sqlite3_exec(db, insertQuery.c_str(), callback1, 0, &messageError);
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
            exit = sqlite3_exec(db, selectQuery.c_str(), callback1, 0, &messageError);
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

        // INSERT new students
        string insertStudentQuery = "INSERT INTO STUDENT (ID, NAME, SURNAME, GRADYEAR, MAJOR, EMAIL) VALUES "
            "(20011, 'Harry', 'Potter', '2003', 'BCOS', 'potterh'), "
            "(20012, 'Luna', 'Lovegood', '2002', 'BSAS', 'lovegoodl');";
        exit = sqlite3_exec(db, insertStudentQuery.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cout << "Error inserting new students." << endl;
            sqlite3_free(messageError);
        }

        // REMOVE one instructor
        string removeInstructorQuery = "DELETE FROM INSTRUCTOR WHERE ID = 20006;";
        exit = sqlite3_exec(db, removeInstructorQuery.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cout << "Error removing instructor." << endl;
            sqlite3_free(messageError);
        }

        // UPDATE admin title
        string updateAdminQuery = "UPDATE ADMIN SET TITLE = 'Vice-President' WHERE FIRST_NAME = 'Vera' AND LAST_NAME = 'Rubin';";
        exit = sqlite3_exec(db, updateAdminQuery.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cout << "Error updating administrator title." << endl;
            sqlite3_free(messageError);
        }

        // search and display instructors for each course
        string selectCoursesQuery = "SELECT * FROM COURSES;";
        exit = sqlite3_exec(db, selectCoursesQuery.c_str(), callback1, 0, &messageError);
        if (exit != SQLITE_OK) {
            cout << "Error retrieving courses." << endl;
            sqlite3_free(messageError);
        }

    }
    */
    // DELETE TO UNCOMMENT ASSIGNMENT 3

    sqlite3_close(db);  // *match* to database open (*)

    return 0;
}