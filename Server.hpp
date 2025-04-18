#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <iostream>

class Server
{
private:
    int server_fd;

public:
    Server();
    Server(const std::string &name);
    Server(const Server &other);
    ~Server();

    Server &operator=(const Server &other);
    // Other public member functions
};

#endif // Server_HPP