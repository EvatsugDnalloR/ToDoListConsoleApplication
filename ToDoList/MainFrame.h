#pragma once
#include <memory>
#include <vector>
#include "ToDo.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <print>
#include <format>

#include <memory>
#include <set>
#include <sstream>
#include <ranges>

#include "ReadFromFile.h"
#include "WriteToFile.h"

class MainFrame
{
	bool exit_;
	std::vector<ToDo> to_do_s_;
	std::shared_ptr<std::string> msg_ptr_;

public:
	MainFrame();

	void StartApp();

private:
	void PrintToDos();

	static void PrintOptions();

	void HandleUserInput(const std::string& user_input);

	void HandleAddToDo();

	void HandleDeleteToDo();

	[[nodiscard]] std::vector<int> TakingDeleteParam(const std::string& user_input) const;

	static std::string RemoveSpaces(const std::string& input);

	void HandleMarkAsDone();

	void HandleModifyMsg();

	void ExitAndSave();

	static void CleanConsole();
};