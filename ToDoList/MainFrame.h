#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <print>
#include <format>
#include <memory>
#include <set>
#include <sstream>
#include <ranges>
#include <vector>
#include "ReadFromFile.h"
#include "WriteToFile.h"
#include "ToDo.h"

class MainFrame
{
	/** 	 */
	bool exit_;

	/** 	 */
	std::vector<ToDo> to_do_s_;

	/** 	 */
	std::shared_ptr<std::string> msg_ptr_;

public:
	/**
	 * 
	 */
	MainFrame();

	/**
	 * 
	 */
	void StartApp();

private:
	/**
	 * 
	 */
	void PrintToDos();

	/**
	 * 
	 */
	static void PrintOptions();

	/**
	 * 
	 * @param user_input 
	 */
	void HandleUserInput(const std::string& user_input);

	/**
	 * 
	 */
	void HandleAddToDo();

	/**
	 * 
	 */
	void HandleDeleteToDo();

	/**
	 * 
	 * @param user_input 
	 * @return 
	 */
	[[nodiscard]] std::vector<int> TakingDeleteParam(const std::string& user_input) const;

	/**
	 * 
	 * @param input 
	 * @return 
	 */
	static std::string RemoveSpaces(const std::string& input);

	/**
	 * 
	 */
	void HandleMarkAsDone();

	/**
	 * 
	 */
	void HandleModifyMsg();

	/**
	 * 
	 */
	void ExitAndSave();

	/**
	 * 
	 */
	static void CleanConsole();
};