#pragma once
#include <format>
#include <string>

/**
 * A TODO structure that represent each TODO.
 */
	struct ToDo
{
	/**  The message of a TODO.	 */
	std::string msg;

	/**  The boolean condition that tells if a TODO is marked as done or not.	 */
	bool done;

	ToDo(std::string msg, const bool done)
		: msg(std::move(msg)),
		done(done)
	{
	}

	// ReSharper disable once CommentTypo
	/**
	 * A helper function to overload the operator<< to print the ToDo struct.
	 *
	 * Should be printed as:
	 *	"Finish the code [  ]", which means not marked as done yet.
	 *	"Finish the code [ Done ]", which means marked as done.
	 * @param os	the ostream to be overloaded
	 * @param todo	the current ToDo class
	 * @return
	 */
	friend std::ostream& operator<<(std::ostream& os, const ToDo& todo)
	{
		std::string status = todo.done ? "Done" : "";
		const std::string to_be_printed = std::format("{} [ {} ]", todo.msg, status);
		os << to_be_printed;
		return os;
	}
};