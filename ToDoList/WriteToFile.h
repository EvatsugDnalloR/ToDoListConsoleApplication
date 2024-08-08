#pragma once
#include <string>
#include <vector>
#include <format>
#include <fstream>
#include <filesystem>

/**
 * The class for doing the operation of adding, deleting, modifying or
 *		mark the ToDos as done by writing to the specification txt file.
 */
class WriteToFile
{
public:

	/**
	 * Static method that add a ToDo message to the {filename} txt,
	 *		and it will be marked as not done by default.
	 * @param input_todo	the input ToDo message that need to be added
	 * @param filename		the txt file that needs to be written in
	 */
	static void AddToDo(std::string input_todo, const std::string& filename);

	/**
	 * Static method that delete the {chosen_line}-th line of ToDo
	 *		in the {filename} txt file.
	 * @param chosen_line	the line that indicate which ToDo need to be deleted
	 * @param filename		the txt file that needs to be written in
	 */
	static void DeleteToDo(size_t chosen_line, const std::string& filename);

	/**
	 * Static method that mark or unmark the chosen ToDo to be done.
	 * @param chosen_line	the line that indicate which ToDo need to be marked or unmarked
	 * @param filename	the txt file that needs to be written in
	 */
	static void MarkAsDone(size_t chosen_line,const std::string& filename);

	/**
	 * Static method that modifies the message of the chosen ToDo.
	 * @param chosen_line	the line that indicate which ToDo message need to be modified
	 * @param msg	the message that will be parsed in
	 * @param filename	the name of the txt file that needs to be written in
	 */
	static void ModifyToDoMsg(size_t chosen_line, std::string msg, const std::string& filename);

private:
	/**
	 * Check if the {input} string contains any '#' character.
	 * @param input	the input string that should be checked 
	 */
	static void FindSharp(const std::string& input);

	/**
	 * Private auxiliary method that checks if the {filename} exists or not.
	 * @param filename	the txt file that we need to check the existence
	 */
	static void CheckExist(const std::string& filename);

	/**
	 * Private auxiliary method that checks if the {file} can be opened or not.
	 * @param file	the file that we want to open and write to
	 */
	static void CheckIsOpen(const std::ofstream& file);

	/**
	 * Private auxiliary vector that contains each line of the {filename} txt.
	 * @param filename	the txt file that should be split and put into the vector
	 * @return	a vector that contains each line of the {filename} txt
	 */
	static auto GetLines(const std::string& filename) -> std::vector<std::string>;

	/**
	 * Private auxiliary method that takes the modified version of each line of the ToDos
	 *		as a vector, and write back to the original {filename} txt.
	 * @param filename	the txt file that should be written in
	 * @param lines		the modified version of each line of ToDos
	 */
	static void ModifyFile(const std::string& filename, const std::vector<std::string>& lines);
};
