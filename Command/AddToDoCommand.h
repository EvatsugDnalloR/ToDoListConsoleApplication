#pragma once
#include "Command.h"
#include "ReadFromFile.h"
#include "../ToDoList/WriteToFile.h"

class AddToDoCommand final : public Command
{
	std::string user_input_;

public:
	explicit AddToDoCommand(std::string input);
	~AddToDoCommand() override = default;

    // Copy constructor
    AddToDoCommand(const AddToDoCommand& other) = default;

    // Copy assignment operator
    AddToDoCommand& operator=(const AddToDoCommand& other);

    // Move constructor
    AddToDoCommand(AddToDoCommand&& other) noexcept;

    // Move assignment operator
    AddToDoCommand& operator=(AddToDoCommand&& other) noexcept;

	void Execute() override;

	void Revert() override;
};
