#pragma once
#include <stack>
#include <memory>
#include <stdexcept>
#include "Command.h"

class UndoRedo
{
	std::stack<std::unique_ptr<Command>> undo_stack_{};
	std::stack<std::unique_ptr<Command>> redo_stack_{};

public:
	UndoRedo() = default;

	[[nodiscard]] auto CanUndo() const -> bool;

	[[nodiscard]] auto CanRedo() const -> bool;

	void Did(std::unique_ptr<Command> command);

	void Undo(const bool redoable);

	void Redo();
};