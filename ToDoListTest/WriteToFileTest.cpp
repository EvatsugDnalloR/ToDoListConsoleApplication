#include "pch.h"
#include "../ToDoList/ReadFromFile.h"
#include "../ToDoList/WriteToFile.h"

const std::string kBasePath{ "test_src/write_to_file/" };

TEST(AddToDo, SuccessAppend)
{
	const std::string input_todo{ "This is a test msg." };
	const std::string filename{ "add_todo_test.txt" };

	WriteToFile::AddToDo(input_todo, std::format("{}{}", kBasePath, filename));

	EXPECT_EQ("This is a test msg.#0\n", 
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}

TEST(DeleteToDo, SuccessDeletion)
{
	constexpr size_t chosen_line{ 0 };
	const std::string filename{ "delete_todo_test.txt" };

	WriteToFile::DeleteToDo(chosen_line, std::format("{}{}", kBasePath, filename));

	EXPECT_EQ("This is the second ToDo msg.#1\n",
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}