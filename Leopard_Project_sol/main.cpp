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
static int login(void* data, int argc, char** argv, char** azColName) {
    string userType = static_cast<const char*>(data);
    User* user = nullptr;

    // Assuming the query returns only one row
    if (argc == 3) {
        string id = argv[0] ? argv[0] : "";
        string name = argv[1] ? argv[1] : "";
        string surname = argv[2] ? argv[2] : "";

        if (userType == "STUDENT") {
            Student* studentUser = new Student();
            studentUser->first_name = name;
            studentUser->last_name = surname;
            studentUser->ID = stoi(id);
            user = studentUser;
        }
        else if (userType == "INSTRUCTOR") {
            Instructor* instructorUser = new Instructor();
            instructorUser->first_name = name;
            instructorUser->last_name = surname;
            instructorUser->ID = stoi(id);
            user = instructorUser;
        }
        else if (userType == "ADMIN") {
            Admin* adminUser = new Admin();
            adminUser->first_name = name;
            adminUser->last_name = surname;
            adminUser->ID = stoi(id);
            user = adminUser;
        }
        if (user) {  // confirm user is created by printing their information
            cout << "Logged in as: " << userType << endl;
            cout << "ID: " << user->ID << endl;
            cout << "First Name: " << user->first_name << endl;
            cout << "Last Name: " << user->last_name << endl;
        }
    }

    return 0;
}

int performLogin(sqlite3* db, const string& username, int ID) {
    int exit;
    int key = 0;  // key provided after ID retrieved

    // Search query for the STUDENT table to retrieve student's ID, name, and last name
    string query = "SELECT ID, NAME, SURNAME FROM STUDENT WHERE EMAIL='" + username + "' AND ID='" + to_string(ID) + "'";
    exit = sqlite3_exec(db, query.c_str(), login, (void*)"STUDENT", nullptr);
    if (exit != SQLITE_OK) {
        cout << "Error executing query for STUDENT table: " << sqlite3_errmsg(db) << endl;
        return exit;
    }
    else {
        key = 2;  // Student authorization
    }

    // Search INSTRUCTOR table for information if not found in STUDENT table
    if (exit == SQLITE_OK) {
        query = "SELECT ID, NAME, SURNAME FROM INSTRUCTOR WHERE EMAIL='" + username + "' AND ID='" + to_string(ID) + "'";
        exit = sqlite3_exec(db, query.c_str(), login, (void*)"INSTRUCTOR", nullptr);
        if (exit != SQLITE_OK) {
            cout << "Error executing query for INSTRUCTOR table: " << sqlite3_errmsg(db) << endl;
            return exit;
        }
        else {
            key = 3;  // Instructor authorization
        }
    }

    // Search ADMIN table if not found in either
    if (exit == SQLITE_OK) {
        query = "SELECT ID, NAME, SURNAME FROM ADMIN WHERE EMAIL='" + username + "' AND ID='" + to_string(ID) + "'";
        exit = sqlite3_exec(db, query.c_str(), login, (void*)"ADMIN", nullptr);
        if (exit != SQLITE_OK) {
            cout << "Error executing query for ADMIN table: " << sqlite3_errmsg(db) << endl;
            return exit;
        }
        else {
            key = 4;  // Admin authorization
        }
    }

    return key;
}

// ------------------------------------------------------------------------------------------
// ------------------------------------------------------------------- MAIN CODE ------------
// ------------------------------------------------------------------------------------------

