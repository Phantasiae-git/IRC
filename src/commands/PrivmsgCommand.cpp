#include "../../includes/commands/PrivmsgCommand.hpp"

PrivmsgCommand::PrivmsgCommand() {}
PrivmsgCommand::~PrivmsgCommand() {}

std::string writeMsg(std::string src, std::string dest, std::string msg) {
	std::ostringstream oss;
	oss << ":" << src << " PRIVMSG " << dest
	<< " " << msg << "\n";
	return oss.str();
}

void PrivmsgCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {

	if (!client.isAthenticated()) {
		return ;
	}
	if (args.size() < 3) {
		sendError(client.getFd(), 461, client.getNickname(), "PRIVMSG", "Not enough parameters");
		return;
	}
	Channel* channelOut = client.findChannel(args[1]);
	if (channelOut) {
		channelOut->broadcast(&client, writeMsg(client.getNickname(), args[1], args[2]));
		return ;
	}
	Client* clientOut = server.findClient(args[1]);
	if (clientOut) {
		std::string msg = writeMsg(client.getNickname(), args[1], args[2]);
		send(clientOut->getFd(), msg.c_str(), msg.size(), 0);
	}
}