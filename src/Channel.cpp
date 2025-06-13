#include "../includes/Channel.hpp"
#include "../includes/utils.hpp"
#include "../includes/Server.hpp"

Channel::Channel(const std::string &name, Client *creator) : name(name)
{
	users.insert(std::make_pair(creator->getUsername(), creator));
	std::cout << "Users Size: " << users.size() << std::endl;
	std::cout << "FIrst: " << (users.begin())->first << std::endl;
	operators.insert(std::make_pair(creator->getUsername(), creator));
	invonly=0;
	pass=0;
	t=0;
	creator->addChannel(name, this);
}

Channel::~Channel()
{
}

bool Channel::getT() const {
	return t;
}

void Channel::setT(bool t_mode) {
	t = t_mode;
}

std::string Channel::getPassword() const {
	return password;
}

void Channel::setPassword(std::string pass) {
	password = pass;
}

std::string Channel::getTopic() const {
	return topic;
}

void Channel::setTopic(std::string Topic) {
	topic = Topic;
}

Channel &Channel::operator=(const Channel &other)
{
	this->users=other.users;
	this->name=other.name;
	this->topic=other.topic;
	this->invited=other.invited;
	this->invonly=other.invonly;
	this->pass=other.pass;
	this->password=other.password;
	this->operators=other.operators;
	this->t=other.t;
	return *this;
}

void Channel::addUser(Client *user, std::string pword)
{
	if (users.find(user->getUsername())!=users.end())
   		return;
	if(invonly && (invited.find(user->getUsername())==users.end()))
		return;
	if(pass && pword!=password)
		return;
	users.insert(std::make_pair(user->getUsername(), user));;
	user->addChannel(name, this);
}

void Channel::addToInvited(Client *user)
{
	if (invited.find(user->getUsername())!=invited.end())
   		return;
	invited.insert(std::make_pair(user->getUsername(), user));;
}

void Channel::broadCast(Client *client, std::string msg)
{
    int sender_fd = client->getFd();

    for (std::map<std::string, Client *>::iterator it=users.begin(); it!=users.end(); it++)
    {   
        int dest_fd = it->second->getFd();

        if (dest_fd != sender_fd)
        {
			send(dest_fd, msg.c_str(), msg.size(), 0);
        }
    }
}


std::string Channel::getName()
{
	return name;
}

int Channel::isOperator(Client *client)
{
	return (operators.find(client->getUsername())!=operators.end());
}

void Channel::removeUser(std::string name)
{
	std::map<std::string, Client *>::iterator userpos=users.find(name);
	if(userpos!=users.end())
		users.erase(userpos);
}