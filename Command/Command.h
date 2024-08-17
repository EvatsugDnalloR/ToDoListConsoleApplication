#pragma once
#include <stdexcept>

class Command
{
	/** To indicate the execution state.	 */
	bool executed_;

public:
	/**
	 * Constructs a command for a given receiver.
	 *
	 * @param executed  initial execution state
	 */
	explicit Command(const bool executed);

	/** Default destructor made in virtual for inheritance.     */
    virtual ~Command() = default;

    
	/**
     * Copy constructor.
     *
     * @param other		the reference to the other {Command} object passed in
     */
    Command(const Command& other) = default;

	/**
     * Copy assignment operator.
     *
     * @param other     the reference to the other {Command} object passed in
     * @return  {*this}
     */
    Command& operator=(const Command& other);

	/**
     * Move constructor.
     *
     * @param other     the reference to the reference of the other {Command} object passed in
     */
    Command(Command&& other) noexcept;

	/**
     * Move assignment operator.
     *
     * @param other     the reference to the reference of the other {Command} object passed in
     * @return  {*this}
     */
    Command& operator=(Command&& other) noexcept;

	/**
	 * A public getter for the execution state {executed_}.
	 *
	 * @return  {this->executed_}
	 */
	[[nodiscard]] bool GetExecuted() const;

	/** Execute the command, will be overridden by a concrete command.	 */
	virtual void Execute();

	/** Revert the command, will be overridden by a concrete command.	 */
	virtual void Revert();
};
