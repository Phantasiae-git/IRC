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
	void disconnectClient(int i);
	void SignalHandler(int signum);
	

	//std::string &getInputBuffer();
    //void appendToBuffer(const std::string data)
    //void clearBufferUpTo(size_t pos)

public:
	Server(int port, std::string password);
	~Server();
	const std::map<int, Client*> &getClients() const;
	void broadCast(Client *client, std::string msg);
	
	bool start();
	void run();
	
};

#endif