#include "UndoRedo.h"

/**
 * Check if there's any command that is available to undo.
 *
 * @return	{!undo_stack.empty()}
 */
bool UndoRedo::CanUndo() const
{
	return !undo_stack_.empty();
}

/**
 * Check if there's any command that is available to redo.
 *
 * @return	{!redo_stack.empty()}
 */
bool UndoRedo::CanRedo() const
{
	return !redo_stack_.empty();
}

/**
 * Adds given command to the do-history.
 * If the command was not yet executed, then it is first executed.
 * Redo stack will be cleared.
 *
 * @param command	the command to incorporate
 * @post {command->GetExecuted() == true}
 * @post {redo_stack_.empty() == true}
 */
void UndoRedo::Did(std::shared_ptr<Command> command)
{
	if (!command->GetExecuted())
	{
		command->Execute();
	}

	undo_stack_.push(std::move(command));

	// assign a new empty stack for {redo_stack_} to clear it
	redo_stack_ = std::stack<std::shared_ptr<Command>>();
}

/**
 * Undo the most recent done command, optionally allowing it
 *   to be redone.
 *
 * @param redoable	whether to allow redo
 * @pre {CanUndo() == true}
 * @throw runtime_error	if {CanUndo() != true}
 * @post {command->GetExecuted() == false}
 */
void UndoRedo::Undo(const bool redoable)
{
	if (!CanUndo())
	{
		throw std::runtime_error("Nothing to undo");
	}
	auto command = std::move(undo_stack_.top());
	undo_stack_.pop();
	command->Revert();
	if (redoable)
	{
		redo_stack_.push(std::move(command));
	}
	else
	{
		redo_stack_ = std::stack<std::shared_ptr<Command>>();
	}
}

/**
 * Redo the most recent command.
 *
 * @pre {CanRedo() == true}
 * @throw runtime_error	if {CanRedo() != true}
 * @post {command->GetExecuted() == true}
 */
void UndoRedo::Redo()
{
	if (!CanRedo())
	{
		throw std::runtime_error("Nothing to redo");
	}
	auto command = std::move(redo_stack_.top());
	redo_stack_.pop();
	command->Execute();
	undo_stack_.push(std::move(command));
}
