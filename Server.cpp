#include "Server.hpp"

Server::Server()
{
    
}

Server::Server(const std::string &name)
{
    std::cout << "Server constructor called" << std::endl;
}

Server::Server(const Server &other)
{
    std::cout << "Server copy constructor called" << std::endl;
}

Server::~Server()
{
    std::cout << "Server destructor called" << std::endl;
}

Server &Server::operator=(const Server &other)
{
    if (this != &other)
    {   
        // Assign other attributes
    }
    return *this;
}
