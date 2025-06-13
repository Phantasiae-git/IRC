#include "../../includes/commands/UserCommand.hpp"

UserCommand::UserCommand() {}
UserCommand::~UserCommand() {}


void UserCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {
    
    (void)server;

    if(client.getNickname().empty())
    {
        sendMessage(client.getFd(), "You must set a NickName before use USER\n");
        return;
    }
    if(client.isRegistered())
    {
        sendMessage(client.getFd(), "(462) ERR_ALREADYREGISTRED\n");
        return;
    }

    if(args.size() != 2 )
    {
        sendMessage(client.getFd(), "(461) ERR_NEEDMOREPARAMS\n");
        return;
    }
    if(!is_validNickOrUser(args[1]))
    {
        sendMessage(client.getFd(), "User Invalid\n"); //Trocar 
        return;
    }

    client.setUsername(args[1]);
    client.setRegistered(true);
    sendMessage(client.getFd(), client.getNickname() + " Set a new user " + args[1] + "\n");
}
