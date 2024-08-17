#pragma once
#include <stack>
#include <memory>
#include <stdexcept>
#include "Command.h"

class UndoRedo
{
	/** Stack that stores pointer to {Command} object (for polymorphism)
	 * for undo purpose.
	 * Initialised to empty.
	 */
	std::stack<std::unique_ptr<Command>> undo_stack_{};

	/** Stack that stores pointer to {Command} object (for polymorphism)
	 * for redo purpose.
	 * Initialised to empty.
	 */
	std::stack<std::unique_ptr<Command>> redo_stack_{};

public:
	/** Default constructor that do nothing. 	 */
	UndoRedo() = default;

	/**
	 * Check if there's any command that is available to undo.
	 *
	 * @return	{!undo_stack.empty()}
	 */
	[[nodiscard]] auto CanUndo() const -> bool;

	/**
	 * Check if there's any command that is available to redo.
	 *
	 * @return	{!redo_stack.empty()}
	 */
	[[nodiscard]] auto CanRedo() const -> bool;

	/**
	 * Adds given command ti te do-history.
	 * If the command was not yet executed, then it is first executed.
	 *
	 * @param command	the command to incorporate
	 */
	void Did(std::unique_ptr<Command> command);

	/**
	 * Undo the most recent done command, optionally allowing it
	 *   to be redone.
	 *
	 * @param redoable	whether to allow redo
	 */
	void Undo(const bool redoable);

	/** Redo the most recent command.	 */
	void Redo();
};