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
		sendError(client.getFd(), 476, client.getNickname(), " ", "Bad channel mask\n");
		return;
	}
    std::map<std::string, Channel *> channels;
	channels=client.getChannels();
	std::map<std::string, Channel *>::iterator it=channels.find(args[1]);
	if(it==channels.end())
	{
		sendError(client.getFd(), 442, client.getNickname(), " ", "You're not on the channel\n");
		return;
	}
	Channel *channel =it->second;
	if(!channel->isOperator(&client) && channel->getT() == true)
	{
		sendError(client.getFd(), 482, client.getNickname(), " ", "You're not a channel operator\n");
		return;
	}

    if(args.size() == 2)
    {
        if(channel->getTopic().empty())
           sendMessage(client.getFd(), args[1] + " :No topic is set\n");
        else
            sendMessage(client.getFd(), args[1] + " :" + channel->getTopic() + '\n');
    }
    else if(args.size() == 3)
    {
        channel->setTopic(args[2]);
        channel->broadCast(&client, ":" + client.getNickname() + " TOPIC " + channel->getName() + ": New Topic Define\n");
        sendMessage(client.getFd(), ":" + client.getNickname() + " TOPIC " + channel->getName() + ": New Topic Define\n");
    }

    
}