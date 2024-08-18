#include "DeleteToDoCommand.h"

DeleteToDoCommand::DeleteToDoCommand(const std::vector<int>& chosen_numbers):
	Command(false),
	chosen_numbers_(chosen_numbers)
{
}

DeleteToDoCommand& DeleteToDoCommand::operator=(const DeleteToDoCommand& other)
{
	if (this != &other) 
	{
		Command::operator=(other);
		chosen_numbers_ = other.chosen_numbers_;
		deleted_todos_ = other.deleted_todos_;
	}
	return *this;
}

DeleteToDoCommand::DeleteToDoCommand(DeleteToDoCommand&& other) noexcept
	: Command(std::move(other)),
      chosen_numbers_(std::move(other.chosen_numbers_)),  // NOLINT(bugprone-use-after-move)
      deleted_todos_(std::move(other.deleted_todos_))  // NOLINT(bugprone-use-after-move)
{
}

DeleteToDoCommand& DeleteToDoCommand::operator=(DeleteToDoCommand&& other) noexcept {
	if (this != &other) {
		Command::operator=(std::move(other));
		chosen_numbers_ = std::move(other.chosen_numbers_);  // NOLINT(bugprone-use-after-move)
		deleted_todos_ = std::move(other.deleted_todos_);
	}
	return *this;
}

void DeleteToDoCommand::Execute()
{
	Command::Execute();
	std::vector lines{ WriteToFile::GetLines(kFilename) };
	int deviation{};
	for (const auto& num : chosen_numbers_)
	{
		deleted_todos_.insert({ num, lines.at(num) });
		WriteToFile::DeleteToDo(num - deviation, kFilename);
		deviation++;
	}
}

void DeleteToDoCommand::Revert()
{
	Command::Revert();
	std::vector lines{ WriteToFile::GetLines(kFilename) };

	for (const auto& [index, msg] : deleted_todos_)
	{
		lines.insert(lines.begin() + index, msg);
	}

	WriteToFile::ModifyFile(kFilename, lines);
}
