#include "Student.h"
#include "displays.h"
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


// ------------------------------------------------------------ SEARCH COURSES 
string Student::search_course() {  // search via parameter
    char* errorMessage = nullptr;
    sqlite3* db;
    // open DB
    int exit = sqlite3_open("leopardDatabase.db", &db);
    if (exit != SQLITE_OK) {
        result = "Error opening the database.";
        return result;
    }

    int choice;
    string col;
    string parameter;

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
        result = "\nCOURSE NOT FOUND.";
    }

    sqlite3_close(db);  // close DB

    return result;
}

// ------------------------------------------------------------ ADD COURSES 
void Student::add_course(sqlite3* db, int userID, int courseCRN) {
    // begin creating SQL statement to update the course col
    int option;
    string sql = "UPDATE STUDENT SET ";

    // building SET clause to remove the course CRN from the correct col
    for (int i = 1; i <= 5; ++i) {
        string columnName = "COURSE_" + std::to_string(i);
        sql += columnName + " = CASE WHEN " + columnName + " IS NULL THEN " + std::to_string(courseCRN) +
            " ELSE " + columnName + " END";

        if (i != 5) {  // separate unless last item
            sql += ", ";
        }
    }

    // only update row with the matching user ID
    sql += " WHERE ID = " + std::to_string(userID);

    // confirm desired course  deletion
    cout << "Confirm Addition of Course " << courseCRN << endl;
    cout << "[1] CONFIRM ADDITION [2] CANCEL ADDITION";
    cin >> option;
    if (option == 1) {  // confirm addition and carry out command
        int exit = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    }

    if (exit != SQLITE_OK) {
        std::cout << "Error executing SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Course " << courseCRN << " added to schedule." << std::endl;
    }
}

// ------------------------------------------------------------ DROP COURSES 
void Student::drop_course(sqlite3* db, int userID, int courseCRN) {
    // begin creating SQL statement to update the course col
    string sql = "UPDATE STUDENT SET ";

    // building SET clause to remove the course CRN from the correct col
    for (int i = 1; i <= 5; ++i) {
        string columnName = "COURSE_" + to_string(i);
        sql += columnName + " = CASE WHEN " + columnName + " = " + to_string(courseCRN) +
            " THEN NULL ELSE " + columnName + " END";

        if (i != 5) {  // seperate unless last item
            sql += ", ";
        }
    }

    // only update row with the matching user ID
    sql += " WHERE ID = " + to_string(userID);

    // confirm desired course deletion
    cout << "Confirm Deletion of Course " << courseCRN << endl;
    cout << "[1] CONFIRM DELETION [2] CANCEL DELETION";
    cin >> option;
    if (option == 1) {  // confirm deletion and carry out command
        int exit = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    }

    if (exit != SQLITE_OK) {
        cout << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
    }
    else {
        cout << "Course " << courseCRN << " removed from schedule." << endl;
    }
}

// ------------------------------------------------------------ PRINT SCHEDULE 
int Student::print_schedule(int user_ID) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int userID = user_ID;  // gather user's ID for searching courses

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
    sqlite3_bind_int(stmt, 1, userID);

    // execute statement
    exit = sqlite3_step(stmt);
    if (exit != SQLITE_ROW) {  // ID not found
        cout << "No matching student found with ID: " << userID << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return exit;
    }

    // go over columns 6 through 10 (COURSE_1 to COURSE_5) and upload to courses array
    for (int i = 6; i < 11; ++i) {
        const unsigned char* course = sqlite3_column_text(stmt, i);
        courses[i - 6] = string(reinterpret_cast<const char*>(course));  // translate gathered information and upload to courses
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