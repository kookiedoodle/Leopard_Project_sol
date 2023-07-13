#include<string>
#include "User.h"

using std::string;
extern char* errorMessage;


class Student :
	public User
{
protected:
	//attritude (data)
	string result;
	int option;

public:
	//constructor (initial value)
	Student();
	Student(string in_first_name, string in_last_name);
	Student(string in_first_name, string in_last_name, int in_ID);

	//method
	string search_course(sqlite3* db, int choice, string col, string parameter);
	void add_course(sqlite3* db, int userID, int courseCRN);
	void drop_course(sqlite3* db, int userID, int courseCRN);
	int print_schedule(sqlite3* db, int userID);

	//destructor (delete)
	~Student();

};