int main() {

    sqlite3* db;
    int exit;  // exit sqlite value
    int exitMenu = 0;
    int ID = 0;  // id and password varaible (password is ID)
    string username;  // email without email extention
    string first_name;
    string last_name;
    int CRN;
    int option = 0;  // menu option selection variable
    int loop = 0;
    int choice;
    string col;
    string parameter;

    int key = 0;  // key provided after ID retrieved 

    cout << "Connecting to Database . . ." << endl;
    // open the database, *match* to database close (*)
    exit = sqlite3_open("leopardDatabase.db", &db);
    if (exit != SQLITE_OK) {
        cout << "ERROR Connecting to the Database.\n\nGoodbye.\n" << endl;
        return 1;
    }
    else {
        cout << "Database Connected.\n\n";  // confirm database connection
    }

    // -------------------------------------------------------------- LOG IN
    // get ID and password from user
    cout << "Enter ID (email name): ";
    cin >> username;
    cout << "Enter Password (user ID): ";
    cin >> ID;
    key = performLogin(db, username, ID);  // perform login process and create user

    Student studentUser;
    int S_userID = studentUser.returnID();  // id variable
    string S_firstName = studentUser.returnFN();  // first name variable
    string S_lastName = studentUser.returnLN();  // last name

    Instructor instructorUser;
    int I_userID = instructorUser.returnID();  // id variable
    string I_firstName = instructorUser.returnFN();  // first name variable
    string I_lastName = instructorUser.returnLN();  // last name

    Student adminUser;
    int A_userID = adminUser.returnID();  // id variable
    string A_firstName = adminUser.returnFN();  // first name variable
    string A_lastName = adminUser.returnLN();  // last name

    switch (key) {  // depending on usertype, enter into options menu
    case 2:  // ---------------- STUDENT ----------------
        // way to loop back to menu and cin >> option within each function
        while (exitMenu != 1) {  // allow multiple menu selections and exit when you wish
            menuS();  // print menu for student functions thru displays.cpp
            cin >> option;
            switch (option) {
            case 1:  // ---------------------- SEARCH course list
                cout << "Enter A Filter To Search Courses By:" << endl;
                cout << "1. 'CRN'\n2. 'DEPT'\n3. 'DOTW'\n4. 'SEMESTER'\nFilter: ";
                cin >> choice;
                switch (choice) {
                case 1:  // search by CRN
                    col = "CRN";  // assign column
                    cout << "\nEnter Course CRN [101, 141, 211, 231, 331, 501, 601]: ";
                    cin >> parameter;  // assign parameter
                    break;
                case 2:  // search by crn
                    col = "DEPT";
                    cout << "\nEnter Department Abbreviation [BSEE, BSCO, BSAS, HUSS]: ";
                    cin >> parameter;
                    break;
                case 3:  // search by dotw
                    col = "DOTW";
                    cout << "\nEnter The First Letter Weekday [M,T,W,R,F]: ";
                    cin >> parameter;
                    break;
                case 4:  // search by semester
                    col = "SEMESTER";
                    cout << "\nEnter A Semester [SPR, SUM, FAL]: ";
                    cin >> parameter;
                    break;
                }
                studentUser.search_course(db, choice, col, parameter);
                break;
            case 2:  // ---------------------- ADD/DROP courses
                loop = 1;
                while (loop == 1) {  // keep editing
                    cout << "\n[0] EXIT TO MAIN PAGE\nAdd Course From Schedule";
                    cout << "\nEnter Course CRN: ";
                    cin >> CRN;  // gather desired CRN from user or 0 to exit
                    if (CRN == 0) {
                        break;  // if user wants to exit course editing break out of case statement
                    }
                    cout << "Would you like to add or drop this course?\n[1] ADD [2] DROP";
                    cin >> option;
                    switch (option) {
                    case 1:  // ---------------------- ADD course
                        studentUser.add_course(db, S_userID, CRN);
                        break;
                    case 2:  // ---------------------- DROP course
                        studentUser.drop_course(db, S_userID, CRN);
                        break;
                    }
                    cout << "\n\nContinue Editing? [1] Stay [0] Return To Main Menu\n\n>> ";
                    cin >> loop;  // loop for editing courses
                }  // while loop
                break;
            case 3:  // print schedule
                studentUser.print_schedule(db, S_userID);  // carryout print schedule function
                break;
            case 0:  // logout
                exitMenu = 1;  // set exitMenu to exit
                break;
            }
        }  // while exitMenu != 1
        break;
    case 3:  // ---------------- INSTRUCTOR ----------------
        menuI();  // print menu for instructor functions
        cin >> option;
        switch (option) {
        case 1:  // search course list
            break;
        case 2:  // print schedule
            break;
        case 3:  // print class roster
            break;
        case 0:  // logout
            break;
        }
        break;
    case 4:  // ---------------- ADMIN ----------------
        menuA();  // print menu for admin functions
        cin >> option;
        switch (option) {
        case 1:  //search/option to EDIT (add/remove) course list
            break;
        case 2:  // print ALL available courses
            break;
        case 3:  // add/remove course (case 1 can access this option directly too)
            break;
        case 4:  // print class roster
            break;
        case 5:  // add/drop student from course
            break;
        case 6:  // print all users
            break;
        case 7:  // add/remove user from database
            break;
        case 0:  // logout
            break;
        }
        break;
    }

    sqlite3_close(db);  // *match* to database open (*)

    return 0;
}