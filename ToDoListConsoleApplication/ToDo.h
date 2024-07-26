#pragma once
#include <string>

struct ToDo
{
	std::string msg;
	bool done;

	ToDo(std::string msg, const bool done)
		: msg(std::move(msg)),
		  done(done)
	{
	}
};
