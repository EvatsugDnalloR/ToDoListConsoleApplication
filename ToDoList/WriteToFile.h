#pragma once
#include <string>

class WriteToFile
{
public:
	static void AddToDo(std::string input_todo, const std::string& filename);
	static void DeleteToDo(size_t chosen_line, const std::string& filename);
	static void MarkAsDone(size_t chosen_line,const std::string& filename);
	void ModifyToDoMsg(std::string chosen_todo);

private:

};