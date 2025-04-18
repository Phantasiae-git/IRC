#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include "Client.hpp"
#include <vector>

class Channel
{
private:
    std::vector<Client> users;
    std::string name;
    std::string topic;
    bool invonly;
    bool pass;
    std::vector<Client> invited;
    std::string password;

public:
    Channel();
    Channel(const std::string &name);
    Channel(const Channel &other);
    ~Channel();

    Channel &operator=(const Channel &other);
    // Other public member functions
};

#endif // Channel_HPP