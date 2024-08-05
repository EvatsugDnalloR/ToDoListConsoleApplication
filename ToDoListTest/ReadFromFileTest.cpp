#include "pch.h"
#include <array>
#include <fstream>
#include <sstream>
#include "../ToDoList/ReadFromFile.h"

/**
 * Test if a string containing one ToDo is recognised successfully.
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

/**
 * Test if GetToDos can return an empty vector if it receives and empty string.
 */
TEST(GetToDos, EmptyString)
{
	const std::string empty_msg{};
	const std::vector<ToDo> test_todo_vector{ ReadFromFile::GetToDos(empty_msg) };

	EXPECT_TRUE(test_todo_vector.empty());
}

/**
 * Test if GetToDos throws an exception if it receives a string in the wrong format.
 */
TEST(GetToDos, ExceptionCase)
{
	// ReSharper disable once StringLiteralTypo
	const std::string wrong_msg{ "jdfnehfijfuwh  efef" };
	const std::string wrong_sharp_msg{ "This is #a message#0." };
	const std::string missing_boolean{ "This is a msg.#\nThis is the next message#1" };
	const std::string missing_sharp{ "This is a message .0" };

	EXPECT_THROW(ReadFromFile::GetToDos(wrong_msg), std::runtime_error);
	EXPECT_THROW(ReadFromFile::GetToDos(wrong_sharp_msg), std::runtime_error);
	EXPECT_THROW(ReadFromFile::GetToDos(missing_boolean), std::runtime_error);
	EXPECT_THROW(ReadFromFile::GetToDos(missing_sharp), std::runtime_error);
}

/**
 * Test if FileToString can recognise the content of the existing txt files.
 */
TEST(FileToString, GeneralCase)
{
	const std::string base_path{ "test_src/read_from_file/" };
	const std::string filename1{ base_path + "test1.txt" };
	const std::string filename2{ base_path + "test2.txt" };
	const std::string filename3{ base_path + "test3.txt" };

    const std::string test1{ "This is test 1, it should be like this." };
    const std::string test2{ "This is ToDo 1, not done yet.#0\nAnd this should be ToDo 2.#1" };
    const std::string test3{ "dkgshiofnesfheifdusjfnesjfhisenfoe" };

	const std::string content1 = ReadFromFile::FileToString(filename1);
	const std::string content2 = ReadFromFile::FileToString(filename2);
	const std::string content3 = ReadFromFile::FileToString(filename3);

	EXPECT_EQ(ReadFromFile::FileToString(filename1), test1);
	EXPECT_EQ(ReadFromFile::FileToString(filename2), test2);
	EXPECT_EQ(ReadFromFile::FileToString(filename3), test3);
}

/**
 * Test if FileToString can handle a txt file that does not exist, and then
 *		create a blank one of that name.
 */
TEST(FileToString, NoFileCase)
{
	const std::string blank_file_name{ "do_not_exist.txt" };
	const std::string blank{};
	EXPECT_EQ(ReadFromFile::FileToString(blank_file_name), blank);
	const std::ifstream infile{ blank_file_name };
	EXPECT_TRUE(infile);
}