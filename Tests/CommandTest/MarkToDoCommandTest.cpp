#include "CommandTest.h"
#include "../pch.h"
#include "../../Command/MarkToDoCommand.h"
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
class MarkToDoCommandTest : public CommandTest
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
 * Test if MarkToDoCommand can correctly perform the execution with multiple
 *   chosen numbers.
 */
TEST_F(MarkToDoCommandTest, GeneralCase1)
{
	const auto command = std::make_shared<MarkToDoCommand>([]
		{
			const std::vector chosen_numbers{ 1, 2, 3 };
			return chosen_numbers;
		}());

	command->Execute();

	const std::vector to_do_s{ ReadFromFile::GetToDos(ReadFromFile::FileToString(kFilename)) };

	EXPECT_FALSE(to_do_s.at(1).done);
	EXPECT_TRUE(to_do_s.at(2).done);
	EXPECT_FALSE(to_do_s.at(3).done);

	command->Revert();

	EXPECT_EQ(ReadFromFile::FileToString(kFilename), kDefaultContent);
}

/**
 * Another Test if MarkToDoCommand can correctly perform the execution with
 *   multiple chosen numbers.
 */
TEST_F(MarkToDoCommandTest, GeneralCase2)
{
	const auto command = std::make_shared<MarkToDoCommand>([]
		{
			const std::vector chosen_numbers{ 0, 1, 2, 3, 4 };
			return chosen_numbers;
		}());

	command->Execute();

	const std::vector to_do_s{ ReadFromFile::GetToDos(ReadFromFile::FileToString(kFilename)) };

	EXPECT_TRUE(to_do_s.at(0).done);
	EXPECT_FALSE(to_do_s.at(1).done);
	EXPECT_TRUE(to_do_s.at(2).done);
	EXPECT_FALSE(to_do_s.at(3).done);
	EXPECT_TRUE(to_do_s.at(4).done);

	command->Revert();

	EXPECT_EQ(ReadFromFile::FileToString(kFilename), kDefaultContent);
}

/** Test if MarkToDoCommand can throw a runtime_error if the file does not exist. */
TEST_F(MarkToDoCommandTest, ExecutionException)
{
	const auto command = std::make_shared<MarkToDoCommand>([]
		{
			const std::vector to_be_deleted{ 0, 1, 2, 3, 4 };
			return to_be_deleted;
		}());
	std::filesystem::remove(kFilename);	// delete the txt file before execution
	EXPECT_THROW(command->Execute(), std::runtime_error);
}