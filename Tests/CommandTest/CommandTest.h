#pragma once
#include <filesystem>
#include "../pch.h"
#include "../../ToDoList/ReadFromFile.h"

/**
 * A class to create setup and teardown process for any Command type test,
 *   where each test require a clean "specification.txt" file present.
 * In this way no problem about multiple tests accessing the same txt file
 *   at the same time occurs.
 */
class CommandTest : public ::testing::Test
{
protected:
	/** Create the file before each test.	 */
	void SetUp() override {
		std::ofstream outfile(kFilename);
	}

	/** Remove the file after each test.	 */
	void TearDown() override {
		std::filesystem::remove(kFilename);
	}
};