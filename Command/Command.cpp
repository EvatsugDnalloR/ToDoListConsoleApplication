#include "Command.h"

/**
 * Constructs a command for a given receiver.
 *
 * @param executed  initial execution state
 */
Command::Command(const bool executed) : executed_(executed)
{
}

/**
 * Copy assignment operator.
 *
 * @param other     the reference to the other {Command} object passed in
 * @return  {*this}
 */
Command& Command::operator=(const Command& other)
{
	if (this != &other) 
	{
		executed_ = other.GetExecuted();
	}
	return *this;
}

/**
 * Move constructor.
 *
 * @param other     the reference to the reference of the other {Command} object passed in
 */
Command::Command(Command&& other) noexcept : executed_(other.GetExecuted())
{
	other.SetExecuted(false);
}

/**
 * Move assignment operator.
 *
 * @param other     the reference to the reference of the other {Command} object passed in
 * @return  {*this}
 */
Command& Command::operator=(Command&& other) noexcept
{
	if (this != &other) {
		executed_ = other.GetExecuted();
		other.SetExecuted(false);
	}
	return *this;
}

/**
 * A public getter for the execution state {executed_}.
 *
 * @return  {this->executed_}
 */
bool Command::GetExecuted() const
{
	return executed_;
}

/**
 * A public setter for the execution state {executed_}.
 *
 * @param executed	a boolean indicating the execution state
 */
void Command::SetExecuted(const bool executed)
{
	executed_ = executed;
}

/**
 * Execute the command, will be overridden by a concrete command.
 *
 * @pre {executed_ == false}
 * @throw runtime_error	if {executed_ != false}
 * @post {executed_ == true}
 */
void Command::Execute()
{
	if (executed_)
	{
		throw std::runtime_error("Command is already executed");
	}
	executed_ = true;
}

/**
 * Revert the command, will be overridden by a concrete command.
 *
 * @pre {executed_ == true}
 * @throw runtime_error	if {executed_ != true}
 * @post {executed_ == false}
 */
void Command::Revert()
{
	if (!executed_)
	{
		throw std::runtime_error("Command is not yet executed");
	}
	executed_ = false;
}
