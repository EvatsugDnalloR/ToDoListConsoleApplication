cmake_minimum_required (VERSION 3.20.2)

project(CommandTest)

set(CommandTest_Src
	pch.h
	UndoRedoTest.cpp
	AddToDoCommandTest.cpp
)

add_executable(${PROJECT_NAME} ${CommandTest_Src} "pch.h")

target_link_libraries(${PROJECT_NAME} 
	Command
	ToDoList
	gtest_main
)

add_test(NAME CommandTest COMMAND ${PROJECT_NAME})
