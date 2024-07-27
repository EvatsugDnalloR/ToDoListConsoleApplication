#include "pch.h"

#include <array>

#include "../ToDoListConsoleApplication/ReadFromFile.cpp"

/**
 * Test if a string containing one ToDo is able to be recognised successfully.
 */
TEST(GetToDos, SingleToDo)
{
	const std::string single_msg{ "Finish the code !#0" };
	const std::vector<ToDo> test_todo_vector{ ReadFromFile::GetToDos(single_msg) };

	EXPECT_EQ(test_todo_vector.size(), 1);

	std::ostringstream oss_test;
	oss_test << test_todo_vector.at(0);
	EXPECT_EQ(oss_test.str(), "Finish the code ! [  ]");
}

/**
 * Test if a string containing multiple ToDos is able to be recognised successfully.
 */
TEST(GetToDos, MultiToDos)
{
	const std::string multi_msg{ "Finish the code!#1\nDo this shit now.#0\nLeave this place.#0" };
	const std::vector<ToDo> test_todo_vector{ ReadFromFile::GetToDos(multi_msg) };

	EXPECT_EQ(std::size(test_todo_vector), 3);

	std::array<std::ostringstream, 3> oss_tests;

	for (int i{}; i < oss_tests.size(); i++)
	{
		
		oss_tests.at(i) << test_todo_vector.at(i);
	}

	EXPECT_EQ(oss_tests.at(0).str(), "Finish the code! [ Done ]");
	EXPECT_EQ(oss_tests.at(1).str(), "Do this shit now. [  ]");
	EXPECT_EQ(oss_tests.at(2).str(), "Leave this place. [  ]");
}

TEST(GetToDos, EmptyString)
{
	const std::string empty_msg{};
	const std::vector<ToDo> test_todo_vector{ ReadFromFile::GetToDos(empty_msg) };

	EXPECT_TRUE(test_todo_vector.empty());
}

TEST(GetToDos, ExceptionCase)
{
	// ReSharper disable once StringLiteralTypo
	const std::string wrong_msg{"jdfnehfijfuwh  efef"};
	const std::string wrong_sharp_msg{ "This is #a message#0." };
	const std::string missing_boolean{ "This is a msg.#\nThis is the next message#1" };
	const std::string missing_sharp{ "This is a message .0" };

	EXPECT_THROW(ReadFromFile::GetToDos(wrong_msg), std::runtime_error);
	EXPECT_THROW(ReadFromFile::GetToDos(wrong_sharp_msg), std::runtime_error);
	EXPECT_THROW(ReadFromFile::GetToDos(missing_boolean), std::runtime_error);
	EXPECT_THROW(ReadFromFile::GetToDos(missing_sharp), std::runtime_error);
}