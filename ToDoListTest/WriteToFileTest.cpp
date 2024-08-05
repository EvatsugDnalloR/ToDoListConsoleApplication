#include <array>

#include "pch.h"
#include "../ToDoList/ReadFromFile.h"
#include "../ToDoList/WriteToFile.h"

const std::string kBasePath{ "test_src/write_to_file/" };

/**
 * 
 */
TEST(AddToDo, SuccessEmptyAppend)
{
	const std::string input_todo{ "This is a test msg." };
	const std::string filename{ "add_todo_test_empty.txt" };

	WriteToFile::AddToDo(input_todo, std::format("{}{}", kBasePath, filename));

	EXPECT_EQ("This is a test msg.#0\n", 
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}

/**
 * 
 */
TEST(AddToDo, SuccessNotEmptyAppend)
{
	const std::string input_todo{ "This is the message to be appended !!" };
	const std::string filename{ "add_todo_test_not_empty.txt" };

	WriteToFile::AddToDo(input_todo, std::format("{}{}", kBasePath, filename));

	EXPECT_EQ(std::format("This message already exists.#1\n{}#0\n", input_todo),
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}

/**
 * 
 */
TEST(AddToDo, FileDoesNotExist)
{
	const std::string input_todo{ "This is a test msg." };
	const std::string filename{ "does_not_exist.txt" };

	EXPECT_THROW(WriteToFile::AddToDo(input_todo, 
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}

/**
 * 
 */
TEST(AddToDo, InputContiansSharp)
{
	const std::string input_todo{ "This input ### contains #." };
	const std::string filename{ "add_todo_test_empty.txt" };

	EXPECT_THROW(WriteToFile::AddToDo(input_todo, 
		std::format("{}{}", kBasePath, filename)),
		std::invalid_argument);
}

/**
 * 
 */
TEST(DeleteToDo, SimpleDeletion)
{
	const std::string filename{ "delete_todo_test_simple.txt" };

	WriteToFile::DeleteToDo(0, 
		std::format("{}{}", kBasePath, filename));

	EXPECT_EQ("This is the second ToDo msg.#1\n",
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}

/**
 * 
 */
TEST(DeleteToDo, ComplexDeletion)
{
	const std::string filename{ "delete_todo_test_complex.txt" };

	WriteToFile::DeleteToDo(2, 
		std::format("{}{}", kBasePath, filename));
	WriteToFile::DeleteToDo(2,
		std::format("{}{}", kBasePath, filename));

	EXPECT_EQ("This is the first msg.#1\nThis is the second msg.#0\nThis is the last ToDo.,.,,.#0\n",
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}

/**
 * 
 */
TEST(DeleteToDo, LineNotExist)
{
	const std::string filename{ "delete_todo_test_simple.txt" };

	EXPECT_THROW(WriteToFile::DeleteToDo(100, 
		std::format("{}{}", kBasePath, filename)),
		std::invalid_argument);
}

/**
 * 
 */
TEST(DeleteToDo, FileNotExist)
{
	const std::string filename{ "does_not_exist.txt" };

	EXPECT_THROW(WriteToFile::DeleteToDo(0,
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}

/**
 * 
 */
TEST(MarkAsDone, SuccessMarking)
{
	const std::string filename{ "mark_as_done_test.txt" };

	WriteToFile::MarkAsDone(0, std::format("{}{}", kBasePath, filename));
	WriteToFile::MarkAsDone(1, std::format("{}{}", kBasePath, filename));

	EXPECT_EQ(
		"This one should be done after.#1\nThis one should be marked undone#0\nThis one should not be changed ! #1\n",
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}

/**
 * 
 */
TEST(MarkAsDone, InvalidToDo)
{
	const std::string filename{ "mark_as_done_invalid.txt" };

	EXPECT_THROW(WriteToFile::MarkAsDone(0, 
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}

/**
 * 
 */
TEST(MarkAsDone, LineNotExist)
{
	const std::string filename{ "mark_as_done_test.txt" };

	EXPECT_THROW(WriteToFile::MarkAsDone(100, 
		std::format("{}{}", kBasePath, filename)),
		std::invalid_argument);
}

/**
 * 
 */
TEST(MarkAsDone, FileNotExist)
{
	const std::string filename{ "does_not_exist.txt" };

	EXPECT_THROW(WriteToFile::MarkAsDone(0, 
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}

/**
 * 
 */
TEST(ModifyToDoMsg, SingleModification)
{
	const std::string filename{ "modify_test_single.txt" };
	const std::string modify_msg{ "This line has been modified" };

	WriteToFile::ModifyToDoMsg(0, 
		modify_msg, 
		std::format("{}{}", kBasePath, filename));

	EXPECT_EQ(std::format("{}#0\nThis line should not be modified#1\n", modify_msg),
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}

/**
 * 
 */
TEST(ModifyToDoMsg, MultiModification)
{
	const std::string filename{ "modify_test_multi.txt" };
	const std::string modify_msg1{ "The first line is modified" };
	const std::string modify_msg2{ "The second line is also modified" };
	const std::string modify_msg3{ "The third line also haha modified,..,.,.,." };
	const std::string modify_msg4{ "No line is able to be unmodified..." };

	const std::array modify_messages{
		modify_msg1,
		modify_msg2,	
		modify_msg3,
		modify_msg4
	};

	for (int i = 0; i < modify_messages.size(); i++)
	{
		WriteToFile::ModifyToDoMsg(i, 
			modify_messages.at(i), 
			std::format("{}{}", kBasePath, filename));
	}

	EXPECT_EQ(std::format("{}#0\n{}#0\n{}#0\n{}#0\n",
		modify_msg1, modify_msg2, modify_msg3, modify_msg4),
		ReadFromFile::FileToString(std::format("{}{}", kBasePath, filename)));
}

/**
 * 
 */
TEST(ModifyToDoMsg, MsgContiansSharp)
{
	const std::string modify_msg{ "This input ### contains #." };
	const std::string filename{ "modify_test_single.txt" };

	EXPECT_THROW(WriteToFile::ModifyToDoMsg(0, 
		modify_msg, 
		std::format("{}{}", kBasePath, filename)),
		std::invalid_argument);
}

TEST(ModifyToDoMsg, ToDoLineInvalid)
{
	const std::string filename{ "modify_test_invalid.txt" };

	EXPECT_THROW(WriteToFile::ModifyToDoMsg(0,
		"any modification",
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}

/**
 * 
 */
TEST(ModifyToDoMsg, LineNotExist)
{
	const std::string filename{ "modify_test_single.txt" };

	EXPECT_THROW(WriteToFile::ModifyToDoMsg(100,
		"some modification...",
		std::format("{}{}", kBasePath, filename)),
		std::invalid_argument);
}

/**
 * 
 */
TEST(ModifyToDoMsg, FileNotExist)
{
	const std::string filename{ "does_not_exist.txt" };

	EXPECT_THROW(WriteToFile::ModifyToDoMsg(0,
		"some modification...",
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}