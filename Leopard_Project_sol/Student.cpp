#include "Student.h"
#include <iostream>
#include <string>

string name;
string first_name;
string last_name;
int ID;

//constructor (initial value)
Student::Student() {
    name = "N/A";
}
Student::Student(string in_first_name, string in_last_name) {
    first_name = in_first_name;
    last_name = in_last_name;
}
Student::Student(string in_first_name, string in_last_name, int in_ID) {
    first_name = in_first_name;
    last_name = in_last_name;
    ID = in_ID;
}


//method
string Student::search_course(string& col, string& parameter) {  // search via parameter
    // open DB
    int exit = sqlite3_open("leopardDatabase.db", &db);
    if (exit != SQLITE_OK) {
        result = "Error opening the database.";
        return result;
    }

    // search course given column name and parameter to search (ex. search course provided CRN number)
    string command = "SELECT * FROM COURSES WHERE " + col + " = '" + parameter + "';";  // search column and parameter in that column

    exit = sqlite3_exec(db, command.c_str(), [](void* data, int argc, char** argv, char** azColName) -> int {
        // search result output, printing column info currently
        for (int i = 0; i < argc; i++) {
            std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }

        return 0;
    }, nullptr, &errorMessage);

    // Check for errors
    if (exit != SQLITE_OK) {
        result = "Error executing the search command.";
    }

    // close DB
    sqlite3_close(db);

    return result;
}

void Student::add_course(int in_CRN, string blockPeriod) {  // work on this!!!!
    // to add course, we must have the student's ID,
    // have user give a block period they want the class in,
    // go to user that matches ID#, insert CRN code into specfic block
}

void Student::drop_course(int in_CRN) {
    // Implementation for dropping a course from the student's schedule
}

string Student::display_schedule() {
    // Implementation for displaying the student's schedule
    return placeholder;
}

//destreuctor (delete)
Student::~Student() {

}