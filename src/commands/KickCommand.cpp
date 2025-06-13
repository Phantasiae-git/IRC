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
	std::vector<Channel *> channels;
	channels=client.getChannels();
	Channel channel;
	int not_on_ch=1;
	for(std::vector<Channel *>::iterator it=channels.begin();it!=channels.end();it++)
	{
		if((*it)->getName()==args[1])
		{
			not_on_ch=0;
			channel=*(*it);
		}
	}
	if(not_on_ch)
	{
		std::cout << "(442) NOTONCHANNEL" << std::endl;
		return;
	}
	if(!channel.isOperator(&client))
	{
		std::cout << "(482) CHANOPRIVSNEEDED" << std::endl;
		return;
	}
	
	std::vector<Client *> members;
	members=channel.getUsers();
	
	for(std::vector<Client *>::iterator it= members.begin(); it!=members.end(); it++)
	{
		if((*it)->getUsername()==args[1])
			channel.removeUser(*it);
	}
}
