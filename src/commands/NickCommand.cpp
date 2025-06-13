#include "../../includes/commands/NickCommand.hpp"

NickCommand::NickCommand() {}
NickCommand::~NickCommand() {}


bool	NickCommand::is_validNickName(const std::string &nickname)
{
	if (nickname.empty() || nickname.length() > 9)
		return (false);

	const std::string specialChars = "[]\\`^{}";

	if (!isalpha(nickname[0]) && specialChars.find(nickname[0]) == std::string::npos)
		return (false);

	for (size_t i = 1; i < nickname.length(); ++i)
	{
		if (!isalnum(nickname[i]) && specialChars.find(nickname[i]) == std::string::npos && nickname[i] != '-')
			return (false);
	}
	return (true);
}

/*
Verificar nicks iguais (loop)
*/

bool is_duplicateNick(const Server &server, const std::string &nick)
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
    if(args.size() < 2)
    {
        sendMessage(client.getFd(), "(431) ERR_NONICKNAMEGIVEN\n");
        return;
    }

    if(!is_validNickName(args[1]))
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
            server.broadCast(&client, client.getNickname() + ": changed his nickname to " + args[1]);
        client.setNickname(args[1]);
    }
}
