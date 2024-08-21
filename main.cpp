#include <csignal>
#include <cstdlib>
#include "ToDoList/MainFrame.h"

/**
 * Signal handler function, once the Ctrl C pressed, the
 *   program will just freeze and require manual exit.
 * @param sig_num	signal number sent through Ctrl C
 */
void SignalHandler(const int sig_num)
{
	std::println("{}{}\nInterrupt signal ({}) received",kBold, kRed, sig_num);
	std::print("Program will be frozen, please quit the program manually{}", kReset);
	exit(sig_num);
}

int main(int argc, char* argv[])
{
	signal(SIGINT, SignalHandler);  // NOLINT(cert-err33-c), register the signal handler
	MainFrame main_frame;
	main_frame.StartApp();
	if (!main_frame.GetExitSuccess())
	{
		return EXIT_FAILURE;	// mostly due to file missing or file corruption of specification.txt
	}
	return EXIT_SUCCESS;
}
