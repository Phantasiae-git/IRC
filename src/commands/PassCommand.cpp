#include "../../includes/commands/PassCommand.hpp"

PassCommand::PassCommand() {}
PassCommand::~PassCommand() {}

void PassCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {

	(void)server;
	if (args[1].empty()) {
		sendMessage(client.getFd(), "(461) ERR_NEEDMOREPARAMS");
		return ;
	}
	else if (client.isRegistered()) {
		sendMessage(client.getFd(), "(462) ERR_ALREADYREGISTRED");
		return ;
	}
	else {
		client.setPassword(args[1]);
	}
}