#include "pch.h"
#include "../ToDoListConsoleApplication/ReadFromFile.cpp"

TEST(CorrectMatch, SingleToDo)
{
	const std::string single_msg{ "Finish the code !#0" };
	const std::vector<ToDo> test_todo_vector{ ReadFromFile::GetToDos(single_msg) };

	EXPECT_EQ(std::size(test_todo_vector), 1);

	std::ostringstream oss_test;
	oss_test << test_todo_vector.at(0);
	EXPECT_EQ(oss_test.str(), "Finish the code ! [  ]");
}