#include "../../includes/commands/NickCommand.hpp"

NickCommand::NickCommand() {}
NickCommand::~NickCommand() {}

void NickCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {

    (void)server;
    if(args.size() < 2)
    {
        std::cerr << "ERR_NONICKNAMEGIVEN" << std::endl;
        return;
    }

    if(!is_validNickName(args[1]))
    {
        std::cerr << "NickName Invalid" << std::endl; //verificar se existe algum código de erro para isto
        return;
    }
    else
    {
        client.setNickname(args[1]);
        sendMessage(client.getFd(), "Nickname is set to " + args[1] + "\n");
    }
}
