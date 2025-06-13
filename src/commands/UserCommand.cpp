#include "../../includes/commands/UserCommand.hpp"

UserCommand::UserCommand() {}
UserCommand::~UserCommand() {}


bool UserCommand::is_duplicateUser(const Server &server, const std::string &user)
{
    const std::map<int, Client*> &clients = server.getClients();

    for (std::map<int, Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it) 
    {
        if (it->second && (it->second->getNickname()) == user)
            return true;
    }
    return false;
}

void UserCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {
    
    (void)server;
    if(client.getNickname().empty())
    {
        std::cout << "You must set a NickName before use USER\n" << std::endl;
        return;
    }
    if(client.isRegistered())
    {
        std::cout << "(462) ERR_ALREADYREGISTRED\n" << std::endl;
        return;
    }

    if(args.size() != 2 )
    {
        std::cout << "(461) ERR_NEEDMOREPARAMS\n" << std::endl;
        return;
    }
    if(!is_validNickOrUser(args[1]))
    {
        sendMessage(client.getFd(), "User Invalid\n"); //Trocar 
        return;
    }
    else if(is_duplicateUser(server, args[1]))
    {
        std::cout << "Error: Duplicate User\n" << std::endl;
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
