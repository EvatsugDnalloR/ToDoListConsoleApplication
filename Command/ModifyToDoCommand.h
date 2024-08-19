#pragma once
#include <vector>
#include "Command.h"
#include "../ToDoList/ReadFromFile.h"
#include "../ToDoList/WriteToFile.h"

class ModifyToDoCommand final : public Command
{
	int chosen_number_{};

	std::string to_do_msg_{};

	std::string modified_{};

public:
	explicit ModifyToDoCommand(const int& chosen_number, std::string to_do_msg);
	~ModifyToDoCommand() override = default;

	// Copy constructor
	ModifyToDoCommand(const ModifyToDoCommand& other) = default;

	// Copy assignment operator
	ModifyToDoCommand& operator=(const ModifyToDoCommand& other);

	// Move constructor
	ModifyToDoCommand(ModifyToDoCommand&& other) noexcept;

	// Move assignment operator
	ModifyToDoCommand& operator=(ModifyToDoCommand&& other) noexcept;

	void Execute() override;

	void Revert() override;
};