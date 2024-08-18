cmake_minimum_required (VERSION 3.20.2)

project(CommandTest)

set(CommandTest_Src
	${CMAKE_SOURCE_DIR}/Tests/pch.h
	UndoRedoTest.cpp
	AddToDoCommandTest.cpp
	DeleteToDoCommandTest.cpp
)

add_executable(${PROJECT_NAME} ${CommandTest_Src})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Tests)

target_link_libraries(${PROJECT_NAME} 
	Command
	ToDoList
	gtest_main
)

add_test(NAME CommandTest COMMAND ${PROJECT_NAME})
