#include <fstream>
#include <sstream>
#include "ReadFromFile.h"

void ReadFromFile::PushToDo(std::string line, std::vector<ToDo>& todo_vector)
{
    const size_t pos = line.find('#');
    if (pos == std::string::npos)
    {
	    throw std::runtime_error("Missing '#' character");
    }

    const std::string msg = line.substr(0, pos);
    if (line.size() <= pos + 1)
    {
        throw std::runtime_error("Missing status value after '#' character");
    }

    const char status_char = line[pos + 1];
    if (status_char != '0' && status_char != '1')
    {
        throw std::runtime_error("Invalid status value after '#' character");
    }

    const bool done = (status_char == '1');
    const ToDo to_do{ msg, done };
    todo_vector.push_back(to_do);
}

std::vector<ToDo> ReadFromFile::GetToDos(std::string input)
{
    if (input.empty()) 
    {
        return std::vector<ToDo>{};
    }

    std::istringstream input_ref(std::move(input));
    std::string line;
    std::vector<ToDo> todo_vector;
    while (std::getline(input_ref, line))
    {
	    PushToDo(line, todo_vector);
    }
    return todo_vector;
}

std::string ReadFromFile::FileToString(const std::string& filename)
{
    std::ifstream infile(filename);

    /*
     * If file doesn't exist, create it, a blank txt file
     *  and return an empty string.
     */
    if (!infile) 
    {
        std::ofstream outfile(filename);
        return "";
    }

    /*
     * Read the contents of the existing file.
     */
    std::string content((std::istreambuf_iterator<char>(infile)),
        std::istreambuf_iterator<char>());
    return content;
}
