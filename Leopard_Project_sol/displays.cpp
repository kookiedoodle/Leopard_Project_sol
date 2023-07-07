#include "displays.h"

// use this for any menu displays to lessen the main.cpp

void assign3() {
    cout << "========== MENU ==========" << endl;
    cout << "1. Search for records" << endl;
    cout << "2. Insert new records" << endl;
    cout << "3. Print all records from a table" << endl;
    cout << "4. Create a table" << endl;
    cout << "5. Update existing records" << endl;
    cout << "6. Remove records from the database" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}

void menuS() {  // student list
    cout << "========== MENU ==========" << endl;
    cout << "1. SEARCH Course List" << endl;  // make sure this option has user input parameters
    cout << "2. ADD/DROP Courses" << endl;  // based on course CRN
    cout << "3. PRINT Schedule" << endl;
    cout << "0- LOGOUT" << endl;
    cout << ">> ENTER OPTION: " << endl;
}

void menuI() {  // instructor list
    cout << "========== MENU ==========" << endl;
    cout << "1. SEARCH Course List" << endl;  // make sure this option has user input parameters
    cout << "2. PRINT Schedule" << endl;  // based on CRN + continue thinking of method
    cout << "3. PRINT Class Roster" << endl;  // search student database for students w matching CRN
    cout << "0- LOGOUT" << endl;
    cout << ">> ENTER OPTION: " << endl;
}

void menuA() {  // admin list
    cout << "========== *ADMIN* ==========" << endl;
    cout << "------- COURSE OPTIONS ------" << endl;  // course based editing and viewing
    cout << "1. SEARCH/EDIT Course List" << endl;  // add/remove based on CRN (if deleted, will automatically delete in student and instructor?)
    cout << "2. PRINT ALL Available Courses" << endl;  // implement this to print courses first thing in option 1
    cout << "3. ADD/REMOVE Courses" << endl; // make sure this option has user input parameters and add option to jump to print roster vv
    cout << "4. PRINT Course Roster" << endl;  // includes instructor and students, able to go back to search and jump to add/drop student
    cout << "-------- USER OPTIONS -------" << endl;
    cout << "5. ADD/DROP Student From Course" << endl;  // implement this to print courses first thing in option 1
    cout << "6. PRINT ALL Users" << endl;  // add/remove based on ID, have a CONFIRMATION if they really want to delete!!!
    cout << "7. ADD/REMOVE User From Database" << endl;  // implement this to print courses first thing in option 1
    cout << "0- LOGOUT" << endl;
    cout << ">> ENTER OPTION: " << endl;
}