#include "../includes/Channel.hpp"
#include "../includes/utils.hpp"

Channel::Channel(const std::string &name, Client *creator) : name(name)
{
	users.push_back(creator);
	operators.push_back(creator);
	invonly=0;
	pass=0;
	creator->addChannel(this);
}

Channel::~Channel()
{
	std::cout << "Channel destructor called" << std::endl;
}

std::string Channel::getPassword() const {
	return password;
}

void Channel::setPassword(std::string pass) {
	password = pass;
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
	return *this;
}

void Channel::addUser(Client *user, std::string pword)
{
	if (std::find(users.begin(), users.end(), user) != users.end())
   		return;
	if(invonly && (std::find(invited.begin(), invited.end(), user) == invited.end()))
		return;
	if(pass && pword!=password)
		return;
	users.push_back(user);
	user->addChannel(this);
}


void Channel::broadCast(Client *client, std::string msg)
{
    int sender_fd = client->getFd();

    for (size_t j = 0; j < users.size(); j++)
    {   
        int dest_fd = users[j]->getFd();

        if (dest_fd != sender_fd)
        {
            sendMessage(dest_fd, msg);
        }
    }
}


std::string Channel::getName()
{
	return name;
}

int Channel::isOperator(Client *client)
{
	if(std::find(operators.begin(),operators.end(), client)!=operators.end())
		return 1;
	else
		return 0;
}

std::vector<Client *> Channel::getUsers()
{
	return users;
}

void Channel::removeUser(Client *user)
{
	std::vector<Client *>::iterator userpos=std::find(users.begin(),users.end(), user);
	if(userpos!=users.end())
		users.erase(userpos);
}