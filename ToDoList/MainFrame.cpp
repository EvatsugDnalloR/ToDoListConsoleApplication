#include "MainFrame.h"

/**
 * Further development:
 *		TODO: make the output to be printed prettier (especially PrintToDos and PrintOptions)
 *		TODO: add the logic to actually save and exit, otherwise abandon the specification file
 *		TODO: add the UndoRedo feature to the program (perhaps by Command Pattern)
 */


/**
 * The constructors that initialises the three variables of MainFrame class.
 */
MainFrame::MainFrame()
{
	exit_ = false;	// false at default, once true then the program ends

	exit_success_ = true;	// true at default, if quit due to errors then will be set to false

	to_do_s_ = {};	//empty at default, change according to the specification.txt file

	msg_ptr_ = nullptr;	// null at default, will be pointed to any error message if occured
}

/**
 * The main function that should be called to run the whole MainFrame.
 */
void MainFrame::StartApp()
{
	while (!exit_)
	{
		CleanConsole();

		/*
		 * If the {msg_ptr_} is not null, print the extra error message
		 *		and reset the {msg_ptr_} back to null.
		 */
		if (msg_ptr_)
		{
			std::println("{}", *msg_ptr_);
			msg_ptr_ = nullptr;
		}

		PrintToDos();

		PrintOptions();

		HandleUserInput([]	// take the user input and put them all in upper cases
		{
			std::string user_input;
			std::getline(std::cin, user_input);
			std::ranges::transform(user_input, user_input.begin(), ::toupper);
			return user_input;
		}());
	}
}

/**
 * Method that read the specification.txt file and prints the latest
 *		modified version of all ToDos.
 */
void MainFrame::PrintToDos()
{
	/*
	 * Read the string from the specification.txt file,
	 *		initialise all the To_Do object with each line of the string,
	 *		then initialise the {to_do_s_} variable by putting all those
	 *		To_Do object into {to_do_s}.
	 */
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
		}
	}
}

/**
 * A private method that prints all the options available for the user.
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
}

/**
 * A private switch statement that will react accordingly to the user input,
 *		and decide which operation to perform on the current To_Do list.
 * The Delete, MarkAsDone and ModifyMsg operation can be accessed only if
 *		the {to_do_s_} is not empty, i.e. there are at least one To_Do for
 *		the operation to perform on.
 * @pre the {user_input} parameter is in capital (always true due to
 *	   the lambda function to initialise the param when this function is called)
 * @param user_input	self explained...
 */
void MainFrame::HandleUserInput(const std::string& user_input)
{
	switch (user_input[0])	// accessing the first character of {user_input} as a char
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
 * A private method that asks the user to input the To_Do string and
 *		insert it to the specification.txt by calling {WriteToFile::AddToDo}.
 */
void MainFrame::HandleAddToDo()
{
	std::println("Please add your ToDo message:");

	try
	{
		WriteToFile::AddToDo([]
			{	// lambda function to get the string input
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
		exit_success_ = false;	// quit due to fatal error that the file is corrupted
	}
}

/**
 * A private method that asks the user to select the To_Do that
 *		the user want to delete, and delete them by calling {WriteToFile::DeleteToDo}.
 * @pre  {to_do_s} is not empty (cannot be violated dur to the {HandleUserInput} method)
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
		PerformDeletion(to_be_deleted);
	}
}

/**
 * 
 * @param user_input 
 * @return 
 */
std::vector<int> MainFrame::TakingDeleteParam(const std::string& user_input) const
{
	const std::string trimmed_input{[user_input]
	{
		std::string result = user_input;
		std::erase(result, ' ');
		return result;
	}()};

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
 * Auxiliary method that perform the actual deletion of one or multiple To_Do_s selected.
 * Each line number of To_Do message selected is deviated by 1 at first place.
 * With the success deletion of the former To_Do_s, the line number of the
 *		rest of To_Do_s in the {to_be_deleted} vector will be further deviated
 *		by 1 (such as formerly {1, 3, 5}, after the deletion of {1}, it should be
 *		{2, 4} left).
 * @pre  {to_be_deleted} is sorted (cannot be violated due to the TakingDeleteParam function)
 * @param to_be_deleted		the vector that contains all the line number of To_Do_s
 *		that should be deleted
 * @post  all the To_Do_s at the former lines in {to_be_deleted} should be deleted
 */
void MainFrame::PerformDeletion(const std::vector<int>& to_be_deleted)
{
	int deviation{ 1 };
	for (const auto number : to_be_deleted)
	{
		/*
		 * The {invalid_argument} exception from DeleteToDo can be ignored
		 *		since it has already been dealt with {TakingDeleteParam} function.
		 */
		try
		{
			WriteToFile::DeleteToDo(number - deviation, kFilename);
		}
		catch (const std::runtime_error& e)
		{
			std::println("Problem occurs with the specification file...");
			std::println("Details: {}", e.what());
			exit_ = true;
			exit_success_ = false;	// quit due to fatal error that the file is corrupted
			break;
		}
		deviation++;
	}
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
			exit_success_ = false;
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
			exit_success_ = false;
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
 * A public getter of {exit_success_} for the main.cpp to know if
 *		the program quit normally or not.
 * @return	{this.exit_success_}
 */
bool MainFrame::GetExitSuccess() const
{
	return exit_success_;
}