#include <vector>
#include "../pch.h"
#include "../../Command/UndoRedo.h"

/**
 * Test the expected behaviour of UndoRedo class when a single command
 *   is inserted and executed.
 */
TEST(UndoRedo, SingleCommand)
{
	UndoRedo undo_redo;

	// initially both stack is empty so nothing to redo or undo
	EXPECT_FALSE(undo_redo.CanUndo());
	EXPECT_FALSE(undo_redo.CanRedo());

	const auto command = std::make_shared<Command>(false);

	undo_redo.Did(command);

	// after did the command 
	EXPECT_TRUE(command->GetExecuted()); // command should be executed
	EXPECT_TRUE(undo_redo.CanUndo());	// there's a command to undo
	EXPECT_FALSE(undo_redo.CanRedo());	// nothing to redo yet

	undo_redo.Undo(true);

	// when a command is undone with redo enabled
	EXPECT_FALSE(command->GetExecuted());
	EXPECT_TRUE(undo_redo.CanRedo());
	EXPECT_FALSE(undo_redo.CanUndo());

	undo_redo.Redo();

	// when a command is redone
	EXPECT_TRUE(command->GetExecuted());
	EXPECT_TRUE(undo_redo.CanUndo());
	EXPECT_FALSE(undo_redo.CanRedo());

	undo_redo.Undo(false);

	// when a command is undone with redo disabled
	EXPECT_FALSE(command->GetExecuted());
	EXPECT_FALSE(undo_redo.CanRedo());
	EXPECT_FALSE(undo_redo.CanUndo());
}

/**
 * Test the expected behaviour of UndoRedo class when multiple commands
 *   are inserted and executed.
 */
TEST(UndoRedo, MultiCommands)
{
	UndoRedo undo_redo;

	std::vector<std::shared_ptr<Command>> commands{};

	for (size_t i{}; i < 10; i++)
	{
		commands.push_back(std::make_shared<Command>(false));
	}

	for (const auto& command : commands)
	{
		undo_redo.Did(command);	// do all commands
	}

	for (const auto& command : commands)
	{
		EXPECT_TRUE(command->GetExecuted());	// all commands should be executed
	}

	// there should be commands to undo, but nothing to redo yet
	EXPECT_TRUE(undo_redo.CanUndo());
	EXPECT_FALSE(undo_redo.CanRedo());

	for (size_t i{}; i < commands.size() - 1; i++)
	{
		undo_redo.Undo(true);	//undo all commands until there's one left
	}

	// still one command left to undo, so can be undone and can be redone
	EXPECT_TRUE(undo_redo.CanRedo());
	EXPECT_TRUE(undo_redo.CanUndo());

	undo_redo.Undo(true);	// undo the last left command

	// nothing to undo but a bunch to redo
	EXPECT_TRUE(undo_redo.CanRedo());
	EXPECT_FALSE(undo_redo.CanUndo());

	for (size_t i{}; i < commands.size(); i++)
	{
		undo_redo.Redo();	// redo all commands
	}

	EXPECT_TRUE(undo_redo.CanUndo());	// a bunch of commands to undo
	EXPECT_FALSE(undo_redo.CanRedo());	// nothing to redo

	for (size_t i{}; i < commands.size(); i++)
	{
		undo_redo.Undo(false);	//undo all commands but with redo disabled
	}

	// nothing to undo and nothing to redo
	EXPECT_FALSE(undo_redo.CanRedo());
	EXPECT_FALSE(undo_redo.CanUndo());
}

/**
 * Test if there's runtime_error thrown when the execution condition of
 *	 command is not satisfied, which will be thrown from the Command class.
 */
TEST(UndoRedoException, CommandIssue)
{
	UndoRedo undo_redo;
	const auto command = std::make_shared<Command>(true);
	undo_redo.Did(command);

	command->Revert();	// put the command to "not executed yet" state

	// expected an exception where tried to undo a command that has not been executed yet
	EXPECT_THROW(undo_redo.Undo(true), std::runtime_error);

	undo_redo.Did(command);
	undo_redo.Undo(true);
	command->Execute();	// put the command to "already executed" state

	// expected an exception where tried to redo a command that has been already executed
	EXPECT_THROW(undo_redo.Redo(), std::runtime_error);
}

/**
 * Test if there's runtime_error thrown if tried to undo or redo when the
 *	 {undo_stack_} or {redo_stack_} is empty.
 */
TEST(UndoRedoException, StackEmpty)
{
	UndoRedo undo_redo;
	const auto command = std::make_shared<Command>(true);
	undo_redo.Did(command);

	// expected an exception where tried to redo while nothing on {redo_stack_}
	EXPECT_THROW(undo_redo.Redo(), std::runtime_error);

	undo_redo.Undo(true);

	// expected an exception where tried to undo while nothing on {undo_stack}
	EXPECT_THROW(undo_redo.Undo(false), std::runtime_error);


	undo_redo.Redo();
	undo_redo.Undo(false);	// redo is disabled, so not pushed to {redo_stack}

	// expected an exception where tried to undo while nothing on {undo_stack}
	EXPECT_THROW(undo_redo.Redo(), std::runtime_error);
}