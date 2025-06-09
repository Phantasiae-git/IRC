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
	int						listener_fd;
	int						port;
	std::string				password;
	std::vector<pollfd>		pfds;
	std::map<int, Client*>	clients;

	void acceptNewClient();
	void handleClientData(int i);
	void disconnectClient(int i);

public:
	Server(int portOut, std::string password);
	~Server();
	
	bool start();
	void run();
};

#endif