#include "AddToDoCommand.h"

/**
 * Construct the user input.
 *
 * @param input		the actual input from the user
 */
AddToDoCommand::AddToDoCommand(std::string input): Command(false), user_input_(std::move(input))
{
}

/**
 * Copy assignment operator.
 *
 * @param other     reference to other {AddToDoCommand}object
 * @return  {*this}
 */
AddToDoCommand& AddToDoCommand::operator=(const AddToDoCommand& other)
{
	if (this != &other) 
	{
		Command::operator=(other);
		user_input_ = other.user_input_;
	}
	return *this;
}

/**
 * Move constructor.
 *
 * @param other     reference to the reference to other {AddToDoCommand}object
 */
AddToDoCommand::AddToDoCommand(AddToDoCommand&& other) noexcept : Command(std::move(other)),
	user_input_(std::move(other.user_input_))  // NOLINT(bugprone-use-after-move)
	// first {std::move} move the Command part of {other}, second move the user_input_
{
}

/**
 * Move assignment operator.
 *
 * @param other     reference to the reference to other {AddToDoCommand}object
 * @return  {*this}
 */
AddToDoCommand& AddToDoCommand::operator=(AddToDoCommand&& other) noexcept
{
	if (this != &other) {
		Command::operator=(std::move(other));
		user_input_ = std::move(other.user_input_);  // NOLINT(bugprone-use-after-move)
		// first {std::move} move the Command part of {other}, second move the user_input_
	}
	return *this;
}

/**
 * Execute the AddToDo operation.
 *
 * @throw invalid_argument	due to AddToDo method
 * @throw runtime_error	due to AddToDo method
 */
void AddToDoCommand::Execute()
{
	Command::Execute();
	WriteToFile::AddToDo(user_input_, kFilename);
}

/**
 * Revert the AddToDo operation.
 *
 * @throw runtime_error	if the {filename} txt cannot be opened correctly
 */
void AddToDoCommand::Revert()
{
	Command::Revert();
	std::vector lines{ WriteToFile::GetLines(kFilename) };
	//delete the last element of all lines, which should be the last added To_Do
	lines.pop_back();
	WriteToFile::ModifyFile(kFilename, lines);
}
