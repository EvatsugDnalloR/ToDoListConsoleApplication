#include <format>
#include <fstream>
#include <filesystem>
#include "WriteToFile.h"

/**
 * The method that add a ToDo message to the {filename} txt,
 *		and it will be marked as not done by default.
 * @pre the {filename} txt exists and can be opened correctly
 * @pre the {input_todo} message doesn't contain '#' character
 * @param input_todo	the input ToDo message that need to be added
 * @param filename	the txt file that needs to be written in
 * @throw invalid_argument	if {input_todo} message contains any '#' character
 * @throw runtime_error	if the {filename} txt does not exist or
 *		cannot be opened correctly
 * @post the {filename} txt contains the ToDO message of {input_todo} and
 *		been marked as not done
 */
void WriteToFile::AddToDo(std::string input_todo, const std::string& filename)
{
	FindSharp(input_todo);

	CheckExist(filename);

	std::ofstream outfile(filename, std::ios_base::app);
	CheckIsOpen(outfile);

	outfile << std::format("{}#0\n", std::move(input_todo));		

	outfile.close();
}

/**
 * The method that delete the {chosen_line}-th line of ToDo
 *		in the {filename} txt file.
 * Initialise a vector that contains each line of the {filename} txt,
 *		then delete the corresponding line of ToDo at the
 *		{chosen_line} position of the vector, and finally write all lines
 *		in the vector back to the {filename} txt.
 * @pre the {filename} txt exists and can be opened correctly
 * @pre the {chosen_line} should be in the range of the size of the vector
 * @param chosen_line	the line that indicate which ToDo need to be deleted
 * @param filename	the name of the txt file that needs to be written in
 * @throw invalid_argument	if {chosen_line} is out of range
 * @throw runtime_error	if the {filename} txt does not exist or
 *		cannot be opened correctly
 * @post the ToDo previously at the {chosen_line} position should
 *		no longer exists in the {filename} txt
 */
void WriteToFile::DeleteToDo(const size_t chosen_line, const std::string& filename)
{
	CheckExist(filename);
	std::vector<std::string> lines{ GetLines(filename) };

	if (chosen_line >= lines.size())
	{
		throw std::invalid_argument("Chosen line is out of range");
	}

	lines.erase(lines.begin() + chosen_line);

	ModifyFile(filename, lines);
}

/**
 * The method that mark or unmark the chosen ToDo to be done.
 * If the condition of the ToDo is not done (i.e. #0), then mark as done (i.e. #1),
 *		and vice or versa.
 * @pre the {filename} txt exists and can be opened correctly
 * @pre the {chosen_line} should be in the range of the size of the vector
 * @pre the ToDo message at the position {chosen_line} should contain a '#' character,
 *		and followed by either '0' or '1'
 * @param chosen_line	the line that indicate which ToDo need to be marked or unmarked
 * @param filename	the txt file that needs to be written in
 * @throw runtime_error	if the {filename} txt does not exist or
 *		cannot be opened correctly, or the ToDo message doesn't
 *		contain a '#' character, or followed by
 *		the character other than '0' and '1'
 * @throw invalid_argument	if {chosen_line} is out of range
 * @post the ToDo message at the {chosen_line} position has been marked as the
 *		opposite condition to before
 */
void WriteToFile::MarkAsDone(const size_t chosen_line, const std::string& filename)
{
	CheckExist(filename);
	std::vector<std::string> lines{ GetLines(filename) };

	if (chosen_line >= lines.size())
	{
		throw std::invalid_argument("Chosen line is out of range");
	}

	std::string& chosen_line_str = lines.at(chosen_line);
	const size_t pos = chosen_line_str.find('#');
	if (pos == std::string::npos || pos + 1 >= chosen_line_str.size())
	{
		throw std::runtime_error("Invalid format in the chosen line");
	}

	switch (char& status_char = chosen_line_str.at(pos + 1))
	{
		case '0':
			status_char = '1';
			break;
		case '1':
			status_char = '0';
			break;
		default:
			throw std::runtime_error("Invalid status value after '#' character");
	}

	ModifyFile(filename, lines);
}

