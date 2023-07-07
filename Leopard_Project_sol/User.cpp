#include "User.h"
#include <iostream>
#include <string>

User::User() {
	ID = 0000;  // represents guest account w no info
	first_name = "TEMP";
	last_name = "GUEST";
}
User::User(string in_first_name, string in_last_name) {
	ID = 0000;  //  rep guest account w no info
	first_name = in_first_name;
	last_name = in_last_name;
}
User::User(string in_first_name, string in_last_name, int in_ID) {
	first_name = in_first_name;
	last_name = in_last_name;
	ID = in_ID;
}

//method
void User::print_info() {
	cout << "User #" << ID << endl; //  print ID
	cout << last_name << ", " << first_name << endl; //  print last_name, first_name ex. "Arpino, Katherine"
}

//destructor (delete)
User::~User() {

}