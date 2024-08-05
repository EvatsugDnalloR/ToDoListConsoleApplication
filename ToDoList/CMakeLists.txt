project(ToDoList)

set(ToDoList_Src
	ToDo.h
	ReadFromFile.h
	ReadFromFile.cpp
	WriteToFile.h
	WriteToFile.cpp
)

add_library(${PROJECT_NAME} ${ToDoList_Src})
