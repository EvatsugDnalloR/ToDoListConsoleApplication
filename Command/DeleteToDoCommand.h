#pragma once
#include <map>
#include <vector>
#include "Command.h"
#include "../ToDoList/ReadFromFile.h"
#include "../ToDoList/WriteToFile.h"

class DeleteToDoCommand final : public Command
{
	/** The chosen index of To_Do messages to be deleted.	 */
	std::vector<int> chosen_numbers_{};

	/**
	 * The map storing the original index and the To_Do messages deleted.
	 * Should be initialised during execution of deletion.
	 */
	std::map<int, std::string> deleted_todos_{};

public:
	/**
	 * Default constructor to construct the {chosen_numbers}.
	 *
	 * @param chosen_numbers	chosen indexes of the To_Do messages to be deleted
	 */
	explicit DeleteToDoCommand(const std::vector<int>& chosen_numbers);

	/** Default destructor for proper inheritance.	 */
	~DeleteToDoCommand() override = default;

	/**
	 * Copy constructor.
	 *
	 * @param other		reference to other DeleteToDoCommand object
	 */
	DeleteToDoCommand(const DeleteToDoCommand& other) = default;

	/**
	 * Copy assignment operator.
	 *
	 * @param other		reference to other DeleteToDoCommand object
	 * @return	{*this}
	 */
	DeleteToDoCommand& operator=(const DeleteToDoCommand& other);

	/**
	 * Move constructor.
	 *
	 * @param other		reference to the reference of another DeleteToDoCommand object
	 */
	DeleteToDoCommand(DeleteToDoCommand&& other) noexcept;

	/**
	 * Move assignment operator.
	 *
	 * @param other		reference to the reference of another DeleteToDoCommand object
	 * @return	{*this}
	 */
	DeleteToDoCommand& operator=(DeleteToDoCommand&& other) noexcept;

	/** Execute the DeleteToDo command and backup the deleted To_Dos.	 */
	void Execute() override;

	/** Revert the DeleteToDoCommand by rewrite the deleted To_Dos back.	 */
	void Revert() override;
};