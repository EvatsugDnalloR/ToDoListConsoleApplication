project(ToDoList)

set(ToDoList_Src
	ToDo.h
	ReadFromFile.h
	ReadFromFile.cpp
	WriteToFile.h
	WriteToFile.cpp
	MainFrame.h
	MainFrame.cpp
)

add_library(${PROJECT_NAME} ${ToDoList_Src})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
