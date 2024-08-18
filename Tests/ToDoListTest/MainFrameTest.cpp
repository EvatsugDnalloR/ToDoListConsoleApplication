#include <array>
#include "../pch.h"
#include "../../ToDoList/MainFrame.h"

const static std::string kBasePath{ "test_src/main_frame/" };

static MainFrame main_frame;	// static MainFrame object for all tests

/**
 * Test if {TakingMultiParam} can handle the correct integer input in wrong order,
 *		which should be sorted in the vector returned.
 */
TEST(TakingMultiParam, GeneralCase1)
{
	const std::string filename{ "taking_param_1.txt" };
	main_frame.SetToDoS(ReadFromFile::GetToDos(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename))));

	const std::vector<int> result{ main_frame.TakingMultiParam("3, 2, 1") };
	constexpr std::array expected{ 0, 1, 2 };
	for (int i = 0; i < result.size(); i++)
	{
		EXPECT_EQ(expected.at(i), result.at(i));
	}
}

/**
 * Test if {TakingMultiParam} cam handle the spaces inside the user input.
 */
TEST(TakingMultiParam, GeneralCase2)
{
	const std::string filename{ "taking_param_2.txt" };
	main_frame.SetToDoS(ReadFromFile::GetToDos(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename))));

	const std::vector<int> result{ main_frame.TakingMultiParam("1,      3,   4") };
	constexpr std::array expected{ 0, 2, 3 };
	for (int i = 0; i < result.size(); i++)
	{
		EXPECT_EQ(expected.at(i), result.at(i));
	}
}

/**
 * Test if {TakingMultiParam} can throw an exception when the user input contains any
 *	 non-integer element.
 */
TEST(TakingMultiParam, ExceptionCase1)
{
	const std::string filename{ "exception.txt" };
	main_frame.SetToDoS(ReadFromFile::GetToDos(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename))));
	EXPECT_THROW(std::vector<int> result{ main_frame.TakingMultiParam("1e, 3.8") },
		std::invalid_argument);
}

/**
 * Test if {TakingMultiParam} can throw an exception when the user input contains any
 *	 duplicated integers.
 */
TEST(TakingMultiParam, ExceptionCase2)
{
	const std::string filename{ "exception.txt" };
	main_frame.SetToDoS(ReadFromFile::GetToDos(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename))));
	EXPECT_THROW(std::vector<int> result{ main_frame.TakingMultiParam("1,3,3,4") },
		std::invalid_argument);
}

/**
 * Test if {TakingMultiParam} can throw an exception when the user input contains any
 *   integer that is out of the range of {to_do_s_}.
 */
TEST(TakingMultiParam, ExceptionCase3)
{
	const std::string filename{ "exception.txt" };
	main_frame.SetToDoS(ReadFromFile::GetToDos(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename))));
	EXPECT_THROW(std::vector<int> result{ main_frame.TakingMultiParam("1,3,3,100") },
		std::invalid_argument);
}