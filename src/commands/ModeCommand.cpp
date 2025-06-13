#include "../../includes/commands/ModeCommand.hpp"

ModeCommand::ModeCommand()
{
}
ModeCommand::~ModeCommand()
{
}

void ModeCommand::execute(Server &server, Client &client, const std::vector<std::string> &args)
{
	if(args.size()<3)
	{
		sendError(client.getFd(), 461, client.getNickname(), " ", "Needs more parameters\n");
		return;
	}
	if(server.channels.find(args[1])==server.channels.end())
	{
		sendError(client.getFd(), 403, client.getNickname(), " ", "No such channel\n");
		return;
	}
	
}