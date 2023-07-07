#include<string>
#include "User.h"

using std::string;
extern char* errorMessage;


class Student :
	public User
{
protected:
	//attritude (data)
	string CRN;
	string course_name;
	string result;


public:
	//constructor (initial value)
	Student();
	Student(string in_first_name, string in_last_name);
	Student(string in_first_name, string in_last_name, int in_ID);

	//method
	string search_course(string& col, string& parameter);
	void add_course(int in_CRN, string blockPeriod);
	void drop_course(int in_CRN);
	string display_schedule();

	//destreuctor (delete)
	~Student();

};
