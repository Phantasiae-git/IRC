#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
private:
    int client_fd;
    std::string nickname;
    std::string username;
    std::string real_name;
    int server_fd;

public:
    Client();
    Client(const std::string &name);
    Client(const Client &other);
    ~Client();

    Client &operator=(const Client &other);
    // Other public member functions
};

#endif // Client_HPP