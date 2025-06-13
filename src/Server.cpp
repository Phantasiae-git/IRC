#include "../includes/Server.hpp"
#include "../includes/CommandHandler.hpp"

Server::Server(int port, std::string pswd)
    : _listener_fd(-1), _port(port), _password(pswd) {}

Server::~Server()
{
    std::cout << "Server destructor called" << std::endl;
}

const std::map<int, Client*> &Server::getClients() const 
{
    return this->clients;
}

void Server::broadCast(Client *client, std::string msg)
{
    int sender_fd = client->getFd();

    for (size_t j = 0; j < pfds.size(); j++)
    {   
        int dest_fd = pfds[j].fd;

        if (dest_fd != _listener_fd && dest_fd != sender_fd)
        {
            sendMessage(dest_fd, msg);
        }
    }
}
void Server::acceptNewClient()
{
    // novo cliente
    sockaddr_in client_addr;
    socklen_t cl_addr_len = sizeof client_addr;

    Client newclient(accept(_listener_fd, (sockaddr *)&client_addr, &cl_addr_len));
    
    if (newclient.getFd() < 0)
    {
        std::cerr << "accept failed: " << errno << std::endl;
        return;
    }
    pfds.push_back((pollfd){newclient.getFd(), POLLIN, 0});
    std::cout << "yay! new connection from " << inet_ntoa(client_addr.sin_addr) << " on socket " << newclient.getFd() << std::endl;

    clients.insert(std::make_pair(newclient.getFd(), &newclient)); // adicionar cliente a um map

    
    
}

void Server::handleClientData(int i)
{
    CommandHandler cmdhandler;
    char buf[256];
    int nbytes = recv(pfds[i].fd, buf, sizeof buf, 0);
    int sender_fd = pfds[i].fd; 

	std::cout << nbytes << std::endl;
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
		std::cout << _input_buffers[sender_fd] << std::endl;
		size_t pos;
        while ((pos = _input_buffers[sender_fd].find("\n")) != std::string::npos) {
            std::string msg = _input_buffers[sender_fd].substr(0, pos);
            _input_buffers[sender_fd].erase(0, pos + 2);

            std::map<int, Client*>::iterator it = clients.find(sender_fd);
            Client* client = it->second;

            cmdhandler.handle(*this, *client, msg);
        }
    }
}
void Server::disconnectClient(int i)
{
    std::cout << "client disconnected on socket " << pfds[i].fd << std::endl;
	_input_buffers.erase(pfds[i].fd);
    close(pfds[i].fd);
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
        while (1)
        {
            int act_socks = poll(&pfds[0], pfds.size(), -1);
			std::cout << act_socks << std::endl;
            if (act_socks < 0)
            {
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