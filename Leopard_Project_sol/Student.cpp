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


// ------------------------------ SEARCH COURSES ------------------------------
string Student::search_course(string& col, string& parameter) {  // search via parameter
    char* errorMessage = nullptr;
    sqlite3* db;
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

// ------------------------------ ADD COURSES ------------------------------
void Student::add_course(int in_CRN, string blockPeriod) {  // work on this!!!!
    // to add course, we must have the student's ID,
    // have user give a block period they want the class in,
    // go to user that matches ID#, insert CRN code into specfic block
}

// ------------------------------ DROP COURSES ------------------------------
void Student::drop_course(int in_CRN) {
    // Implementation for dropping a course from the student's schedule
}

int Student::print_schedule(int userID) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int ID = userID;

    string courses[5]; // 5 cell array to store the courses

    // open database connection
    int exit = sqlite3_open("leopardDatabase.db", &db);
    if (exit != SQLITE_OK) {
        cout << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return exit;
    }

    // SQL statement to get courses from matched ID profile
    string sql = "SELECT COURSE_1, COURSE_2, COURSE_3, COURSE_4, COURSE_5 FROM STUDENT WHERE ID = ?";
    exit = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);  // prepare statement
    if (exit != SQLITE_OK) {  // failed SQL msg
        cout << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return exit;
    }

    // bind ID parameter to '?' in statement sql above
    sqlite3_bind_int(stmt, 1, ID);

    // execute statement
    exit = sqlite3_step(stmt);
    if (exit != SQLITE_ROW) {  // ID not found
        cout << "No matching student found with ID: " << ID << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return exit;
    }

    // go over columns 6 through 10 (COURSE_1 to COURSE_5) and upload to courses array
    for (int i = 6; i < 11; ++i) {
        const unsigned char* course = sqlite3_column_text(stmt, i);
        courses[i - 5] = string(reinterpret_cast<const char*>(course));  // translate gathered information and upload to courses
    }

    for (int i = 0; i < 5; ++i) {  // print schedule starting at COURSE_1
        cout << "COURSE " << (i + 1) << ": " << courses[i] << endl;
    }

    sqlite3_finalize(stmt);  // finalize statement
    sqlite3_close(db);  // close DB connection

    return SQLITE_OK;
}

//destructor (delete)
Student::~Student() {

}