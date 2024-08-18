project(Command)

set(Command_Src
	UndoRedo.h
	UndoRedo.cpp
	Command.h
	Command.cpp
	AddToDoCommand.h
	AddToDoCommand.cpp
	DeleteToDoCommand.h
	DeleteToDoCommand.cpp
)

add_library(${PROJECT_NAME} ${Command_Src})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} ToDoList)
