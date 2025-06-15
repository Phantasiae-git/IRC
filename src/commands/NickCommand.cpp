#include "../../includes/commands/NickCommand.hpp"

NickCommand::NickCommand() {}
NickCommand::~NickCommand() {}

/*
Verificar nicks iguais (loop)
*/

bool NickCommand::is_duplicateNick(const Server &server, const std::string &nick)
{
	const std::map<int, Client*> &clients = server.getClients();

	for (std::map<int, Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it) 
	{
		if (it->second && toUpper(it->second->getNickname()) == toUpper(nick))
			return true;
	}
	return false;
}

void NickCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {

	if (client.getPassword().empty()) 
	{
		sendError(client.getFd(), 1, client.getNickname(), "", "You must enter the password");
		return;
	}
	if(args.size() != 2 )
	{
		sendError(client.getFd(), 431, client.getNickname(), " ", "You didn't give a nickname");
		return;
	}

	if(!is_validNickOrUser(args[1]))
	{
		sendError(client.getFd(), 432, client.getNickname(), " ", "Not a valid nickname");
		return;
	}
	else if(is_duplicateNick(server, args[1]))
	{
		sendError(client.getFd(), 433, client.getNickname(), " ", "Nickname is already in use");
		return;
	}
	else
	{
		if(client.getNickname().empty())
			sendMessage(client.getFd(), "Introducing new nick " + args[1] + "\n");
		else
		{
			std::map<std::string, Channel *> channels = client.getChannels();
			for(std::map<std::string, Channel *>::iterator it= channels.begin(); it!=channels.end(); it++)
				it->second->broadcast(&client, client.getNickname() + ": changed his nickname to " + args[1]);
		}
		client.setNickname(args[1]);
	}
}
