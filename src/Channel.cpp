#include "../includes/Channel.hpp"


Channel::Channel(const std::string &name, Client *creator) : name(name)
{
	users.push_back(creator);
	
}

Channel::~Channel()
{
	std::cout << "Channel destructor called" << std::endl;
}

