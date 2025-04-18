#include "Server.hpp"
#include "Client.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        std::cout << "usage: ./ircserv <port> <password>" << std::endl;
        return(1);
    }

    
}