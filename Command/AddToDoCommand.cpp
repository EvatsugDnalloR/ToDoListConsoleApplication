#include "AddToDoCommand.h"

/**
 * A public setter of {user_input_} variable for unit test purpose.
 *
 * @param user_input	user input string
 */
void AddToDoCommand::SetUserInput(const std::string& user_input)
{
	user_input_ = user_input;
}

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
 * @post {executed_ == true}
 * @post {user_input_} should be inserted to the back of the txt file
 */
void AddToDoCommand::Execute()
{
	Command::Execute();
	WriteToFile::AddToDo(user_input_, kFilename);
}

/**
 * Revert the AddToDo operation by deleting the last line of
 *   the txt file, which should be the most recent inserted message.
 *
 * @throw runtime_error	if the txt file doesn't exist
 * @throw runtime_error if the txt file cannot be opened correctly
 * @post {executed_ == false}
 * @post  the last line of {user_input_} should be deleted
 */
void AddToDoCommand::Revert()
{
	Command::Revert();
	std::vector lines{ WriteToFile::GetLines(kFilename) };

	//delete the last element of all lines, which should be the last added To_Do
	lines.pop_back();
	WriteToFile::ModifyFile(kFilename, lines);
}
