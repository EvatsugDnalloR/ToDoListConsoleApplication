#pragma once
#include "Command.h"
#include "ReadFromFile.h"
#include "../ToDoList/WriteToFile.h"

/**
 * The concrete command to Add a To_Do message entered by the user.
 */
class AddToDoCommand final : public Command
{
	/** The user input To_Do message.	 */
	std::string user_input_;

public:
	/**
	 * Construct the user input.
	 *
	 * @param input		the actual input from the user
	 */
	explicit AddToDoCommand(std::string input);

	/** Default destructor for correct inheritance.	 */
	~AddToDoCommand() override = default;

	/**
     * Default copy constructor.
     *
     * @param other		reference to other {AddToDoCommand}object
     */
    AddToDoCommand(const AddToDoCommand& other) = default;

	/**
     * Copy assignment operator.
     *
     * @param other     reference to other {AddToDoCommand}object
     * @return  {*this}
     */
    AddToDoCommand& operator=(const AddToDoCommand& other);

	/**
     * Move constructor.
     *
     * @param other     reference to the reference to other {AddToDoCommand}object
     */
    AddToDoCommand(AddToDoCommand&& other) noexcept;

	/**
     * Move assignment operator.
     *
     * @param other     reference to the reference to other {AddToDoCommand}object
     * @return  {*this}
     */
    AddToDoCommand& operator=(AddToDoCommand&& other) noexcept;

	/** Execute the AddToDo operation.	 */
	void Execute() override;

	/** Revert the AddToDo operation.	 */
	void Revert() override;
};
