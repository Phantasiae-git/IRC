#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include "Client.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

class Client;

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
	bool t;//1 only ops can, 0 anyone can

public:
	Channel();
    Channel(const std::string &name, Client *creator);
    ~Channel();

	Channel &operator=(const Channel &other);

	void addUser(Client *user, std::string password);
	void broadCast(Client *client, std::string msg);
    std::string getPassword() const;
    void setPassword(std::string pass);
	std::string getName();
	int isOperator(Client *client);
	std::vector<Client *> getUsers();
	void removeUser(Client *user);
    std::string getTopic() const;
    void setTopic(std::string topic);
    bool getT() const;
    void setT(bool t_mode);

};

#endif // Channel_HPP