/**
 * The method that modifies the message of the chosen ToDo, and
 *		keep the original condition of done or not done.
 * @pre the {filename} txt exists and can be opened correctly
 * @pre the {chosen_line} should be in the range of the size of the vector
 * @pre the input modification {msg} should not contain any '#' character
 * @pre the chosen ToDo message should contain a '#' character
 * @param chosen_line	the line that indicate which ToDo message need to be modified
 * @param msg	the message that will be parsed in
 * @param filename	the txt file that needs to be written in
 * @throw runtime_error	if the {filename} txt does not exist or
 *		cannot be opened correctly, or the ToDo message
 *		doesn't contain a '#' character
 * @throw invalid_argument	if {chosen_line} is out of range
 *		or the {msg} string contains a '#' character
 * @post the ToDo at the {chosen_line} position should contain the new message of {msg},
 *		and having the same done or not done condition as before
 */
void WriteToFile::ModifyToDoMsg(const size_t chosen_line, std::string msg, const std::string& filename)
{
	CheckExist(filename);

	FindSharp(msg);

	std::vector<std::string> lines{ GetLines(filename) };

	// Check if the chosen line is within the range
	if (chosen_line >= lines.size())
	{
		throw std::invalid_argument ("Chosen line is out of range");
	}

	// Modify the message part of the chosen line
	std::string& chosen_line_str = lines.at(chosen_line);
	const size_t pos = chosen_line_str.find('#');
	if (pos == std::string::npos)
	{
		throw std::runtime_error("Invalid format in the chosen line");
	}

	// Replace the message part before the '#' character with the new message
	chosen_line_str = std::format("{}{}", std::move(msg), chosen_line_str.substr(pos));

	// Write the updated lines back to the file
	ModifyFile(filename, lines);
}

/**
 * Check if the {input} string contains any '#' character,
 *	if so throw an exception.
 * @param input		the input string that should be checked 
 * @throw invalid_argument	if the {input} string contains any '#' character
 */
void WriteToFile::FindSharp(const std::string& input)
{
	if (input.find('#') != std::string::npos)
	{
		throw std::invalid_argument("The ToDo message cannot contain the '#' character.");
	}
}

/**
 * The auxiliary method that checks if the {filename} exists or not.
 * @param filename	the txt file that we need to check the existence
 * @throw runtime_error	if the {filename} doesn't exist
 */
void WriteToFile::CheckExist(const std::string& filename)
{
	if (!std::filesystem::exists(filename))
	{
		throw std::runtime_error("File does not exist");
	}
}


/**
 * The auxiliary method that checks if the {outfile} can be opened or not.
 * @param file	the file that we want to open and write to
 * @throw runtime_error	if the {filename} txt cannot be opened correctly
 */
void WriteToFile::CheckIsOpen(const std::ofstream& file)
{
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
}

/**
 * The auxiliary vector that contains each line of the {filename} txt.
 * @pre the {filename} txt exists and can be opened correctly
 * @param filename	the txt file that needs to be written in
 * @throw runtime_error	if the {filename} txt cannot be opened correctly
 * @return	a vector that contains each line of the {filename} txt
 */
std::vector<std::string> WriteToFile::GetLines(const std::string& filename)
{
	// Open the file in input mode
	std::ifstream infile(filename);
	if (!infile.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(infile, line))
	{
		lines.push_back(line);
	}
	infile.close();

	return lines;
}

/**
 * The auxiliary method that takes the modified version of each line of the ToDos
 *		as a vector, and write back to the original {filename} txt.
 * @pre the {filename} txt exists and can be opened correctly
 * @param filename	the txt file that should be written in
 * @param lines		the modified version of each line of ToDos
 * @throw runtime_error	if the {filename} txt cannot be opened correctly
 */
void WriteToFile::ModifyFile(const std::string& filename, const std::vector<std::string>& lines)
{
	std::ofstream outfile(filename);
	CheckIsOpen(outfile);

	for (const auto& line : lines)
	{
		outfile << std::format("{}\n", line);
	}
	outfile.close();
}
