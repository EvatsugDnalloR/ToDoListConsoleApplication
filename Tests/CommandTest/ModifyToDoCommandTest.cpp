#include <memory>

#include "CommandTest.h"
#include "../pch.h"
#include "../../Command/ModifyToDoCommand.h"
#include "../../ToDoList/ReadFromFile.h"

/** A default string that should be written to the specification.txt file. */
const static std::string kDefaultContent{
		"This is a first message.#0\n"
			"This is a second one...#1\n"
			"The third one .,.,., #0\n"
			"The fourth one ofc,,,#1\n"
			"Gonna need some fifth one.#0\n"
};

/**
 * Inherited from CommandTest for SetUp and TearDown method.
 */
class ModifyToDoCommandTest : public CommandTest
{
	/**
	 * Need modification where if "specification.txt" is created correctly,
	 *   then write the default string {kDefaultContent} into it.
	 */
	void SetUp() override
	{
		if (std::ofstream outfile(kFilename); outfile)
		{
			outfile << kDefaultContent;
		}
		else
		{
			std::cerr << "Failed to create file: " << kFilename << "\n";
		}
	}
};

/**
 * Test if ModifyToDoCommand can handle the modification of a single line of To_Do message.
 */
TEST_F(ModifyToDoCommandTest, SingleModification)
{
	std::string modified{ "This is a modified string..." };
	const auto command = std::make_shared<ModifyToDoCommand>(3, modified);

	command->Execute();

	const std::vector to_do_s{ ReadFromFile::GetToDos(ReadFromFile::FileToString(kFilename)) };

	EXPECT_EQ(to_do_s.at(3).msg, modified);
	EXPECT_TRUE(to_do_s.at(3).done);	//the done boolean should not change after modification

	command->Revert();

	EXPECT_EQ(ReadFromFile::FileToString(kFilename), kDefaultContent);
}

/**
 * Test if ModifyToDoCommand execute correctly when there's multiple modification happens.
 */
TEST_F(ModifyToDoCommandTest, MultiModification)
{
	std::string modified1{ "This is a modified string..." };
	std::string modified2{ "This is another modification!" };
	// ReSharper disable once StringLiteralTypo
	std::string modified3{ "sjkdfhsdfbdus" };

	const auto command1 = std::make_shared<ModifyToDoCommand>(0, modified1);
	const auto command2 = std::make_shared<ModifyToDoCommand>(2, modified2);
	const auto command3 = std::make_shared<ModifyToDoCommand>(4, modified3);

	command1->Execute();
	command2->Execute();
	command3->Execute();

	std::vector to_do_s{ ReadFromFile::GetToDos(ReadFromFile::FileToString(kFilename)) };

	EXPECT_EQ(to_do_s.at(0).msg, modified1);
	EXPECT_FALSE(to_do_s.at(0).done);

	EXPECT_EQ(to_do_s.at(2).msg, modified2);
	EXPECT_FALSE(to_do_s.at(2).done);

	EXPECT_EQ(to_do_s.at(4).msg, modified3);
	EXPECT_FALSE(to_do_s.at(4).done);

	command1->Revert();

	to_do_s = ReadFromFile::GetToDos(ReadFromFile::FileToString(kFilename));

	EXPECT_EQ(to_do_s.at(0).msg, "This is a first message.");
	EXPECT_FALSE(to_do_s.at(0).done);

	EXPECT_EQ(to_do_s.at(2).msg, modified2);
	EXPECT_FALSE(to_do_s.at(2).done);

	EXPECT_EQ(to_do_s.at(4).msg, modified3);
	EXPECT_FALSE(to_do_s.at(4).done);

	command2->Revert();

	to_do_s = ReadFromFile::GetToDos(ReadFromFile::FileToString(kFilename));

	// {to_do_s.at(0)} was not changed here so no point to retest

	EXPECT_EQ(to_do_s.at(2).msg, "The third one .,.,., ");
	EXPECT_FALSE(to_do_s.at(2).done);

	EXPECT_EQ(to_do_s.at(4).msg, modified3);
	EXPECT_FALSE(to_do_s.at(4).done);

	command3->Revert();

	EXPECT_EQ(ReadFromFile::FileToString(kFilename), kDefaultContent);
}

/**
 * Test if ModifyToDoCommand can throw a runtime_error if the txt file doesn't exist.
 */
TEST_F(ModifyToDoCommandTest, RunTimeException)
{
	const auto command = std::make_shared<ModifyToDoCommand>(0, "...");
	std::filesystem::remove(kFilename);	// delete the txt file before execution
	EXPECT_THROW(command->Execute(), std::runtime_error);
}

/**
 * Test if ModifyToDoCommand can throw an invalid_argument exception if the modification
 *   string contains any '#' symbol.
 */
TEST_F(ModifyToDoCommandTest, InvalidArgumentException)
{
	const auto command = std::make_shared<ModifyToDoCommand>(0, 
		"This message is ## invalid...");
	EXPECT_THROW(command->Execute(), std::invalid_argument);
}
