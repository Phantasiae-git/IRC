#include "../../includes/commands/JoinCommand.hpp"

JoinCommand::JoinCommand() {}
	
JoinCommand::~JoinCommand() {}

void JoinCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {

	if (!client.isAthenticated()) {
		return ;
	}
	if (args.size() < 2) {
		sendError(client.getFd(), 461, client.getNickname(), "JOIN", "Not enough parameters");
		return;
	}
	if (args[1].empty() || args[1][0] != '#') {
		sendError(client.getFd(), 476, client.getNickname(), args[1], "Bad Channel Mask");
		return;
	}
	std::map<std::string, Channel*>::iterator it = server.channels.find(args[1]);
	if (it != server.channels.end()) {
		if (!it->second->getPassword().empty()) {
			if (args.size() < 3 || it->second->getPassword() != args[2]) {
				sendError(client.getFd(), 475, client.getNickname(), it->first, "Cannot join channel (+k)");
				return ;
			}
			it->second->addUser(&client, args[2]);
		} 
		else
			it->second->addUser(&client, "");
		sendMessage(client.getFd(), "Joined Channel\n");
	}
	else {
		Channel* newChannel = new Channel(args[1], &client);
		if (args.size() >= 3 && !args[2].empty()) {
			newChannel->setPassword(args[2]);
		}
		server.channels.insert(std::make_pair(args[1], newChannel));
		sendMessage(client.getFd(), "Created Channel\n");
	}
}