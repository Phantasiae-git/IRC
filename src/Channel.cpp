#include "../includes/Channel.hpp"

Channel::Channel(const std::string &name, Client *creator) : name(name)
{
	users.push_back(creator);
	operators.push_back(creator);
	invonly=0;
	pass=0;
}

Channel::~Channel()
{
	std::cout << "Channel destructor called" << std::endl;
}


void Channel::addUser(Client *user, std::string pword)//if no password send empty
{
	if (std::find(users.begin(), users.end(), user) != users.end())
   		return;
	if(invonly && (std::find(invited.begin(), invited.end(), user) == invited.end()))
		return;
	if(pass && pword!=password)
		return;
	users.push_back(user);
}
