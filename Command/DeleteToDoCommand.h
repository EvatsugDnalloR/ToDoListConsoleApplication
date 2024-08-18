#pragma once
#include <map>
#include <vector>
#include "Command.h"

class DeleteToDoCommand final : public Command
{
	std::vector<int> chosen_numbers_{};

	std::map<int, std::string> deleted_todos_{};

public:
	explicit DeleteToDoCommand(const std::vector<int>& chosen_numbers);
	~DeleteToDoCommand() override = default;

	void Execute() override;

	void Revert() override;
};