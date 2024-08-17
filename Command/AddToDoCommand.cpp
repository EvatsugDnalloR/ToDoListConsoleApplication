#include "AddToDoCommand.h"

AddToDoCommand::AddToDoCommand(std::string input): Command(false), user_input_(std::move(input))
{
}

AddToDoCommand& AddToDoCommand::operator=(const AddToDoCommand& other)
{
	if (this != &other) 
	{
		Command::operator=(other);
		user_input_ = other.user_input_;
	}
	return *this;
}

AddToDoCommand::AddToDoCommand(AddToDoCommand&& other) noexcept : Command(std::move(other)),
	user_input_(std::move(other.user_input_))  // NOLINT(bugprone-use-after-move)
{
}

AddToDoCommand& AddToDoCommand::operator=(AddToDoCommand&& other) noexcept
{
	if (this != &other) {
		Command::operator=(std::move(other));
		user_input_ = std::move(other.user_input_);  // NOLINT(bugprone-use-after-move)
	}
	return *this;
}


void AddToDoCommand::Execute()
{
	Command::Execute();
	WriteToFile::AddToDo(user_input_, kFilename);
}

void AddToDoCommand::Revert()
{
	Command::Revert();
	std::vector lines{ WriteToFile::GetLines(kFilename) };
	lines.pop_back();
	WriteToFile::ModifyFile(kFilename, lines);
}
