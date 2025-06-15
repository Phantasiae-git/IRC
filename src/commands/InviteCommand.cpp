#include "../../includes/commands/InviteCommand.hpp"
#include "../../includes/CommandHandler.hpp"

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
		sendError(client.getFd(), 461, client.getNickname(), "INVITE", "Not enough parameters");
		return;
	}
    std::map<std::string, Channel *> channels;
	channels=client.getChannels();
	std::map<std::string, Channel *>::iterator it=channels.find(args[2]);
	if(it==channels.end())
	{
		sendError(client.getFd(), 442, client.getNickname(), " ", "You're not on the channel\n");
		return;
	}
	Channel *channel =it->second;
	if(!channel->isOperator(&client))
	{
		sendError(client.getFd(), 482, client.getNickname(), " ", "You're not a channel operator\n");
		return;
	}
	std::map<int, Client *> clients = server.getClients();
	Client *victim = NULL;
	for(std::map<int, Client *>::iterator client_it=clients.begin(); client_it != clients.end(); client_it++)
	{
		if((client_it->second)->getNickname() == args[1])
		{
			victim = client_it->second;
		}
	}
	if(!victim)
	{
		sendError(client.getFd(), 401, args[1], " ", "No such nickname\n");
		return;
	}
	channels=victim->getChannels();
	it=channels.find(args[2]);
	if(it != channels.end())
	{
		sendError(client.getFd(), 443, victim->getNickname(), "", "User is already on channel\n");
		return;
	}

	CommandHandler handler;
	channel->addToInvited(victim);
	sendMessage(victim->getFd(), ":" + client.getPrefix() + " INVITE " + victim->getNickname() + " :" + channel->getName());
	handler.handle(server, *victim, "JOIN " + channel->getName());
	sendMessage(client.getFd(), ":ircserver 341 " + client.getNickname() + " " + victim->getNickname() + " " + channel->getName());
}
