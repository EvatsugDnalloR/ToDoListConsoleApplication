#include "MarkToDoCommand.h"

/**
 * Default constructor to construct {chosen_numbers}.
 *
 * @param chosen_numbers	chosen indexes of the To_Do messages to be marked
 */
MarkToDoCommand::MarkToDoCommand(const std::vector<int>& chosen_numbers) :
	Command(false), chosen_numbers_(chosen_numbers)
{
}

/**
 * Copy assignment operator.
 *
 * @param other		reference to other MarkToDoCommand object
 * @return	{*this}
 */
MarkToDoCommand& MarkToDoCommand::operator=(const MarkToDoCommand& other)
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
 * @param other		reference to the reference to other MarkToDoCommand object
 */
MarkToDoCommand::MarkToDoCommand(MarkToDoCommand&& other) noexcept
	: Command(std::move(other)),
      chosen_numbers_(std::move(other.chosen_numbers_))  // NOLINT(bugprone-use-after-move)
{
}

/**
 * Move assignment operator.
 *
 * @param other		reference to the reference to other MarkToDoCommand object
 * @return	{*this}
 */
MarkToDoCommand& MarkToDoCommand::operator=(MarkToDoCommand&& other) noexcept
{
	if (this != &other) 
	{
		Command::operator=(std::move(other));
		chosen_numbers_ = std::move(other.chosen_numbers_);  // NOLINT(bugprone-use-after-move)
	}
	return *this;
}


/**
 * Execute the MarkToDoCommand to mark or unmark To_Do_s.
 *
 * @pre  for all num in {chosen_numbers_}, num are in the range of {to_do_s_} vector
 *   in the MainFrame class (cannot be violated due to TakingMultiParam method)
 * @throw runtime_error	due to MarkAsDone method
 * @post  {executed_ == true}
 * @post  all the To_Do_s at the chosen_numbers_ index have been marked or unmarked accordingly
 */
void MarkToDoCommand::Execute()
{
	Command::Execute();

	for (const auto& num : chosen_numbers_)
	{
		WriteToFile::MarkAsDone(num, kFilename);
	}
}

/**
 * Revert the MarkToDoCommand by executing MarkToDo method again
 *   on the same objects.
 *
 *	 @pre  {executed_ == true}
 *	 @throw runtime_error due to MarkAsDone method
 *	 @post  {executed == false}
 *	 @post  all the To_Do_s that have been marked or unmarked are restored to
 *	   the original state of [ Done ] or [ ]
 */
void MarkToDoCommand::Revert()
{
	Command::Revert();

	for (const auto& num : chosen_numbers_)
	{
		WriteToFile::MarkAsDone(num, kFilename);
	}
}
