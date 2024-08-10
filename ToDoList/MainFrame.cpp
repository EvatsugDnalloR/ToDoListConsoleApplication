#include "MainFrame.h"

//TODO: make the output to be printed prettier
//TODO: test the available methods of MainFrame


/**
 * 
 */
MainFrame::MainFrame()
{
	exit_ = false;

	to_do_s_ = {};

	msg_ptr_ = nullptr;
}

/**
 * 
 */
void MainFrame::StartApp()
{
	while (!exit_)
	{
		CleanConsole();

		/*
		 * 
		 */
		if (msg_ptr_)
		{
			std::println("{}", *msg_ptr_);
			msg_ptr_ = nullptr;
		}

		PrintToDos();

		PrintOptions();

		HandleUserInput([]	//...
		{
			std::string user_input;
			std::getline(std::cin, user_input);
			std::ranges::transform(user_input, user_input.begin(), ::toupper);
			return user_input;
		}());
	}
}

/**
 * 
 */
void MainFrame::PrintToDos()
{
	to_do_s_ = ReadFromFile::GetToDos(ReadFromFile::FileToString(kFilename));

	if (to_do_s_.empty())
	{
		std::println("<<The ToDo list is empty>>");
	}
	else
	{
		int count{1};
		for (const auto& to_do: to_do_s_)
		{
			std::cout << count << ". " << to_do << "\n";
			count++;
			//TODO: make the printed To_Do prettier
		}
	}
}

/**
 * 
 */
void MainFrame::PrintOptions()
{
	using namespace std;
	println("Available options:");
	println("A - Add a ToDo");
	println("D - Delete any ToDo");
	println("F - Mark or unmark any ToDo as done");
	println("M - Modify any ToDo message");
	println("E - GetExit and save");
	//TODO: make the output prettier
}

/**
 * 
 * @param user_input 
 */
void MainFrame::HandleUserInput(const std::string& user_input)
{
	switch (user_input[0])
	{
		case 'A':
			HandleAddToDo();
			break;
		case 'D':
			if (to_do_s_.empty())
			{
				msg_ptr_ = std::make_shared<std::string>("The ToDo List is still empty, "
					"please add some ToDo before deleting anything...");
			}
			else
			{
				HandleDeleteToDo();
			}
			break;
		case 'F':
			if (to_do_s_.empty())
			{
				msg_ptr_ = std::make_shared<std::string>("The ToDo List is still empty, "
					"please add some ToDo before marking anything...");
			}
			else
			{
				HandleMarkAsDone();
			}
			break;
		case 'M':
			if (to_do_s_.empty())
			{
				msg_ptr_ = std::make_shared<std::string>("The ToDo List is still empty, "
					"please add some ToDo before modifying anything...");
			}
			else
			{
				HandleModifyMsg();
			}
			break;
		case 'E':
			ExitAndSave();
			break;
		default:
			msg_ptr_ = std::make_shared<std::string>("Invalid option entered, "
					"please enter the correct option...");
	}
}

/**
 * 
 */
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
	catch (const std::invalid_argument& e)
	{
		msg_ptr_ = std::make_shared<std::string>(std::format(
			"Problem occurs with the entered ToDo message...\n"
			"Details: {}", e.what()));
	}
	catch (const std::runtime_error& e)
	{
		std::println("Problem occurs with the specification file...");
		std::println("Details: {}", e.what());
		exit_ = true;
	}
}

/**
 * 
 */
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
	catch (const std::invalid_argument& e)
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

/**
 * 
 * @param user_input 
 * @return 
 */
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

/**
 * 
 * @param input 
 * @return 
 */
std::string MainFrame::RemoveSpaces(const std::string& input)
{
	std::string result = input;
	std::erase(result, ' ');
	return result;
}

/**
 * 
 */
void MainFrame::HandleMarkAsDone()
{
	std::println("Please enter the number of the ToDo that you want to mark or unmark:");

	int chosen_number{-1};	//...
	bool to_be_continued = true;	//...

	try
	{
		chosen_number = []{
			std::string input;
			std::getline(std::cin, input);
			return std::stoi(input);
		}();
	}
	catch (const std::invalid_argument& e)
	{
		msg_ptr_ = std::make_shared<std::string>(std::format(
			"Problem occurs when entering the number of the ToDo...\n"
			"Details: {}", e.what()));
		to_be_continued = false;
	}

	if (to_be_continued)
	{
		try
		{
			WriteToFile::MarkAsDone(chosen_number - 1, kFilename);
		}
		catch (const std::invalid_argument& e)
		{
			msg_ptr_ = std::make_shared<std::string>(std::format(
				"Problem occurs with the number of the ToDo entered...\n"
				"Details: {}", e.what()));
		}
		catch (const std::runtime_error& e)
		{
			std::println("Problems occurs with the specification file...");
			std::println("Details: {}", e.what());
			exit_ = true;
		}
	}
}

/**
 * 
 */
void MainFrame::HandleModifyMsg()
{
	std::println("Please enter the number of the ToDo that you want to modify:");

	int chosen_number{-1};
	bool to_be_continued = true;

	try
	{
		chosen_number = [] {
			std::string input;
			std::getline(std::cin, input);
			return std::stoi(input);
			}();
	}
	catch (const std::invalid_argument& e)
	{
		msg_ptr_ = std::make_shared<std::string>(std::format(
			"Problem occurs when entering the number of the ToDo...\n"
			"Details: {}", e.what()));
		to_be_continued = false;
	}

	if (to_be_continued)
	{
		CleanConsole();

		std::cout << chosen_number << ". " << to_do_s_.at(chosen_number - 1);
		std::println("");
		std::println("Please enter the message for replacement:");

		std::string todo_msg;
		std::getline(std::cin, todo_msg);

		try
		{
			WriteToFile::ModifyToDoMsg(chosen_number - 1, todo_msg, kFilename);
		}
		catch (const std::invalid_argument& e)
		{
			msg_ptr_ = std::make_shared<std::string>(std::format(
				"Problem occured with the entered parameter...\n"
				"Details: {}", e.what()));
		}
		catch (const std::runtime_error& e)
		{
			std::println("Problems occurs with the specification file...");
			std::println("Details: {}", e.what());
			exit_ = true;
		}
	}
}

/**
 * 
 */
void MainFrame::ExitAndSave()
{
	std::println("Do you want to quit the program and save the specification file ? [y / n]");

	std::string user_input;
	std::getline(std::cin, user_input);

	switch (user_input[0])
	{
		case 'y':
			std::println("Exiting the program...");
			exit_ = true;
			break;
		case 'n':
			msg_ptr_ = std::make_shared<std::string>("Procedure to exit cancelled...");
			break;
		default:
			msg_ptr_ = std::make_shared<std::string>("Invalid option, please enters 'y' or 'n'...");
	}
}


/**
 * 
 */
void MainFrame::CleanConsole()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

/**
 * A public getter of {exit_} variable for unit test purpose.
 * @return	{this.exit_}
 */
bool MainFrame::GetExit() const
{
	return exit_;
}

/**
 * A public getter of {to_do_s} variable for unit test purpose.
 * @return	{this.to_do_s_}
 */
std::vector<ToDo> MainFrame::GetToDoS() const
{
	return to_do_s_;
}

/**
 * A public getter of {msg_ptr_} variable for unit test purpose.
 * @return	{this -> msg_prt_}
 */
std::shared_ptr<std::string> MainFrame::GetMsgPtr() const
{
	return msg_ptr_;
}