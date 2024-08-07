#pragma once
#include <memory>
#include <vector>
#include "ToDo.h"

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

	void PrintOptions();

	void HandleUserInput(std::string& user_input);
};