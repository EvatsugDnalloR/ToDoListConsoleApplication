#include <algorithm>
#include <iostream>
#include <print>

#include <memory>
#include <set>
#include <sstream>

#include "MainFrame.h"
#include "ReadFromFile.h"
#include "WriteToFile.h"

MainFrame::MainFrame()
{
	exit_ = false;

	to_do_s_ = {};

	msg_ptr_ = nullptr;
}


void MainFrame::StartApp()
{
	while (!exit_)
	{
		//TODO: clear all the existing output of the terminal

		if (!msg_ptr_)
		{
			std::println(*msg_ptr_);
			msg_ptr_ = nullptr;
		}

		PrintToDos();

		PrintOptions();

		HandleUserInput([]
		{
			std::string user_input;
			std::getline(std::cin, user_input);
			std::ranges::transform(user_input, user_input.begin(), ::toupper);
			return user_input;
		}());
	}
}

void MainFrame::PrintToDos()
{
	to_do_s_ = ReadFromFile::GetToDos(kFilename);

	if (to_do_s_.empty())
	{
		std::println("<<The ToDo list is still empty>>");
	}
	else
	{
		int count{1};
		for (auto to_do: to_do_s_)
		{
			std::println("{}. {}", count, to_do);
			count++;
			//TODO: make the printed _ToDo_ prettier
		}
	}
}

void MainFrame::PrintOptions()
{
	using namespace std;
	println("Available options:");
	println("A - Add a ToDo");
	println("D - Delete any ToDo");
	println("F - Mark or unmark any ToDo as done");
	println("M - Modify any ToDo message");
	println("E - Exit and save");
	//TODO: make the output prettier
}

void MainFrame::HandleUserInput(const std::string& user_input)
{
	switch (user_input[0])
	{
		case "A":
			HandleAddToDo();
			break;
		case "D":
			HandleDeleteToDo();
			break;
		case "F":
			HandleMarkAsDone();
			break;
		case "M":
			HandleModifyMsg();
			break;
		default:
			//TODO: implement default action
			break;
	}
}

void MainFrame::HandleAddToDo()
{
	std::println("Please add your ToDo message:");

	try
	{
		WriteToFile::AddToDo([]
			{
				std::string user_input;
				std::getline(std::cin, user_input);
				return user_input;
			}(),
				kFilename);
	}
	catch (std::invalid_argument& e)
	{
		msg_ptr_ = std::make_shared<std::string>(std::format(
			"Problem occurs with the entered ToDo message...\n"
			"Details: {}", e.what()));
	}
	catch (std::runtime_error& e)
	{
		std::println("Problem occurs with the specification file...");
		std::println("Details: {}", e.what());
		exit_ = true;
	}

}

void MainFrame::HandleDeleteToDo()
{
	std::println("Please enter the numbers of the ToDos that you want to delete:");
	std::println("(multiple numbers are possible, separate the number by a comma");
	std::println("(example: '1,3,4,5' , which will delete the first, third, fourth and the fifth ToDos ))");

	std::vector<int> to_be_deleted;
	bool to_be_continued = true;

	try
	{
		to_be_deleted = TakingDeleteParam([]
			{
				std::string user_input;
				std::getline(std::cin, user_input);
				return user_input;
			}());
	}
	catch (std::invalid_argument& e)
	{
		msg_ptr_ = std::make_shared<std::string>(std::format(
			"Problem occurs with the numbers of ToDo selected..."
			"Details: {}", e.what()));
		to_be_continued = false;
	}

	if (to_be_continued)
	{
		int deviation{ 1 };
		for (const auto number : to_be_deleted)
		{
			WriteToFile::DeleteToDo(number - deviation, kFilename);
			deviation++;
		}
	}
}

std::vector<int> MainFrame::TakingDeleteParam(const std::string& user_input) const
{
	const std::string trimmed_input{RemoveSpaces(user_input)};

	std::stringstream ss(trimmed_input);
	std::vector<int> numbers;
	std::set<int> unique_numbers;
	std::string token;

	while (std::getline(ss, token, ','))
	{
		if (!std::ranges::all_of(token, ::isdigit)) {
			throw std::invalid_argument("Invalid input: " + token);
		}

		const int number = std::stoi(token);

		if (!unique_numbers.insert(number).second) {
			throw std::invalid_argument("Duplicate number found: " + token);
		}

		numbers.push_back(number);
	}

	std::ranges::sort(numbers);

	if (numbers.front() < 1 || numbers.back() > to_do_s_.size())
	{
		throw std::invalid_argument("Some selected numbers doesn't exists, please choose from the list.");
	}

	return numbers;
}

std::string MainFrame::RemoveSpaces(const std::string& input)
{
	std::string result = input;
	std::erase(result, ' ');
	return result;
}

void MainFrame::HandleMarkAsDone()
{
	std::println("Please enter the number of the ToDo that you want to modify:");


}


