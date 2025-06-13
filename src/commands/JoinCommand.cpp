#include "../../includes/commands/JoinCommand.hpp"

JoinCommand::JoinCommand() {}
	
JoinCommand::~JoinCommand() {}

void JoinCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {
	(void)server;
	(void)args;
	(void)client;
	/*if (client.isAthenticated() == false) {
		return ;
	}*/
	if (args[1][0] != '#') {
		sendError(client.getFd(), 476, client.getNickname(), args[1], "Bad Channel Mask");
	}
}