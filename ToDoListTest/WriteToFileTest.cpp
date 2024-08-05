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
	const std::string filename{ "delete_todo_test.txt" };

	WriteToFile::DeleteToDo(0, std::format("{}{}", kBasePath, filename));

	EXPECT_EQ("This is the second ToDo msg.#1\n",
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}

TEST(MarkAsDone, SuccessMarking)
{
	const std::string filename{ "mark_as_done_test.txt" };

	WriteToFile::MarkAsDone(0, std::format("{}{}", kBasePath, filename));
	WriteToFile::MarkAsDone(1, std::format("{}{}", kBasePath, filename));

	EXPECT_EQ("This one should be done after.#1\nThis one should be marked undone#0\nThis one should not be changed ! #1\n",
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}

TEST(ModifyToDoMsg, SuccessModification)
{
	const std::string filename{ "modify_test.txt" };
	const std::string modify_msg{ "This line has been modified" };

	WriteToFile::ModifyToDoMsg(0, modify_msg, std::format("{}{}", kBasePath, filename));

	EXPECT_EQ(std::format("{}#0\nThis line should not be modified#1\n", modify_msg),
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}