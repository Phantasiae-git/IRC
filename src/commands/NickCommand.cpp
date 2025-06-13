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

    if (client.getPassword().empty()) {
        return;
    }
    if(args.size() != 2 )
    {
        sendMessage(client.getFd(), "(431) ERR_NONICKNAMEGIVEN\n");
        return;
    }

    if(!is_validNickOrUser(args[1]))
    {
        sendMessage(client.getFd(), "(432) ERR_ERRONEUSNICKNAME\n");
        return;
    }
    else if(is_duplicateNick(server, args[1]))
    {
        sendMessage(client.getFd(), "(433) ERR_NICKNAMEINUSE\n");
        return;
    }
    else
    {
        if(client.getNickname().empty())
            sendMessage(client.getFd(), "Introducing new nick " + args[1] + "\n");
        else
        {
			std::vector<Channel *> channels=client.getChannels();
			for(std::vector<Channel *>::iterator it= channels.begin(); it!=channels.end(); it++)
				(*it)->broadCast(&client, client.getNickname() + ": changed his nickname to " + args[1]);
        client.setNickname(args[1]);
		}
    }
}
