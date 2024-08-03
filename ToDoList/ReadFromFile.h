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
	 * Private axillary method to make GetToDos vector function cleaner.
	 * @param line	a line of the input stream from GetToDos
	 * @param todo_vector	the vector that stores all the ToDos that
	 *		will be returned by GetToDos
	 */
	static void PushToDo(std::string line, std::vector<ToDo>& todo_vector);

public:
	/**
	 * Static method that get all the ToDos from the string obtained from
	 *		the "specification.txt" file, and insert them into a vector such that
	 *		they can be iterated through.
	 * @param input the input string that contain all the ToDos, normally should be
	 *		obtained from "specification.txt"
	 * @return	A vector that contain all the ToDos
	 */
	static auto GetToDos(std::string input) -> std::vector<ToDo>;

	/**
	 * Static method that read the text from a txt file, and convert it to a
	 *		string object.
	 * @param filename	the name of the txt file, should be "specification.txt",
	 *		here parsed by parameter for testing different files
	 * @return	A string that contains what is in the txt file
	 */
	static auto FileToString(const std::string& filename) -> std::string;
};