#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <poll.h>
#include <sys/socket.h>
#include "utils.hpp"

class Server
{
private:
    int listener_fd;
    std::vector<pollfd> pfds;

    void acceptNewClient();
    void handleClientData(int i);
    void disconnectClient(int i);
    Server(const std::string &name);
    Server(const Server &other);
    Server &operator=(const Server &other);

public:
    Server();
    ~Server();
    
    bool start(int port);
    void run();
};

#endif