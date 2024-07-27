#pragma once
#include <vector>
#include "ToDo.h"


/** The default name of the Specification file. */
static const std::string kFilename{ "specification.txt" };

/**
 * The class for reading specification file and turn the string
 *		read from file to a vector of ToDos.
 */
class ReadFromFile
{
	/**
	 * Private axillary function to make GetToDos vector function cleaner.
	 * @param line	each line of the input stream from GetToDos
	 * @param todo_vector	the vector that stores all the ToDos that
	 *		will be returned by GetToDos
	 */
	static void PushToDo(std::string line, std::vector<ToDo>& todo_vector);

public:
	static auto GetToDos(std::string input) -> std::vector<ToDo>;

	static auto FileToString(const std::string& filename) -> std::string;
};
