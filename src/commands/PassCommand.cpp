#include "../../includes/commands/PassCommand.hpp"

PassCommand::PassCommand() {}
PassCommand::~PassCommand() {}

void PassCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {
	if(args.size()>2)
		return;
	(void)server;
	if (args[1].empty()) {
		sendError(client.getFd(), 461, client.getNickname(), " ", "Needs more parameters\n");
		return ;
	}
	else if (client.isRegistered()) {
		sendError(client.getFd(), 462, client.getNickname(), " ", "You're already registered!\n");
		return ;
	}
	else {
		client.setPassword(args[1]);
	}
}