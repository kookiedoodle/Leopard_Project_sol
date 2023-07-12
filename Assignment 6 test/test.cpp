#include "pch.h"
#include "../Leopard_Project_sol/Admin.h"
#include "../Leopard_Project_sol/displays.h"
#include "../Leopard_Project_sol/instructor.h"
#include "../Leopard_Project_sol/sqlite3.h"
#include "../Leopard_Project_sol/Student.h"
#include "../Leopard_Project_sol/User.h"


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}



//TEST(LoginTest, CorrectLogin) {
	//performLogin studentTest{};
	//ASSERT_EQ(, );
//}

//TEST(StudentTest, AnalyzeSearch) {
//	Student studenttest{ };
//	ASSERT_EQ( "Digital", studenttest.search_course());
//}

TEST(AddCourseTest, CorrectCourse) {
	Student student;
	std::istringstream input("1");
	std::cin.rdbuf(input.rdbuf());

	int result = search_course();
	EXPECT_EQ(result, )


}

TEST(DropCourseTest, CorrectCourse) {
	Student studentUsertest{ 10001, 101 };
	ASSERT_EQ(, studentUsertest.drop_course());
}

TEST(PrintScheduleTest, CorrectSchedule) {
	Student studentUsertest{ 10001 };
	ASSERT_EQ( , studentUsertest.add_course());
}