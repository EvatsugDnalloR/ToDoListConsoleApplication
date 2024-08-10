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

	/** The vector that contains all the ToDos in the specification.txt	 */
	std::vector<ToDo> to_do_s_;

	/** The pointer that points to an extra message that should be printed,
	 *		typically an error message.
	 *	If no error message, it should be a {nullptr}.
	 */
	std::shared_ptr<std::string> msg_ptr_;

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
	 * A public getter of {exit_} variable for unit test purpose.
	 * @return	{this.exit_}
	 */
	[[nodiscard]] bool GetExit() const;

	/**
	 * A public getter of {to_do_s} variable for unit test purpose.
	 * @return	{this.to_do_s_}
	 */
	[[nodiscard]] std::vector<ToDo> GetToDoS() const;

	/**
	 * A public getter of {msg_ptr_} variable for unit test purpose.
	 * @return	{this -> msg_prt_}
	 */
	[[nodiscard]] std::shared_ptr<std::string> GetMsgPtr() const;

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
	 *		and decide which operation to perform on the current ToDo list.
	 * @param user_input	self explained...
	 */
	void HandleUserInput(const std::string& user_input);

	/**
	 * A private method that asks the user to input the ToDo string and
	 *		insert it to the specification.txt by calling {WriteToFile::AddToDo}.
	 */
	void HandleAddToDo();

	/**
	 * A private method that asks the user to select the ToDo that
	 *		the user want to delete, and delete them by calling {WriteToFile::DeleteToDo}.
	 */
	void HandleDeleteToDo();

	/**
	 * A private auxiliary method that allows the user to select multiple ToDos
	 *		to delete at once by following a specific format.
	 * @param user_input	the user input that contains one or multiple number of ToDos
	 * @return	a vector of integers that contains all the numbers of ToDos that
	 *		should be deleted.
	 */
	[[nodiscard]] std::vector<int> TakingDeleteParam(const std::string& user_input) const;

	/**
	 * A private static auxiliary method that removes all the spaces of the user input
	 *		to ease the format checking of the {TakingDeleteParam} method.
	 * @param input		the same as in the param above
	 * @return	the same string as {input} but without any spaces
	 */
	static std::string RemoveSpaces(const std::string& input);

	/**
	 * A private method 
	 */
	void HandleMarkAsDone();

	/**
	 * 
	 */
	void HandleModifyMsg();

	/**
	 * 
	 */
	void ExitAndSave();

	/**
	 * 
	 */
	static void CleanConsole();
};