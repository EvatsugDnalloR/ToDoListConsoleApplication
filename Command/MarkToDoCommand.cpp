#include "MarkToDoCommand.h"

MarkToDoCommand::MarkToDoCommand(const std::vector<int>& chosen_numbers) :
	Command(false), chosen_numbers_(chosen_numbers)
{
}

MarkToDoCommand& MarkToDoCommand::operator=(const MarkToDoCommand& other)
{
	if (this != &other) 
	{
		Command::operator=(other);
		chosen_numbers_ = other.chosen_numbers_;
	}
	return *this;
}

MarkToDoCommand::MarkToDoCommand(MarkToDoCommand&& other) noexcept
	: Command(std::move(other)),
      chosen_numbers_(std::move(other.chosen_numbers_))  // NOLINT(bugprone-use-after-move)
{
}

MarkToDoCommand& MarkToDoCommand::operator=(MarkToDoCommand&& other) noexcept
{
	if (this != &other) 
	{
		Command::operator=(std::move(other));
		chosen_numbers_ = std::move(other.chosen_numbers_);  // NOLINT(bugprone-use-after-move)
	}
	return *this;
}


void MarkToDoCommand::Execute()
{
	Command::Execute();

	for (const auto& num : chosen_numbers_)
	{
		WriteToFile::MarkAsDone(num, kFilename);
	}
}

void MarkToDoCommand::Revert()
{
	Command::Revert();

	for (const auto& num : chosen_numbers_)
	{
		WriteToFile::MarkAsDone(num, kFilename);
	}
}
