#include <array>
#include "pch.h"
#include "../ToDoList/MainFrame.h"

const static std::string kBasePath{ "test_src/main_frame/" };

TEST(TakingDeleteParam, GeneralCase1)
{
	MainFrame main_frame;
	const std::string filename{ "taking_param_1.txt" };
	main_frame.SetToDoS(ReadFromFile::GetToDos(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename))));

	const std::vector<int> result{ main_frame.TakingDeleteParam("3, 2, 1") };
	constexpr std::array expected{ 1, 2, 3 };
	for (int i = 0; i < result.size(); i++)
	{
		EXPECT_EQ(expected.at(i), result.at(i));
	}
}

TEST(TakingDeleteParam, GeneralCase2)
{
	MainFrame main_frame;
	const std::string filename{ "taking_param_2.txt" };
	main_frame.SetToDoS(ReadFromFile::GetToDos(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename))));

	const std::vector<int> result{ main_frame.TakingDeleteParam("1,      3,   4") };
	constexpr std::array expected{ 1, 3, 4 };
	for (int i = 0; i < result.size(); i++)
	{
		EXPECT_EQ(expected.at(i), result.at(i));
	}
}

TEST(TakingDeleteParam, ExceptionCase1)
{
	MainFrame main_frame;
	const std::string filename{ "exception.txt" };
	main_frame.SetToDoS(ReadFromFile::GetToDos(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename))));
	EXPECT_THROW(std::vector<int> result{ main_frame.TakingDeleteParam("1e, ddd3") },
		std::invalid_argument);
}

TEST(TakingDeleteParam, ExceptionCase2)
{
	MainFrame main_frame;
	const std::string filename{ "exception.txt" };
	main_frame.SetToDoS(ReadFromFile::GetToDos(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename))));
	EXPECT_THROW(std::vector<int> result{ main_frame.TakingDeleteParam("1,3,3,4") },
		std::invalid_argument);
}

TEST(TakingDeleteParam, ExceptionCase3)
{
	MainFrame main_frame;
	const std::string filename{ "exception.txt" };
	main_frame.SetToDoS(ReadFromFile::GetToDos(ReadFromFile::FileToString(
		std::format("{}{}", kBasePath, filename))));
	EXPECT_THROW(std::vector<int> result{ main_frame.TakingDeleteParam("1,3,3,100") },
		std::invalid_argument);
}