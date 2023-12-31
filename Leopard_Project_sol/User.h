#pragma once
#include <string>
#include <iostream>
#include "sqlite3.h"
#include <cctype>

using std::string;
using std::cout;
using std::cin;
using std::endl;

using namespace std;


class User
{
public:
	//attritude (data)
	string first_name;
	string last_name;
	string placeholder;
	int ID;

	//constructor (initial value)
	User();
	User(string in_first_name, string in_last_name);
	User(string in_first_name, string in_last_name, int in_ID);

	//method
	void print_info();  // print id and name
	int returnID();
	string returnFN();
	string returnLN();

	//destructor (delete)
	~User();

};
