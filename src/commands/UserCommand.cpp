#include "../../includes/commands/UserCommand.hpp"

UserCommand::UserCommand() {}
UserCommand::~UserCommand() {}


bool UserCommand::is_duplicateUser(const Server &server, const std::string &user)
{
std::map<int, Client*> &clients = server.getClients();

	for (std::map<int, Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it) 
	{
		if (it->second && (it->second->getUsername()) == user)
			return true;
	}
	return false;
}

void UserCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {
	
	(void)server;
	if(client.getNickname().empty())
	{
		sendError(client.getFd(), 1, client.getNickname(), "", "You must set a NickName before use USER");
		return;
	}
	if(client.isRegistered())
	{
		sendError(client.getFd(), 462, client.getNickname(), " ", "You're already registered!\n");
		return;
	}

	if(args.size() != 2 )
	{
		sendError(client.getFd(), 461, client.getNickname(), " ", "Needs more parameters\n");
		return;
	}
	if(!is_validNickOrUser(args[1]))
	{
		sendError(client.getFd(), 432, client.getNickname(), " ", "Not a valid username\n");
		return;
	}
	else if(is_duplicateUser(server, args[1]))
	{
		sendError(client.getFd(), 433, client.getNickname(), " ", "Username is already in use\n");
		return;
	}

	client.setUsername(args[1]);
	client.setRegistered(true);
	sendMessage(client.getFd(), client.getNickname() + " Set a new user " + args[1] + "\n");

	if(client.getPassword() == server.getPassword())
	{
	   client.setAuthentication(true);
	   sendMessage(client.getFd(), "You have successfully enter on server\n");
	}   
}
