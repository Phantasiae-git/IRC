#include "../../includes/commands/KickCommand.hpp"

KickCommand::KickCommand()
{
}
KickCommand::~KickCommand()
{
}

void KickCommand::execute(Server &server, Client &client, const std::vector<std::string> &args)
{
	if(args.size() < 3)
	{
		std::cout << "(461) ERR_NEEDMOREPARAMS" << std::endl;
		return;
	}
	if(args[1][0]!='#')
	{
		std::cout << "(476) ERR_BADCHANMASK" << std::endl;
		return;
	}
	if(server.channels.find(args[1])==server.channels.end())
	{
		std::cout << "(403) ERR_NOSUCHCHANNEL" << std::endl;
		return;
	}
	std::map<std::string, Channel *> channels;
	channels=client.getChannels();
	std::map<std::string, Channel *>::iterator it=channels.find(client.getUsername());
	if(it==channels.end())
	{
		std::cout << "(442) NOTONCHANNEL" << std::endl;
		return;
	}
	Channel *channel =it->second;
	if(!channel->isOperator(&client))
	{
		std::cout << "(482) CHANOPRIVSNEEDED" << std::endl;
		return;
	}
	
	channel->removeUser(args[2]);
}
