#pragma once
#include <string>
#include <vector>

class WriteToFile
{
public:

	static void AddToDo(std::string input_todo, const std::string& filename);
	static void DeleteToDo(size_t chosen_line, const std::string& filename);
	static void MarkAsDone(size_t chosen_line,const std::string& filename);
	static void ModifyToDoMsg(size_t chosen_line, std::string msg, const std::string& filename);

private:
	static void CheckIsOpen(const std::ofstream& outfile);
	static auto GetLines(const std::string& filename) -> std::vector<std::string>;
	static void ModifyFile(const std::string& filename, const std::vector<std::string>& lines);
};
