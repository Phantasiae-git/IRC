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
		std::cout << "(476) ERR_BADCHANMASK" << std::endl;
		return;
	}
    std::map<std::string, Channel *> channels;
	channels=client.getChannels();
	std::map<std::string, Channel *>::iterator it=channels.find(args[1]);
	if(it==channels.end())
	{
		std::cout << "(442) NOTONCHANNEL" << std::endl;
		return;
	}
	Channel *channel =it->second;
	if(!channel->isOperator(&client) && channel->getT() == true)
	{
		std::cout << "(482) CHANOPRIVSNEEDED" << std::endl;
		return;
	}

    if(args.size() == 2)
    {
        if(channel->getTopic().empty())
           sendMessage(client.getFd(), args[1] + " :No topic is set\n");
        else
            sendMessage(client.getFd(), args[1] + " :" + channel->getTopic());
    }
    else if(args.size() == 3)
    {
        channel->setTopic(args[2]);
        channel->broadCast(&client, ":" + client.getNickname() + " TOPIC " + channel->getName() + ": New Topic Define\n");
        sendMessage(client.getFd(), ":" + client.getNickname() + " TOPIC " + channel->getName() + ": New Topic Define\n");
    }

    
}