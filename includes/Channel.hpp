#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include "Client.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

class Channel
{
private:
    std::vector<Client *> users;
    std::string name;
    std::string topic;
    bool invonly;
    bool pass;
    std::vector<Client *> invited;
    std::string password;
	std::vector<Client *> operators;

public:
    Channel(const std::string &name, Client *creator);
    ~Channel();

	void addUser(Client *user, std::string password);

};

#endif // Channel_HPP