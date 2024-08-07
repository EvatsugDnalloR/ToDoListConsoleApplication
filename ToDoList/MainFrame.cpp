#include <algorithm>
#include <iostream>
#include <print>
#include "MainFrame.h"
#include "ReadFromFile.h"
#include "WriteToFile.h"

MainFrame::MainFrame()
{
	exit_ = false;

	to_do_s_ = {};

	msg_ptr_ = nullptr;
}


void MainFrame::StartApp()
{
	while (!exit_)
	{
		//TODO: clear all the existing output of the terminal

		if (!msg_ptr_)
		{
			//TODO: print the extra message at startup
		}

		PrintToDos();

		PrintOptions();

		std::string user_input;
		std::getline(std::cin, user_input);

		HandleUserInput(user_input);
	}
}

void MainFrame::PrintToDos()
{
	to_do_s_ = ReadFromFile::GetToDos(kFilename);

	if (to_do_s_.empty())
	{
		std::println("<<The ToDo list is still empty>>");
	}
	else
	{
		for (auto to_do: to_do_s_)
		{
			std::println("{}", to_do);
			//TODO: make the printed _ToDo_ prettier
		}
	}
}

void MainFrame::PrintOptions()
{
	
}

void MainFrame::HandleUserInput(std::string& user_input)
{
	std::ranges::transform(user_input, user_input.begin(), ::toupper);

	switch (user_input[0])
	{
		
	}
}




