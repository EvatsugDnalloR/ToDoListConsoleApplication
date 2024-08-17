#include "Command.h"

#include <stdexcept>

Command::Command(const bool executed) : executed_(executed)
{
}

Command& Command::operator=(const Command& other)
{
	if (this != &other) 
	{
		executed_ = other.executed_();
	}
	return *this;
}

Command::Command(Command&& other) noexcept : executed_(other.executed_())
{
	other.executed_ = false;
}

Command& Command::operator=(Command&& other) noexcept
{
	if (this != &other) {
		executed_ = other.executed_();
		other.executed_ = false;
	}
	return *this;
}

bool Command::GetExecuted() const
{
	return executed_;
}

void Command::Execute()
{
	if (executed_)
	{
		throw std::runtime_error("Command is already executed");
	}
	executed_ = true;
}

void Command::Revert()
{
	if (!executed_)
	{
		throw std::runtime_error("Command is not yet executed");
	}
	executed_ = false;
}
