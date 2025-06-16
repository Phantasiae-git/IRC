#include "../includes/Channel.hpp"
#include "../includes/utils.hpp"
#include "../includes/Server.hpp"

Channel::Channel(const std::string &name, Client *creator) : name(name)
{
	users.insert(std::make_pair(creator->getUsername(), creator));
	operators.insert(std::make_pair(creator->getUsername(), creator));
	invonly = 0;
	pass = 0;
	limitUsers = 0;
	t = 0;
	creator->addChannel(name, this);
}

Channel::~Channel()
{
}
bool Channel::getInviteOnly() const
{
	return invonly;
}

void Channel::setInviteOnly(bool inviteOnly)
{
	invonly = inviteOnly;
}

bool Channel::getT() const
{
	return t;
}

void Channel::setT(bool t_mode)
{
	t = t_mode;
}

std::string Channel::getPassword() const
{
	return password;
}

void Channel::setPassword(std::string pass)
{
	password = pass;
}

std::string Channel::getTopic() const
{
	return topic;
}

void Channel::setTopic(std::string Topic)
{
	topic = Topic;
}

size_t Channel::getLimitUsers() const
{
	return limitUsers;
}

void Channel::setLimitUsers(size_t limit)
{
	limitUsers = limit;
}

Channel &Channel::operator=(const Channel &other)
{
	this->users = other.users;
	this->name = other.name;
	this->topic = other.topic;
	this->invited = other.invited;
	this->invonly = other.invonly;
	this->pass = other.pass;
	this->password = other.password;
	this->operators = other.operators;
	this->t = other.t;
	return *this;
}

void Channel::addUser(Client *user, std::string pword)
{
	if (users.find(user->getUsername()) != users.end())
		return;
	if (invonly)
	{
		std::map<std::string, Client *>::iterator invitedpos = invited.find(user->getUsername());
		if (invitedpos == users.end())
			return;
		else
			invited.erase(invitedpos);
	}
	if (pass && pword != password)
		return;
	users.insert(std::make_pair(user->getUsername(), user));
	user->addChannel(name, this);
}

void Channel::addToInvited(Client *user)
{
	if (invited.find(user->getUsername()) != invited.end())
		return;
	invited.insert(std::make_pair(user->getUsername(), user));
	;
}

void Channel::broadcast(Client *client, std::string msg)
{
	int sender_fd = client->getFd();

	for (std::map<std::string, Client *>::iterator it = users.begin(); it != users.end(); it++)
	{
		int dest_fd = it->second->getFd();

		if (dest_fd != sender_fd)
		{
			std::string newMsg = msg + "\r\n";
			send(dest_fd, newMsg.c_str(), newMsg.size(), 0);
		}
	}
}

std::string Channel::getName()
{
	return name;
}

int Channel::isOperator(Client *client)
{
	return (operators.find(client->getUsername()) != operators.end());
}

void Channel::removeUser(std::string name, Client *kicker, std::string message)
{
	broadcast(kicker, message);
	sendMessage(kicker->getFd(), message);

	std::map<std::string, Client *>::iterator userpos = users.begin();
	while (userpos != users.end()) {
		if (userpos->second->getNickname() == name || userpos->second->getUsername() == name)
			break ;
		userpos++;
	}
	if (userpos == users.end())
		return ;
		
	std::string msg = formatMessage(*(userpos->second), userpos->second->getNickname(), "PART", this->name, "");
	send(userpos->second->getFd(), msg.c_str(), msg.size(), 0);

	userpos->second->removeChannel(this);
	
	users.erase(userpos);
}

void Channel::eraseUser(std::string name)
{
	std::map<std::string, Client *>::iterator userpos = users.find(name);
	if (userpos == users.end())
		return;
	users.erase(userpos);
}

std::map<std::string, Client *> Channel::getUsers()
{
	return users;
}

void Channel::addToOperators(Client *user)
{
	if (operators.find(user->getUsername()) != operators.end())
		return;
	operators.insert(std::make_pair(user->getUsername(), user));
	;
}
std::string Channel::getFormattedUserList() const
{

	std::string result;
	for (std::map<std::string, Client *>::const_iterator it = operators.begin(); it != operators.end(); ++it)
	{
		std::string op = it->second->getNickname();
		if (!result.empty())
			result += " ";
		result += "@" + op;
	}
	for (std::map<std::string, Client *>::const_iterator it = users.begin(); it != users.end(); ++it)
	{
		std::string user = it->second->getNickname();
		if (operators.find(it->first) != operators.end())
			continue;
		if (!result.empty())
			result += " ";
		result += user;
	}
	return result;
}

int Channel::isInvited(Client *client)
{
	return (invited.find(client->getUsername()) != invited.end());
}

int Channel::removeOp(Client *client)
{
	std::map<std::string, Client *>::iterator it = operators.find(client->getUsername());
	if (it == operators.end())
		return 0;
	operators.erase(it);
	return 1;
}