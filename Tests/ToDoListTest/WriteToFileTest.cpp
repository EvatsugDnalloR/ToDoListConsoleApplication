#include <array>
#include "../pch.h"
#include "../../ToDoList/ReadFromFile.h"
#include "../../ToDoList/WriteToFile.h"

const static std::string kBasePath{ "test_src/write_to_file/" };

/**
 * Test if AddToDo can append a To_Do message to an empty file.
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
 * Test if AddToDo can append a To_Do message to a file already contains
 *		some To_Do messages.
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
 * Test if AddToDo can throw an exception if the target file does not exist.
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
 * Test if AddToDo can throw an exception if the input string contains
 *		any '#' character.
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
 * Test if DeleteToDo can delete a single To_Do from some ToDos.
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
 * Test if DeleteToDo can delete multiple ToDos from more ToDos.
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
 * Test if DeleteToDo can throw an exception if the target line of To_Do
 *		doesn't exist.
 */
TEST(DeleteToDo, LineNotExist)
{
	const std::string filename{ "delete_todo_test_simple.txt" };

	EXPECT_THROW(WriteToFile::DeleteToDo(100, 
		std::format("{}{}", kBasePath, filename)),
		std::invalid_argument);
}

/**
 * Test if DeleteToDo can throw an exception if the target file does not exist.
 */
TEST(DeleteToDo, FileNotExist)
{
	const std::string filename{ "does_not_exist.txt" };

	EXPECT_THROW(WriteToFile::DeleteToDo(0,
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}

/**
 * Test if MarkAsDone can modify the conditions of multiple ToDos.
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
 * Test if MarkAsDone can throw an exception if the target line of To_Do
 *		does not contain any '#' character.
 */
TEST(MarkAsDone, InvalidToDo)
{
	const std::string filename{ "mark_as_done_invalid.txt" };

	EXPECT_THROW(WriteToFile::MarkAsDone(0, 
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}

/**
 * Test if MarkAsDone can throw an exception if the target line of To_Do
 *		does not exist.
 */
TEST(MarkAsDone, LineNotExist)
{
	const std::string filename{ "mark_as_done_test.txt" };

	EXPECT_THROW(WriteToFile::MarkAsDone(100, 
		std::format("{}{}", kBasePath, filename)),
		std::invalid_argument);
}

/**
 * Test if MarkAsDone can throw an exception if the target file does not exist.
 */
TEST(MarkAsDone, FileNotExist)
{
	const std::string filename{ "does_not_exist.txt" };

	EXPECT_THROW(WriteToFile::MarkAsDone(0, 
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}

/**
 * Test if ModifyToDoMsg can modify the message of a single To_Do.
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
 * Test if ModifyToDoMsg can modify the messages of multiple ToDos.
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
 * Test if ModifyToDoMsg can throw an exception if the modification message
 *		contains any '#' character.
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

/**
 * Test if ModifyToDoMsg can throw an exception if the target line of To_Do
 *		does not have a '#' character.
 */
TEST(ModifyToDoMsg, ToDoLineInvalid)
{
	const std::string filename{ "modify_test_invalid.txt" };

	EXPECT_THROW(WriteToFile::ModifyToDoMsg(0,
		"any modification",
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}

/**
 * Test if ModifyToDoMsg can throw an exception if the target line of To_Do
 *		does not exist.
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
 * Test if ModifyToDoMsg can throw an exception if the target file does not exist.
 */
TEST(ModifyToDoMsg, FileNotExist)
{
	const std::string filename{ "does_not_exist.txt" };

	EXPECT_THROW(WriteToFile::ModifyToDoMsg(0,
		"some modification...",
		std::format("{}{}", kBasePath, filename)),
		std::runtime_error);
}

/**
 * Test if GetLines can correctly put each line of the txt file into a vector.
 */
TEST(GetLines, GeneralCase1)
{
	const std::string filename{ "get_lines_1.txt" };

	const std::vector expected{
		"This is a first line #1",
		"A second line#0",
		"Third line.......",
		"fourth one..."
	};

	const std::vector actual{ WriteToFile::GetLines(
		std::format("{}{}", kBasePath, filename))
	};

	for (size_t i{}; i < actual.size(); i++)
	{
		EXPECT_EQ(expected.at(i), actual.at(i));
	}
}

/**
 * Test if GetLines can correctly put each line of the txt file into a vector.
 */
TEST(GetLines, GeneralCase2)
{
	const std::string filename{ "get_lines_2.txt" };

	const std::vector expected{
		// ReSharper disable once StringLiteralTypo
		"jsdbfjksbefesbf",
		// ReSharper disable once StringLiteralTypo
		"ajksdhfkjsdfsd",
		// ReSharper disable once StringLiteralTypo
		"ejkfbsekfnsejkf",
		// ReSharper disable once StringLiteralTypo
		"sejkfsefbesjbf",
		// ReSharper disable once StringLiteralTypo
		"skefbsejkfbsekj"
	};

	const std::vector actual{ WriteToFile::GetLines(
		std::format("{}{}", kBasePath, filename))
	};

	for (size_t i{}; i < actual.size(); i++)
	{
		EXPECT_EQ(expected.at(i), actual.at(i));
	}
}

/**
 * Test if GetLines can throw an exception if the target file does not exist.
 */
TEST(GetLines, ExceptionCase)
{
	const std::string filename{ "does not exist" };

	EXPECT_THROW(auto vector{ WriteToFile::GetLines(
		std::format("{}{}", kBasePath, filename))
		}, 
		std::runtime_error);
}

/**
 * Test if ModifyFile can correctly modify an empty file.
 */
TEST(ModifyFile, EmptyFileModification)
{
	const std::string filename{ "modify_file_1.txt" };
	const std::string input1{ "This is a message" };
	const std::string input2{ "This is another message##1" };
	const std::string input3{ "This is the last message...." };

	WriteToFile::ModifyFile(std::format("{}{}", kBasePath, filename),
		[input1, input2, input3]
			{
				const std::vector lines{ input1, input2, input3 };
				return lines;
			}());

	EXPECT_EQ(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename)),
		std::format("{}\n{}\n{}\n", input1, input2, input3));
}

/**
 * Test if ModifyFile can correctly modify a file that is already filled
 *   with some texts, and this file should be directly overriden (i.e.
 *   no original information left).
 */
TEST(ModifyFile, FilledFileModification)
{
	const std::string filename{ "modify_file_2.txt" };
	const std::string input1{ "This is a message" };
	const std::string input2{ "This is another message##1" };
	const std::string input3{ "This is the last message...." };
	// ReSharper disable once StringLiteralTypo
	const std::string input4{ "kdshfijfiesfsief" };
	// ReSharper disable once StringLiteralTypo
	const std::string input5{ "sedfhsiefbnisehfsef" };
	// ReSharper disable once StringLiteralTypo
	const std::string input6{ "sjkfseifnsefihsef" };

	WriteToFile::ModifyFile(std::format("{}{}", kBasePath, filename),
		[input1, input2, input3, input4, input5, input6]
		{
			const std::vector lines{
				input1,
				input2,
				input3,
				input4,
				input5
				, input6
			};
			return lines;
		}());

	EXPECT_EQ(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename)),
		std::format("{}\n{}\n{}\n{}\n{}\n{}\n",
			input1, input2, input3, input4, input5, input6));

}