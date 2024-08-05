#include <format>
#include <fstream>
#include <vector>
#include "WriteToFile.h"

void WriteToFile::AddToDo(std::string input_todo, const std::string& filename)
{
	if (input_todo.find('#') != std::string::npos)
	{
		throw std::invalid_argument("The ToDo message cannot contain the '#' character.");
	}
	
	std::ofstream outfile(filename, std::ios_base::app);
	if (!outfile.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}

	//TODO: Decide whether to use {std::move} or just pass by reference
	outfile << std::format("{}#0\n", std::move(input_todo));		

	outfile.close();
}

void WriteToFile::DeleteToDo(size_t chosen_line, const std::string& filename)
{
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

	if (chosen_line >= lines.size())
	{
		throw std::invalid_argument("Chosen line is out of range");
	}

	lines.erase(lines.begin() + chosen_line);

	std::ofstream outfile(filename);
	if (!outfile.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}

	for (const auto& remaining_line : lines)
	{
		outfile << std::format("{}\n", remaining_line);
	}
	outfile.close();
}

void WriteToFile::MarkAsDone(size_t chosen_line, const std::string& filename)
{
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

	if (chosen_line >= lines.size())
	{
		throw std::invalid_argument("Chosen line is out of range");
	}

	std::string& chosen_line_str = lines.at(chosen_line);
	size_t pos = chosen_line_str.find('#');
	if (pos == std::string::npos || pos + 1 >= chosen_line_str.size())
	{
		throw std::runtime_error("Invalid format in the chosen line");
	}

	if (char& status_char = chosen_line_str.at(pos + 1); status_char == '0')
	{
		status_char = '1';
	}
	else if (status_char == '1')
	{
		status_char = '0';
	}
	else
	{
		throw std::runtime_error("Invalid status value after '#' character");
	}

	std::ofstream outfile(filename);
	if (!outfile.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	for (const auto& modified_lines : lines)
	{
		outfile << std::format("{}\n", modified_lines);
	}
	outfile.close();
}

