#include "ReadFromFile.h"

void ReadFromFile::PushToDo(std::string line, std::vector<ToDo>& todo_vector)
{
	if (const size_t pos = line.find('#'); pos != std::string::npos)
	{
		const std::string msg = line.substr(0, pos);
		const bool done = (line[pos + 1] == '1');
		const ToDo to_do{ msg, done };
		todo_vector.push_back(to_do);
	}
}

std::vector<ToDo> ReadFromFile::GetToDos(std::string input)
{
    std::istringstream input_ref(std::move(input));
    std::string line;
    std::vector<ToDo> todo_vector;
    while (std::getline(input_ref, line))
    {
	    PushToDo(line, todo_vector);
    }
    return todo_vector;
}
