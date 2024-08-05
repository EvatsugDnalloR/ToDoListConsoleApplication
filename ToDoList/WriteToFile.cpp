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
