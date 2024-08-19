#include <memory>
#include "CommandTest.h"
#include "../pch.h"
#include "../../Command/DeleteToDoCommand.h"

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
class DeleteToDoCommandTest : public CommandTest
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
 * Test if DeleteToDoCommand can properly delete a single To_Do message,
 *   and also revert it.
 */
TEST_F(DeleteToDoCommandTest, SingleDeletion)
{
	const auto command = std::make_shared<DeleteToDoCommand>([]
		{
			const std::vector to_be_deleted{ 1 };
			return to_be_deleted;
		}());

	command->Execute();
	EXPECT_EQ(ReadFromFile::FileToString(kFilename),
		"This is a first message.#0\n"
		"The third one .,.,., #0\n"
		"The fourth one ofc,,,#1\n"
		"Gonna need some fifth one.#0\n");

	command->Revert();
	EXPECT_EQ(ReadFromFile::FileToString(kFilename), kDefaultContent);
}

/**
 * Test if DeleteToDoCommand can properly delete multiple To_Do messages,
 *   and also revert all of them.
 */
TEST_F(DeleteToDoCommandTest, MultiDeletion)
{
	const auto command = std::make_shared<DeleteToDoCommand>([]
		{
			const std::vector to_be_deleted{ 0, 2, 4 };
			return to_be_deleted;
		}());

	command->Execute();
	EXPECT_EQ(ReadFromFile::FileToString(kFilename),
		"This is a second one...#1\n"
		"The fourth one ofc,,,#1\n");

	command->Revert();
	EXPECT_EQ(ReadFromFile::FileToString(kFilename), kDefaultContent);
}

/** Test if DeleteToDoCommand can throw a runtime_error if the file does not exist. */
TEST_F(DeleteToDoCommandTest, ExecuteException)
{
	const auto command = std::make_shared<DeleteToDoCommand>([]
		{
			const std::vector to_be_deleted{ 0, 1, 2, 3, 4 };
			return to_be_deleted;
		}());
	std::filesystem::remove(kFilename);	// delete the txt file before execution
	EXPECT_THROW(command->Execute(), std::runtime_error);
}