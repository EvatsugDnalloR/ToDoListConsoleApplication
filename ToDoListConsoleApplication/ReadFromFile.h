#pragma once
#include <vector>
#include <sstream>
#include "ToDo.h"

class ReadFromFile
{
static void PushToDo(std::string line, std::vector<ToDo>& todo_vector);

public:
	static auto GetToDos(std::string input) -> std::vector<ToDo>;
};
