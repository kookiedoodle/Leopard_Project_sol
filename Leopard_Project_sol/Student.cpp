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
string Student::search_course(string in_course_name) {  // work on this!!!!
    return placeholder;
}
void Student::add_course(int in_CRN) {  // work on this!!!!

}
void Student::drop_course(int in_CRN) {  // work on this!!!!

}
string Student::display_schedule() {
    return placeholder;
}

//destreuctor (delete)
Student::~Student() {

}