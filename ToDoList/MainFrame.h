#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <print>
#include <format>
#include <memory>
#include <set>
#include <sstream>
#include <ranges>
#include <vector>
#include "ReadFromFile.h"
#include "WriteToFile.h"
#include "ToDo.h"

class MainFrame
{
	/** The flag that determines if the program will exit or not.	 */
	bool exit_;

	/** The flag that tells if the program exit normally or not.	 */
	bool exit_success_;

	/** The vector that contains all the ToDos in the specification.txt	 */
	std::vector<ToDo> to_do_s_;

	/** The pointer that points to an extra message that should be printed,
	 *		typically an error message.
	 *	If no error message, it should be a {nullptr}.
	 */
	std::unique_ptr<std::string> msg_ptr_;

public:
	/**
	 * The constructor that should initialise the three variables above.
	 */
	MainFrame();

	/**
	 * The main function that should be called to run the whole MainFrame.
	 */
	void StartApp();

	/**
	 * A private auxiliary method that allows the user to select multiple ToDos
	 *		to delete at once by following a specific format.
	 * @param user_input	the user input that contains one or multiple number of ToDos
	 * @return	a vector of integers that contains all the numbers of ToDos that
	 *		should be deleted.
	 */
	[[nodiscard]] std::vector<int> TakingDeleteParam(const std::string& user_input) const;

	/**
	 * A public getter of {exit_success_} for the main.cpp to know if
	 *		the program quit normally or not.
	 * @return	{this.exit_success_}
	 */
	[[nodiscard]] bool GetExitSuccess() const;

	/**
	 * A public setter for {to_do_s_} variable for unit test purpose
	 * @param to_do_s	a vector of {To_Do} objects to initialise {to_do_s_} variable
	 */
	void SetToDoS(const std::vector<ToDo>& to_do_s);

private:
	/**
	 * A private method that read the specification.txt file and prints
	 *		the latest modified version of all ToDos.
	 */
	void PrintToDos();

	/**
	 * A private method that prints all the options available for the user.
	 */
	static void PrintOptions();

	/**
	 * A private switch statement that will react accordingly to the user input,
	 *		and decide which operation to perform on the current To_Do list.
	 * @param user_input	self explained...
	 */
	void HandleUserInput(const std::string& user_input);

	/**
	 * A private method that asks the user to input the To_Do string and
	 *		insert it to the specification.txt by calling {WriteToFile::AddToDo}.
	 */
	void HandleAddToDo();

	/**
	 * A private method that asks the user to select the To_Do that
	 *		the user want to delete, and delete them by calling {WriteToFile::DeleteToDo}.
	 */
	void HandleDeleteToDo();

	/**
	 * A private auxiliary method that perform the actual deletion of
	 *		one or multiple To_Do_s selected.
	 * @param to_be_deleted 
	 */
	void PerformDeletion(const std::vector<int>& to_be_deleted);

	/**
	 * A private method that ask the user to select one To_Do, and will
	 *		mark that To_Do as done or undone accordingly by calling
	 *		{WriteToFile::MarkAsDone}.
	 */
	void HandleMarkAsDone();

	/**
	 * A private method that ask the user to select one To_Do, and also
	 *		to enter the message that the user want to replace with, then
	 *		call {WriteToFile::ModifyToDoMsg} to complete the operation.
	 */
	void HandleModifyMsg();

	/**
	 * A private method that asks if the user want to exit or not, if so then
	 *		quit the program.
	 */
	void ExitAndSave();

	/**
	 * A private static method that simply clean the output of the console
	 *		on all platforms.
	 */
	static void CleanConsole();
};