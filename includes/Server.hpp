#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <poll.h>
#include <sys/socket.h>
#include "utils.hpp"
#include "Client.hpp"

class Server
{
private:
	int						_listener_fd;
	int						_port;
	std::string				_password;
	std::vector<pollfd>		pfds;
	std::map<int, Client*>	clients;

	void acceptNewClient();
	void handleClientData(int i);
	void disconnectClient(int i);

public:
	Server(int port, std::string password);
	~Server();
	
	bool start();
	void run();
};

#endif