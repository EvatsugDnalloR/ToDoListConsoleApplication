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
	/**
	 * Default constructor to construct {chosen_numbers}.
	 *
	 * @param chosen_numbers	chosen indexes of the To_Do messages to be marked
	 */
	explicit MarkToDoCommand(const std::vector<int>& chosen_numbers);

	/** Default destructor for proper inheritance.	 */
	~MarkToDoCommand() override = default;

	/**
	 * Copy constructor.
	 *
	 * @param other		reference to other MarkToDoCommand object
	 */
	MarkToDoCommand(const MarkToDoCommand& other) = default;

	/**
	 * Copy assignment operator.
	 *
	 * @param other		reference to other MarkToDoCommand object
	 * @return	{*this}
	 */
	MarkToDoCommand& operator=(const MarkToDoCommand& other);

	/**
	 * Move constructor.
	 *
	 * @param other		reference to the reference to other MarkToDoCommand object
	 */
	MarkToDoCommand(MarkToDoCommand&& other) noexcept;

	/**
	 * Move assignment operator.
	 *
	 * @param other		reference to the reference to other MarkToDoCommand object
	 * @return	{*this}
	 */
	MarkToDoCommand& operator=(MarkToDoCommand&& other) noexcept;

	/** Execute the MarkToDoCommand to mark or unmark To_Do_s.	 */
	void Execute() override;

	/**
	 * Revert the MarkToDoCommand by executing MarkToDo method again
	 *   on the same objects.
	 */
	void Revert() override;
};
