#include "../../includes/commands/TopicCommand.hpp"

TopicCommand::TopicCommand() {}
TopicCommand::~TopicCommand() {}


void TopicCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {

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
    std::vector<Channel *> channels;
	channels=client.getChannels();
	Channel channel;
	int not_on_ch=1;
	for(std::vector<Channel *>::iterator it=channels.begin();it!=channels.end();it++)
	{
		if((*it)->getName() == args[1])
		{
			not_on_ch = 0;
			channel=*(*it);
		}
	}
	if(not_on_ch)
	{
		std::cout << "(442) NOTONCHANNEL" << std::endl;
		return;
	}
	if(!channel.isOperator(&client) ) //&& channel.t)
	{
		std::cout << "(482) CHANOPRIVSNEEDED" << std::endl;
		return;
	}

    if(args.size() == 2)
    {
        if(channel.getTopic().empty())
           std::cout << "ESperar privmsg" << std::endl; //implementar priv msg //msg = <channel> :No topic is set
        else
            std::cout << "ESperar privmsg" << std::endl;//<channel> :<topic> ex 
    }
    else if(args.size() == 3)
    {
        std::cout << "ESperar privmsg" << std::endl;//set new topic
    }

    
}