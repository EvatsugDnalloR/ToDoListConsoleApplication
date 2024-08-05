#include <format>
#include <fstream>
#include "WriteToFile.h"

void WriteToFile::AddToDo(std::string input_todo, const std::string& filename)
{
	if (input_todo.find('#') != std::string::npos)
	{
		throw std::invalid_argument("The ToDo message cannot contain the '#' character.");
	}
	
	std::ofstream outfile(filename, std::ios_base::app);
	CheckIsOpen(outfile);

	//TODO: Decide whether to use {std::move} or just pass by reference
	outfile << std::format("{}#0\n", std::move(input_todo));		

	outfile.close();
}

void WriteToFile::DeleteToDo(const size_t chosen_line, const std::string& filename)
{
	std::vector<std::string> lines{ GetLines(filename) };

	if (chosen_line >= lines.size())
	{
		throw std::invalid_argument("Chosen line is out of range");
	}

	lines.erase(lines.begin() + chosen_line);

	ModifyFile(filename, lines);
}

void WriteToFile::MarkAsDone(const size_t chosen_line, const std::string& filename)
{
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


void WriteToFile::ModifyToDoMsg(const size_t chosen_line, std::string msg, const std::string& filename)
{
	std::vector<std::string> lines{ GetLines(filename) };

	// Check if the chosen line is within the range
	if (chosen_line >= lines.size())
	{
		throw std::out_of_range("Chosen line is out of range");
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

void WriteToFile::CheckIsOpen(const std::ofstream& outfile)
{
	if (!outfile.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
}

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
