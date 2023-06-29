#include "Instructor.h"
#include <iostream>
#include <string>


using std::string;
using std::cout;

//constructor (initial value)
Instructor::Instructor() {
    ID = 0000;
    first_name = "GUEST";
    last_name = "INSTRUCTOR";
}
Instructor::Instructor(string in_first_name, string in_last_name) {
    ID = 0000;
    first_name = in_first_name;
    last_name = in_last_name;
}
Instructor::Instructor(string in_first_name, string in_last_name, int in_ID) {
    first_name = in_first_name;
    last_name = in_last_name;
    ID = in_ID;
}


//method
string Instructor::search_course(string in_course_name) {
    return placeholder;
}
string Instructor::print_schedule() {
    return placeholder;
}
string Instructor::print_class_list() {
    return placeholder;
}

//destreuctor (delete)
Instructor::~Instructor() {

}