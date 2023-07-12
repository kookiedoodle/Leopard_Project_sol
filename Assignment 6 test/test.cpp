#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}



TEST(LoginTest, CorrectLogin) {
	performLogin studentTest{};
	ASSERT_EQ(, );
}

TEST(StudentTest, AnalyzeSearch) {
	Student studentUsertest{ 101 };
	ASSERT_EQ( Digital , studentUsertest.search_course());
}

TEST(AddCourseTest, CorrectCourse) {
	Student studentUsertest{ 10001, 101 };
	ASSERT_EQ( , studentUsertest.add_course());
}

TEST(DropCourseTest, CorrectCourse) {
	Student studentUsertest{ 10001, 101 };
	ASSERT_EQ(, studentUsertest.drop_course());
}