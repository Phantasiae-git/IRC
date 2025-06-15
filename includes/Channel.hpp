#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include "Client.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <map>

class Client;

class Channel
{
private:
    std::map<std::string, Client *> users;
    std::string name;
    std::string topic;
    bool invonly;
    bool pass;
    size_t limitUsers;
    std::map<std::string, Client *> invited;
    std::string password;
	std::map<std::string, Client *> operators;
	bool t;//1 only ops can, 0 anyone can

public:
	Channel();
    Channel(const std::string &name, Client *creator);
    ~Channel();

	Channel &operator=(const Channel &other);

	void addUser(Client *user, std::string password);

    void addToInvited(Client *user);
	void broadcast(Client *client, std::string msg);
    std::string getPassword() const;
    void setPassword(std::string pass);
	std::string getName();
	int isOperator(Client *client);
	void removeUser(std::string name, Client *kicker, std::string message);
    std::string getTopic() const;
    void setTopic(std::string topic);
    bool getT() const;
    void setT(bool t_mode);
  
	std::map<std::string, Client *> getUsers();
    size_t getLimitUsers() const;
    void setLimitUsers(size_t limit);
    bool getInviteOnly() const;
    void setInviteOnly(bool inviteOnly);
    void addToOperators(Client *user);
    std::string getFormattedUserList() const;
    int isInvited(Client *client);
};

#endif // Channel_HPP