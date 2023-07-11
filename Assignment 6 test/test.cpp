#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(LoginTest, CorrectLogin) {
	performLogin rTest{};
	ASSERT_EQ(, rTest.key);
}