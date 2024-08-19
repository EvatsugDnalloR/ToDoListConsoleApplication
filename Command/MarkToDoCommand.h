#pragma once
#include <vector>
#include "Command.h"
#include "../ToDoList/ReadFromFile.h"
#include "../ToDoList/WriteToFile.h"

class MarkToDoCommand final : public Command
{
	/** The chosen index of To_Do messages to be marked or unmarked.	 */
	std::vector<int> chosen_numbers_{};

public:
	explicit MarkToDoCommand(const std::vector<int>& chosen_numbers);
	~MarkToDoCommand() override = default;

	// Copy constructor
	MarkToDoCommand(const MarkToDoCommand& other) = default;

	// Copy assignment operator
	MarkToDoCommand& operator=(const MarkToDoCommand& other);

	// Move constructor
	MarkToDoCommand(MarkToDoCommand&& other) noexcept;

	// Move assignment operator
	MarkToDoCommand& operator=(MarkToDoCommand&& other) noexcept;

	void Execute() override;

	void Revert() override;
};
