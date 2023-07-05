#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "User.h"
#include "displays.h"
#include "sqlite3.h"

#include <iostream>
#include <string>
#include <stdio.h>


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

    int exit;  // sql exit code
    int choice = 0;  // general variable declaration
    int select = 0;
    int ID = 0;
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
        exit = sqlite3_exec(db, selectCoursesQuery.c_str(), callback, 0, &messageError);
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