#include "User.h"
#include <iostream>
#include <string>


using std::string;
using std::cout;

User::User() {
	ID = 0000;  // represents guest account w no info
	first_name = "TEMP";
	last_name = "GUEST";
}
User::User(string in_first_name, string in_last_name) {
	ID = 0000;
	first_name = in_first_name;
	last_name = in_last_name;
}
User::User(string in_first_name, string in_last_name, int in_ID) {
	first_name = in_first_name;
	last_name = in_last_name;
}

//method
string User::show_name() {
	return first_name, last_name;
}


//destreuctor (delete)
User::~User() {

}