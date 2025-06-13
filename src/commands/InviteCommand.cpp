#include "../../includes/commands/InviteCommand.hpp"

InviteCommand::InviteCommand() {}
InviteCommand::~InviteCommand() {}

void InviteCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {

    (void)server;

    if (!client.isAthenticated()) 
    {
		return ;
	}
    if (args.size() < 3) 
    {
		sendError(client.getFd(), 461, client.getNickname(), "TOPIC", "Not enough parameters");
		return;
	}
}
