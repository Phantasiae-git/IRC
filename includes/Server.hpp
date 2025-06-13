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
#include "Channel.hpp"
#include <csignal>

class Server
{
private:
	int						_listener_fd;
	int						_port;
	std::string				_password;
	std::vector<pollfd>		pfds;
	std::map<int, Client*>	clients;
	std::map<int, std::string>	_input_buffers;	
	
	void acceptNewClient();
	void handleClientData(int i);
	void SignalHandler(int signum);
	
public:
	std::map<std::string, Channel*>	channels;
	Server(int port, std::string password);
	~Server();
	const std::map<int, Client*> &getClients() const;
	
	bool start();
	void run();
	void disconnectClient(int i);
	
	std::string getPassword() const;
};

#endif