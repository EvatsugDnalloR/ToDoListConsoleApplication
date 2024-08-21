#pragma once
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>
#include "ToDo.h"


/** The default static name of the Specification file. */
static const std::string kFilename{ "specification.txt" };

/**
 * The class for reading specification file and turn the string
 *		read from file to a vector of ToDos.
 */
class ReadFromFile
{
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

	/**
	 * Public auxiliary vector that contains each line of the {filename} txt.
	 *
	 * @param filename	the txt file that should be split and put into the vector
	 * @return	a vector that contains each line of the {filename} txt
	 */
	static auto GetLines(const std::string& filename) -> std::vector<std::string>;

	/**
	 * Private auxiliary method that checks if the {filename} exists or not.
	 *
	 * @param filename	the txt file that we need to check the existence
	 */
	static void CheckExist(const std::string& filename);

private:
	/**
	* Private axillary method to make GetToDos vector function cleaner.
	* @param line	a line of the input stream from GetToDos
	* @param todo_vector	the vector that stores all the ToDos that
	*		will be returned by GetToDos
	*/
	static void PushToDo(std::string line, std::vector<ToDo>& todo_vector);


};