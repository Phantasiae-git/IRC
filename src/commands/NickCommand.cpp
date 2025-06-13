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
        std::cout << "You must enter the password\n" << std::endl;
        return;
    }
    if(args.size() != 2 )
    {
        std::cout << "(431) ERR_NONICKNAMEGIVEN\n" << std::endl;
        return;
    }

    if(!is_validNickOrUser(args[1]))
    {
        std::cout << "(432) ERR_ERRONEUSNICKNAME\n" << std::endl;
        return;
    }
    else if(is_duplicateNick(server, args[1]))
    {
        std::cout << "(433) ERR_NICKNAMEINUSE\n" << std::endl;
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
				it->second->broadCast(&client, client.getNickname() + ": changed his nickname to " + args[1]);
		}
        client.setNickname(args[1]);
    }
}
