#pragma once
#include <string>
#include <iostream>
#include "sqlite3.h"

sqlite3* db;
char* messageError;
char* errorMessage;

using std::string;
using std::string;
using std::cout;
using std::cin;
using std::endl;


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

	//destreuctor (delete)
	~User();

};
