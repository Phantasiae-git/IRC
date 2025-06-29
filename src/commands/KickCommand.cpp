#include "../../includes/commands/KickCommand.hpp"

KickCommand::KickCommand()
{
}
KickCommand::~KickCommand()
{
}

void KickCommand::execute(Server &server, Client &client, const std::vector<std::string> &args)
{
	if (!client.isAthenticated()) {
		return ;
	}
	if(args.size() < 3)
	{
		sendError(client.getFd(), 461, client.getNickname(), " ", "Needs more parameters\n");
		return;
	}
	if(args[1][0]!='#')
	{
		sendError(client.getFd(), 476, client.getNickname(), " ", "Bad channel mask\n");
		return;
	}
	if(server.channels.find(args[1])==server.channels.end())
	{
		sendError(client.getFd(), 403, client.getNickname(), " ", "No such channel\n");
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
	if(!channel->isOperator(&client))
	{
		sendError(client.getFd(), 482, client.getNickname(), " ", "You're not a channel operator\n");
		return;
	}
	std::string reason = "";
	if (args.size() >= 4)
		reason = args[3];
	std::string message = formatMessage(client, client.getNickname(), "KICK", args[1] + " " + args[2], reason);
	channel->removeUser(args[2], &client, message);
}
