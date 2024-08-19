#include "ModifyToDoCommand.h"

ModifyToDoCommand::ModifyToDoCommand(const int& chosen_number, std::string to_do_msg) :
	Command(false),
	chosen_number_(chosen_number),
	to_do_msg_(std::move(to_do_msg))
{
}

ModifyToDoCommand& ModifyToDoCommand::operator=(const ModifyToDoCommand& other)
{
	if (this != &other) {
		Command::operator=(other);
		chosen_number_ = other.chosen_number_;
		to_do_msg_ = other.to_do_msg_;
	}
	return *this;
}

ModifyToDoCommand::ModifyToDoCommand(ModifyToDoCommand&& other) noexcept
	: Command(std::move(other)),
	  chosen_number_(other.chosen_number_),  // NOLINT(bugprone-use-after-move)
	  to_do_msg_(std::move(other.to_do_msg_))  // NOLINT(bugprone-use-after-move)
{
}

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

void ModifyToDoCommand::Execute()
{
	Command::Execute();

	modified_ = WriteToFile::GetLines(kFilename).at(chosen_number_);

	WriteToFile::ModifyToDoMsg(chosen_number_, to_do_msg_, kFilename);
}

void ModifyToDoCommand::Revert()
{
	Command::Revert();

	std::vector lines{ WriteToFile::GetLines(kFilename) };

	lines.at(chosen_number_) = modified_;

	WriteToFile::ModifyFile(kFilename, lines);
}
