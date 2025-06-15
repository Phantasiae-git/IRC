#include "../../includes/commands/JoinCommand.hpp"

JoinCommand::JoinCommand() {}
	
JoinCommand::~JoinCommand() {}

void sendJoinReplies(Channel *chan, Client *client, std::string channelName) {
	std::string joinMsg = formatMessage(*client, client->getNickname(), "JOIN", channelName, "");
	sendMessage(client->getFd(), joinMsg);
	chan->broadcast(client, joinMsg);
	if (chan->getTopic().empty())
		sendMessage(client->getFd(), ":ircserver 331 " + client->getNickname() + " " + channelName + " :No topic is set");
	else
		sendMessage(client->getFd(), ":ircserver 332 " + client->getNickname() + " " + channelName + " :" + chan->getTopic() + "");
	std::string userList = chan->getFormattedUserList();
	sendMessage(client->getFd(), ":ircserver 353 " + client->getNickname() + " = " + channelName + " :" + userList);
	sendMessage(client->getFd(), ":ircserver 366 " + client->getNickname() + " " + channelName + " :End of /NAMES list");
}

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
		} 
		if(it->second->getInviteOnly())
		{
			if(!(it->second->isInvited(&client)))
			{
				sendError(client.getFd(), 473, client.getNickname(), it->first, "Cannot join channel (+i)");
				return ;
			}
		}
		if((it->second->getLimitUsers()>0) && (it->second->getLimitUsers() <= it->second->getUsers().size()))//>0 means it exists
		{
			sendError(client.getFd(), 471, client.getNickname(), it->first, "Cannot join channel (+l)");
			return;
		}
		it->second->addUser(&client, "");
		sendMessage(client.getFd(), ":" + client.getNickname() + " JOIN :" + args[1]);
		sendJoinReplies(it->second, &client, args[1]);
	}
	else {
		Channel* newChannel = new Channel(args[1], &client);
		server.channels.insert(std::make_pair(args[1], newChannel));
		if (args.size() >= 3 && !args[2].empty()) {
			newChannel->setPassword(args[2]);
		}
		sendJoinReplies(newChannel, &client, args[1]);
	}
}