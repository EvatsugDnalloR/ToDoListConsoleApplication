#include "ToDoList/MainFrame.h"

#include "ToDoList/WriteToFile.h"
#include "ToDoList/ReadFromFile.h"
#include "ToDoList/ToDo.h"

int main(int argc, char* argv[])
{
	MainFrame main_frame;
	main_frame.StartApp();
	return EXIT_SUCCESS;
}