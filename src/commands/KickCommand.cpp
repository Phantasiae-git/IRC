#include "../../includes/commands/KickCommand.hpp"

KickCommand::KickCommand()
{
}
KickCommand::~KickCommand()
{
}

void KickCommand::execute(Server &server, Client &client, const std::vector<std::string> &args)
{
	if(args.size()<2)
	{
		std::cout << "(461) ERR_NEEDMOREPARAMS" << std::endl;
		return;
	}
	if(args[0][0]!='#')
	{
		std::cout << "(476) ERR_BADCHANMASK" << std::endl;
		return;
	}
	//RUN THROUGH SERVER CHANNELS TO CHECK FOR NOSUCHCHANNEL ERROR
	std::vector<Channel *> channels;
	channels=client.getChannels();
	Channel channel;
	int not_on_ch=1;
	for(std::vector<Channel *>::iterator it=channels.begin();it!=channels.end();it++)
	{
		if((*it)->getName()==args[0])
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
	
	
}
