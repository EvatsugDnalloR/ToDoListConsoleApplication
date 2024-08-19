#include <memory>
#include "CommandTest.h"
#include "../pch.h"
#include "../../Command/AddToDoCommand.h"

/**
 * A class to create setup and teardown process for each AddToDoCommand test,
 *   where each test require a clean "specification.txt" file present.
 * In this way no problem about multiple tests accessing the same txt file
 *   at the same time occurs.
 */
class AddToDoCommandTest : public CommandTest
{
};

/**
 * Test if AddToDoCommand works as expected when a single user input
 *   To_Do message need to be inserted.
 */
TEST_F(AddToDoCommandTest, SingleToDoMsg)
{
	std::string input{ "This is a ToDo message..." };
	//std::ofstream outfile(kFilename);

	const auto command = std::make_shared<AddToDoCommand>(input);
	command->Execute();
	EXPECT_EQ(ReadFromFile::FileToString(kFilename), 
		std::format("{}#0\n", input));

	command->Revert();
	EXPECT_TRUE(WriteToFile::GetLines(kFilename).empty());	// should be empty just like initial state
}

/**
 * Test if AddToDoCommand works as expected when multiple user input
 *   To_Do messages need to be inserted.
 */
TEST_F(AddToDoCommandTest, MultipleToDoMsg)
{
	const std::string input1{ "This is the first ToDo message." };
	const std::string input2{ "This is the second ToDo message.,.,.,." };
	const std::string input3{ "This is the third ToDo message!!!" };

	const auto command = std::make_shared<AddToDoCommand>(input1);
	command->Execute();

	// reset the {user_input_} variable and set the execution state to false for further execution
	command->SetUserInput(input2);
	command->SetExecuted(false);
	command->Execute();	// add {input2} to the file

	command->SetUserInput(input3);
	command->SetExecuted(false);
	command->Execute();	// add {input3} to the file

	EXPECT_EQ(ReadFromFile::FileToString(kFilename),
		std::format("{}#0\n{}#0\n{}#0\n", input1, input2, input3));

	command->Revert();	// the last inserted To_Do message should be deleted
	EXPECT_EQ(ReadFromFile::FileToString(kFilename),
		std::format("{}#0\n{}#0\n", input1, input2));

	command->SetExecuted(true);	// set the execution state to true for further undo
	command->Revert();
	EXPECT_EQ(ReadFromFile::FileToString(kFilename),
		std::format("{}#0\n", input1));

	command->SetExecuted(true);
	command->Revert();
	EXPECT_TRUE(WriteToFile::GetLines(kFilename).empty());
}

/**
 * Test if AddToDoCommand can throw the exception when it violates the
 *   preconditions of {WriteToFile::AddToDo} method.
 * The exception for the Revert case is similar.
 */
TEST_F(AddToDoCommandTest, ExecuteException)
{
	// invalid argument when the input message contain any '#' character
	std::string exception_input{ "This input ## is invalid..." };
	const auto command = std::make_shared<AddToDoCommand>(exception_input);
	EXPECT_THROW(command->Execute(), std::invalid_argument);

	// runtime_error when the "specification.txt" file doesn't exist
	command->SetExecuted(false);
	exception_input = "This input is valid...";
	command->SetUserInput(exception_input);
	std::filesystem::remove(kFilename);	// delete the file before execution
	EXPECT_THROW(command->Execute(), std::runtime_error);
}
