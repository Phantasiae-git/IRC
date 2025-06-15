#include "../includes/Server.hpp"
#include "../includes/CommandHandler.hpp"
#include "../includes/globalSignal.hpp"

Server::Server(int port, std::string pswd)
	: _listener_fd(-1), _port(port), _password(pswd) {}

Server::~Server()
{
	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
		delete it->second;
	}
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		delete it->second;
	}
	for (std::vector<pollfd>::iterator it = pfds.begin(); it != pfds.end(); ++it) {
		if (it->fd > 0) {
			close (it->fd);
		}
	}
	channels.clear();
	clients.clear();
	pfds.clear();
	std::cout << "Server destructor called" << std::endl;
}

std::string Server::getPassword() const {
	return _password;
}

const std::map<int, Client*> &Server::getClients() const 
{
	return this->clients;
}

void Server::addClient(int fd, Client *client) {
	clients.insert(std::make_pair(fd, client));

}

std::map<int, Client*> Server::getClients() {
	return clients;
}

Client* Server::findClient(std::string name) {
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++) {
		if (name == it->second->getNickname()) {
			return it->second;
		}
	}
	return NULL;
}

void Server::acceptNewClient()
{
	sockaddr_in client_addr;
	socklen_t cl_addr_len = sizeof client_addr;

	Client* newClient = new Client(accept(_listener_fd, (sockaddr *)&client_addr, &cl_addr_len));
	if (newClient->getFd() < 0)
	{
		std::cerr << "accept failed: " << errno << std::endl;
		delete newClient;
		return;
	}
	pfds.push_back((pollfd){newClient->getFd(), POLLIN, 0});
	std::cout << "yay! new connection from " << inet_ntoa(client_addr.sin_addr) << " on socket " << newClient->getFd() << std::endl;

	clients.insert(std::make_pair(newClient->getFd(), newClient));
}

void Server::handleClientData(int i)
{
	CommandHandler cmdhandler;
	char buf[256];
	int nbytes = recv(pfds[i].fd, buf, sizeof buf, 0);
	int sender_fd = pfds[i].fd; 

	if (nbytes < 1)
	{
		if (nbytes < 0)
			std::cerr << "recv error: " << errno << std::endl;
		else
			std::cerr << "socket shutdown" << std::endl;
		disconnectClient(i);
	}
	else
	{
		_input_buffers[sender_fd].append(buf, nbytes);
		size_t pos;
		while ((pos = _input_buffers[sender_fd].find("\r\n")) != std::string::npos) {
			std::string msg = _input_buffers[sender_fd].substr(0, pos);
			_input_buffers[sender_fd].erase(0, pos + 2);
			std::map<int, Client*>::iterator it = clients.find(sender_fd);
			Client* client = it->second;
			cmdhandler.handle(*this, *client, msg);
			
			if(client->isRegistered() && !client->isAthenticated())
				disconnectClient(i);			
		}
	}
	
}

void Server::disconnectClient(int i)
{
    std::cout << "client disconnected on socket " << pfds[i].fd << std::endl;

    std::map<int, Client*>::iterator it = clients.find(pfds[i].fd);
    sendError(it->second->getFd(), 404, it->second->getNickname(), " ", "You have been disconnected. Please restart conection\n");
    
    close(pfds[i].fd);
    if (it != clients.end()) {

        it->second->removeFromAll();
        delete it->second;
        clients.erase(it);
    }
    pfds.erase(pfds.begin() + i);
}

bool Server::start()
{
	_listener_fd = get_listen_sock(_port);
	if (_listener_fd == -1)
	{
		std::cerr << "Failed to create listener socket" << std::endl;
		return false;
	}
	pfds.push_back((pollfd){_listener_fd, POLLIN, 0});
	std::cout << "Server started with port " << _port << std::endl;
	return true;
}

void Server::run()
{
	try
	{
		while (!g_stop)
		{
			int act_socks = poll(&pfds[0], pfds.size(), -1);
			if (act_socks < 0)
			{
				if (errno == EINTR && g_stop)
					break;
				std::cerr << "poll failed: " << errno << std::endl;
				break;
			}

			for (size_t i = 0; i < pfds.size(); i++)
			{
				
				if (pfds[i].revents & (POLLIN))
				{
					if (pfds[i].fd == _listener_fd)
					{
						acceptNewClient();
					}
					else
					{
						handleClientData(i);
					}
				}
				else if (pfds[i].revents & POLLHUP)
				{
					disconnectClient(i);
					--i;
				}
			}
		}
	}
	catch (const std::exception &e)
	{
		while (!pfds.empty())
			disconnectClient(0);
		std::cerr << e.what() << '\n';
	}
}