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

    /*
    while (true) {
        cout << "---------- What are you? ----------\n";
        cout << "Enter the following options:\n";
        cout << "1 - Student\n";
        cout << "2 - Instructor\n";
        cout << "3 - Admin\n";
        cout << "0 - Exit\n";
        cout << "------------------------------------\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter your first name: ";
            cin >> first_name;
            cout << "Enter your last name: ";
            cin >> last_name;
            cout << "Enter your ID: ";
            cin >> ID;

            Student student_user(first_name, last_name, ID);

            //  edit: add sections
            while (1) {
                cout << "---------What do you want to do?------------\n";
                cout << "Enter the following options:\n";
                cout << "1 - search course" << endl;
                cout << "2 - add course" << endl;
                cout << "3 - drop course" << endl;
                cout << "4 - display schedule" << endl;
                cout << "0 - Exit" << endl;

                cin >> select;
                switch (select) {
                case 1:
                    cout << "Enter the course number name\n";
                    cin >> course_name;

                    student_user->search_course(course_name);
                case 2:
                    cout << "Enter the course CRN\n";
                    cin >> CRN;
                    student_user->add_course(CRN);
                case 3:
                    cout << "Enter the course CRN\n";
                    cin >> CRN;
                    student_user->drop_course(CRN);
                case 4:
                    student_user->display_schedule();
                case 0:
                    break;
                }
                //  edit ended
                break;
            }
        case 2: {
            cout << "Enter your first name: ";
            cin >> first_name;
            cout << "Enter your last name: ";
            cin >> last_name;
            cout << "Enter your ID: ";
            cin >> ID;

            Instructor instructor_user(first_name, last_name, ID);
            instructor_user.showCourses(db);
            break;
        }
        case 3: {
            cout << "Enter your first name: ";
            cin >> first_name;
            cout << "Enter your last name: ";
            cin >> last_name;
            cout << "Enter your ID: ";
            cin >> ID;

            Admin admin_user(first_name, last_name, ID);
            admin_user.showCourses(db);
            break;
        }
        case 0:
            cout << "Exiting the program. Goodbye!\n";
            sqlite3_close(db);
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
        */
    return 0;
}