#include "UndoRedo.h"

bool UndoRedo::CanUndo() const
{
	return !undo_stack_.empty();
}

bool UndoRedo::CanRedo() const
{
	return !redo_stack_.empty();
}

void UndoRedo::Did(std::unique_ptr<Command> command)
{
	if (!command->GetExecuted())
	{
		command->Execute();
	}
	undo_stack_.push(std::move(command));
	redo_stack_ = std::stack<std::unique_ptr<Command>>();
}

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
		redo_stack_ = std::stack<std::unique_ptr<Command>>();
	}
}

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



