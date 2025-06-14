#include "includes/Server.hpp"
#include "includes/utils.hpp"
#include "includes/globalSignal.hpp"

volatile sig_atomic_t g_stop = 0;

void sigintHandler(int signum)
{
	(void)signum;
	std::cout << "\nCaught SIGINT, server is shutting down..." << std::endl;
	g_stop = 1;
}

int main(int argc, char **argv)
{
	if(argc != 3) {
		std::cout << "Usage: ./ircserv Port Password" << std::endl;
		return 1;
	}

	int port;
	if (isValidPort(argv[1], port) == false) {
		std::cerr << "Invalid port: " << argv[1] << " (must be a number between 1024 and 65535)" << std::endl;
		return 1;
	}

	signal(SIGINT, sigintHandler);

	Server server(port, argv[2]);
	if (!server.start()) {
		std::cerr << "failed to start server" << std::endl;
		return 1;
	}
	server.run();
	return 0;
}