#include "ToDoList/MainFrame.h"

int main(int argc, char* argv[])
{
	MainFrame main_frame;
	main_frame.StartApp();
	if (main_frame.GetExitSuccess())
	{
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}