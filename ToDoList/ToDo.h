#pragma once
#include <format>
#include <string>

/**
 * A TO_DO structure that represent each TO_DO.
 */
	struct ToDo
{
	/**  The message of a To_Do.	 */
	std::string msg;

	/**  The boolean condition that tells if a To_Do is marked as done or not.	 */
	bool done;

	ToDo(std::string msg, const bool done)
		: msg(std::move(msg)),
		done(done)
	{
	}

	// ReSharper disable once CommentTypo
	/**
	 * A helper function to overload the operator<< to print the To_Do struct.
	 *
	 * Should be printed as:
	 *	"Finish the code [  ]", which means not marked as done yet.
	 *	"Finish the code [ Done ]", which means marked as done.
	 * @param os	the ostream to be overloaded
	 * @param to_do	the current To_Do class
	 * @return
	 */
	friend std::ostream& operator<<(std::ostream& os, const ToDo& to_do)
	{
		std::string status = to_do.done ? "Done" : "";
		const std::string to_be_printed = std::format("{} [ {} ]", to_do.msg, status);
		os << to_be_printed;
		return os;
	}
};
