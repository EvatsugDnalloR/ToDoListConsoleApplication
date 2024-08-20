#pragma once
#include <vector>
#include "Command.h"
#include "../ToDoList/ReadFromFile.h"
#include "../ToDoList/WriteToFile.h"

class ModifyToDoCommand final : public Command
{
	/** The chosen index of To_Do message to be modified.	 */
	int chosen_number_{};

	/** The message to replace the original To_Do message.	 */
	std::string to_do_msg_{};

	/**
	 * The old To_Do message that is replaced by {to_do_msg}.
	 * Should be initialised during execution of modification.
	 */
	std::string modified_{};

public:
	/**
	 * Default constructor to initialise {chosen_number_} and {to_do_msg}.
	 *
	 * @param chosen_number		the chosen index of To_Do message to be modified
	 * @param to_do_msg		the message to replace the original To_Do message
	 */
	explicit ModifyToDoCommand(const int& chosen_number, std::string to_do_msg);

	/** Default destructor for proper inheritance.	 */
	~ModifyToDoCommand() override = default;

	/**
	 * Copy constructor.
	 *
	 * @param other		reference to other ModifyToDoCommand object
	 */
	ModifyToDoCommand(const ModifyToDoCommand& other) = default;

	/**
	 * Copy assignment operator.
	 *
	 * @param other		reference to other ModifyToDoCommand object
	 * @return	{*this}
	 */
	ModifyToDoCommand& operator=(const ModifyToDoCommand& other);

	/**
	 * Move constructor.
	 *
	 * @param other		reference to the reference to other ModifyToDoCommand object
	 */
	ModifyToDoCommand(ModifyToDoCommand&& other) noexcept;

	/**
	 * Move assignment operator.
	 *
	 * @param other		reference to the reference to other ModifyToDoCommand object
	 * @return	{*this}
	 */
	ModifyToDoCommand& operator=(ModifyToDoCommand&& other) noexcept;

	/** Execute the ModifyToDoCommand and backup the original To_Do message.	 */
	void Execute() override;

	/** Revert the ModifyToDoCommand by restoring the old To_Do message.	 */
	void Revert() override;
};