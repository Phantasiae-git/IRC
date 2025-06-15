#include "../../includes/commands/PrivmsgCommand.hpp"

PrivmsgCommand::PrivmsgCommand() {}
PrivmsgCommand::~PrivmsgCommand() {}

void PrivmsgCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {

	if (!client.isAthenticated()) {
		return ;
	}
	if (args.size() < 3) {
		sendError(client.getFd(), 461, client.getNickname(), "PRIVMSG", "Not enough parameters");
		return;
	}
	std::string msg = formatMessage(client, client.getNickname(), "PRIVMSG", args[1], args[2]);
	Channel* channelOut = client.findChannel(args[1]);
	if (channelOut) {
		channelOut->broadcast(&client, msg);
		return ;
	}
	Client* clientOut = server.findClient(args[1]);
	if (clientOut) {
		send(clientOut->getFd(), msg.c_str(), msg.size(), 0);
	}
}