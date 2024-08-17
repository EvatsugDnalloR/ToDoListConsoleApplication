cmake_minimum_required (VERSION 3.20.2)

project(ToDoListTest)

set(ToDoListTest_Src
    ${CMAKE_SOURCE_DIR}/Tests/pch.h
    ToDoTest.cpp
    ReadFromFileTest.cpp
    WriteToFileTest.cpp
    MainFrameTest.cpp
)

add_executable(${PROJECT_NAME} ${ToDoListTest_Src})

target_link_libraries(${PROJECT_NAME} 
	ToDoList 
	gtest_main
)

add_test(NAME ToDoListTest COMMAND ${PROJECT_NAME})

# Add a custom command to copy the test_src folder to the build directory
add_custom_command(
    TARGET ${PROJECT_NAME} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/ToDoListTest/test_src $<TARGET_FILE_DIR:${PROJECT_NAME}>/test_src
)

# Add a custom command to clean the test_src folder
add_custom_command(
    TARGET ${PROJECT_NAME} 
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/test_src
    COMMENT "Cleaning test_src folder"
)