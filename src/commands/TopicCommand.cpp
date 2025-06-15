#include "../../includes/commands/TopicCommand.hpp"

TopicCommand::TopicCommand() {}
TopicCommand::~TopicCommand() {}


void TopicCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {

    (void)server;

    if (!client.isAthenticated()) 
    {
		return ;
	}
    if (args.size() < 2) 
    {
		sendError(client.getFd(), 461, client.getNickname(), "TOPIC", "Not enough parameters");
		return;
	}
    if(args[1][0]!='#')
	{
		sendError(client.getFd(), 476, client.getNickname(), " ", "Bad channel mask");
		return;
	}
    std::map<std::string, Channel *> channels;
	channels=client.getChannels();
	std::map<std::string, Channel *>::iterator it=channels.find(args[1]);
	if(it==channels.end())
	{
		sendError(client.getFd(), 442, client.getNickname(), " ", "You're not on the channel");
		return;
	}
	Channel *channel =it->second;
	if(!channel->isOperator(&client) && channel->getT() == true)
	{
		sendError(client.getFd(), 482, client.getNickname(), " ", "You're not a channel operator");
		return;
	}

    if(args.size() == 2)
    {
        if (channel->getTopic().empty())
		{
			std::string msg = formatMessage(client, "localhost", "TOPIC", args[1], "No topic is set");
			sendMessage(client.getFd(), msg);
		}
		else
		{
			std::string msg = formatMessage(client, "localhost", "TOPIC", args[1], channel->getTopic());
			sendMessage(client.getFd(), msg);
		}
    }
    else if(args.size() == 3)
    {
        channel->setTopic(args[2]);
		std::string message = formatMessage(client, client.getNickname(), "TOPIC", channel->getName(), args[2]);
        channel->broadcast(&client, message);
        sendMessage(client.getFd(), message);
    }

    
}