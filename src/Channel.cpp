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
