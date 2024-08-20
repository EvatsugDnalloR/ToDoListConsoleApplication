#include "ModifyToDoCommand.h"

/**
 * Default constructor to initialise {chosen_number_} and {to_do_msg}.
 *
 * @param chosen_number		the chosen index of To_Do message to be modified
 * @param to_do_msg		the message to replace the original To_Do message
 */
ModifyToDoCommand::ModifyToDoCommand(const int& chosen_number, std::string to_do_msg) :
	Command(false),
	chosen_number_(chosen_number),
	to_do_msg_(std::move(to_do_msg))
{
}

/**
 * Copy assignment operator.
 *
 * @param other		reference to other ModifyToDoCommand object
 * @return	{*this}
 */
ModifyToDoCommand& ModifyToDoCommand::operator=(const ModifyToDoCommand& other)
{
	if (this != &other) {
		Command::operator=(other);
		chosen_number_ = other.chosen_number_;
		to_do_msg_ = other.to_do_msg_;
	}
	return *this;
}

/**
 * Move constructor.
 *
 * @param other		reference to the reference to other ModifyToDoCommand object
 */
ModifyToDoCommand::ModifyToDoCommand(ModifyToDoCommand&& other) noexcept
	: Command(std::move(other)),
	  chosen_number_(other.chosen_number_),  // NOLINT(bugprone-use-after-move)
	  to_do_msg_(std::move(other.to_do_msg_))  // NOLINT(bugprone-use-after-move)
{
}

/**
 * Move assignment operator.
 *
 * @param other		reference to the reference to other ModifyToDoCommand object
 * @return	{*this}
 */
ModifyToDoCommand& ModifyToDoCommand::operator=(ModifyToDoCommand&& other) noexcept
{
	if (this != &other) 
	{
		Command::operator=(std::move(other));
		chosen_number_ = other.chosen_number_;  // NOLINT(bugprone-use-after-move)
		to_do_msg_ = std::move(other.to_do_msg_);
	}
	return *this;
}

/**
 * Execute the ModifyToDoCommand and backup the original To_Do message.
 *
 * @pre  {chosen_number_} is in the range of {to_do_s_} vector in
 *   the MainFrame class (cannot be violated due to the checks before
 *   passing in the parameter)
 * @throw runtime_error due to ModifyToDoMsg method
 * @throw invalid_argument due to ModifyToDoMsg method
 * @post  {executed_ == true}
 * @post  the original To_Do message has been replaced by {to_do_msg_}
 * @post  the done boolean of the original To_Do is not modified
 */
void ModifyToDoCommand::Execute()
{
	Command::Execute();

	modified_ = WriteToFile::GetLines(kFilename).at(chosen_number_);

	WriteToFile::ModifyToDoMsg(chosen_number_, to_do_msg_, kFilename);
}

/**
 * Revert the ModifyToDoCommand by restoring the old To_Do message.
 *
 * @pre	 {executed_ == true}
 * @throw runtime_error if the txt file does not exist
 * @post  {executed_ == false}
 * @post  the To_Do message at index {chosen_number_} is restored to {modified}
 */
void ModifyToDoCommand::Revert()
{
	Command::Revert();

	std::vector lines{ WriteToFile::GetLines(kFilename) };

	lines.at(chosen_number_) = modified_;

	WriteToFile::ModifyFile(kFilename, lines);
}
