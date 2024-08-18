#pragma once
#include <map>
#include <vector>
#include "Command.h"
#include "../ToDoList/ReadFromFile.h"
#include "../ToDoList/WriteToFile.h"

class DeleteToDoCommand final : public Command
{
	std::vector<int> chosen_numbers_{};

	std::map<int, std::string> deleted_todos_{};

public:
	explicit DeleteToDoCommand(const std::vector<int>& chosen_numbers);
	~DeleteToDoCommand() override = default;

	// Copy constructor
	DeleteToDoCommand(const DeleteToDoCommand& other) = default;

	// Copy assignment operator
	DeleteToDoCommand& operator=(const DeleteToDoCommand& other);

	// Move constructor
	DeleteToDoCommand(DeleteToDoCommand&& other) noexcept;

	// Move assignment operator
	DeleteToDoCommand& operator=(DeleteToDoCommand&& other) noexcept;

	void Execute() override;

	void Revert() override;
};