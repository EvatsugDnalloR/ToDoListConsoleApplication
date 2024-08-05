cmake_minimum_required (VERSION 3.20.2)

project(ToDoListTest)

set(ToDoListTest_Src
    pch.h
    ToDoTest.cpp
    ReadFromFileTest.cpp
)

add_executable(${PROJECT_NAME} ${ToDoListTest_Src} "WriteToFileTest.cpp")

target_link_libraries(${PROJECT_NAME} 
	ToDoList 
	gtest_main
)

add_test(NAME ToDoListTest COMMAND ${PROJECT_NAME})

# Add a custom command to copy the test_src folder to the build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/ToDoListTest/test_src $<TARGET_FILE_DIR:${PROJECT_NAME}>/test_src
)