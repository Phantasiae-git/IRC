#include "../../includes/commands/ModeCommand.hpp"

ModeCommand::ModeCommand()
{
}
ModeCommand::~ModeCommand()
{
}

void ModeCommand::execute(Server &server, Client &client, const std::vector<std::string> &args)
{
	if(server.channels.find(args[1])==server.channels.end())
	{
		std::cout << "(403) ERR_NOSUCHCHANNEL" << std::endl;
		return;
	}
	
}