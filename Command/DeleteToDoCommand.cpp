#include "DeleteToDoCommand.h"

/**
 * Default constructor to construct the {chosen_numbers}.
 *
 * @param chosen_numbers	chosen indexes of the To_Do messages to be deleted
 */
DeleteToDoCommand::DeleteToDoCommand(const std::vector<int>& chosen_numbers):
	Command(false),
	chosen_numbers_(chosen_numbers)
{
}

/**
 * Copy assignment operator.
 *
 * @param other		reference to other DeleteToDoCommand object
 * @return	{*this}
 */
DeleteToDoCommand& DeleteToDoCommand::operator=(const DeleteToDoCommand& other)
{
	if (this != &other) 
	{
		Command::operator=(other);
		chosen_numbers_ = other.chosen_numbers_;
	}
	return *this;
}

/**
 * Move constructor.
 *
 * @param other		reference to the reference of another DeleteToDoCommand object
 */
DeleteToDoCommand::DeleteToDoCommand(DeleteToDoCommand&& other) noexcept
	: Command(std::move(other)),
      chosen_numbers_(std::move(other.chosen_numbers_))  // NOLINT(bugprone-use-after-move)
{
}

/**
 * Move assignment operator.
 *
 * @param other		reference to the reference of another DeleteToDoCommand object
 * @return	{*this}
 */
DeleteToDoCommand& DeleteToDoCommand::operator=(DeleteToDoCommand&& other) noexcept {
	if (this != &other) {
		Command::operator=(std::move(other));
		chosen_numbers_ = std::move(other.chosen_numbers_);  // NOLINT(bugprone-use-after-move)
	}
	return *this;
}

/**
 * Execute the DeleteToDo command and backup the deleted To_Dos.
 * When deleting multiple To_Do lines, with the success deletion of
 *   the former To_Do, the line number of the rest of To_Do_s in the
 *   {chosen_numbers_} vector will be further deviated by 1
 *   (such as formerly {1, 3, 5}, after the deletion of {1}, it should be
 *	 {2, 4} left).
 * Possible invalid_argument exception can be ignored since the precondition
 *   for this exception will not be violated.
 *
 * @pre  for all index in {chosen_numbers}, each one are in the range of {lines}
 *	 (cannot be violated due to the TakingMultiParam method from MainFrame class)
 * @throw runtime_error		due to DeleteToDo method
 * @post {executed_ == true}
 * @post all To_Do_s with the indexes in {chosen_numbers_} should be deleted
 */
void DeleteToDoCommand::Execute()
{
	Command::Execute();

	std::vector lines{ ReadFromFile::GetLines(kFilename) };
	int deviation{};	// initially no deviation
	for (const auto& num : chosen_numbers_)
	{
		// insert the pair of index and message of deleted To_Do
		deleted_todos_.insert({ num, lines.at(num) });

		WriteToFile::DeleteToDo(num - deviation, kFilename);
		deviation++;	// deviated by 1 for any further deletion
	}
}

/**
 * Revert the DeleteToDoCommand by rewrite the deleted To_Dos back.
 *
 * @throw runtime_error if the txt file doesn't exist or can't be opened
 * @post {executed_ == false}
 * @post all the deleted messages in {deleted_todos_} should be inserted
 *	 to the original place in the file according to the indexed stored
 */
void DeleteToDoCommand::Revert()
{
	Command::Revert();

	std::vector lines{ ReadFromFile::GetLines(kFilename) };
	for (const auto& [index, deleted_msg] : deleted_todos_)
	{
		lines.insert(lines.begin() + index, deleted_msg);
	}

	WriteToFile::ModifyFile(kFilename, lines);
}
