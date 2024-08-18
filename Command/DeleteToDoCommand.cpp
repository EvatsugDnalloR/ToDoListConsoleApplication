#include "DeleteToDoCommand.h"

DeleteToDoCommand::DeleteToDoCommand(const std::vector<int>& chosen_numbers):
	Command(false),
	chosen_numbers_(chosen_numbers)
{
}

void DeleteToDoCommand::Execute()
{
	Command::Execute();
	
}
