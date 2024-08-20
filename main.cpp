#include <csignal>
#include <cstdlib>
#include "ToDoList/MainFrame.h"

// Signal handler function
void signalHandler(int signum) {
	std::cout << "\nInterrupt signal (" << signum << ") received.\n";
	// Perform cleanup and exit
	std::cout << "Performing cleanup...\n";
	// Add your cleanup code here
	exit(signum);
}

int main(int argc, char* argv[])
{
	signal(SIGINT, signalHandler);
	MainFrame main_frame;
	main_frame.StartApp();
	if (!main_frame.GetExitSuccess())
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}