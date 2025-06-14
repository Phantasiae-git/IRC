#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <map>
#include <string>
#include <cctype>
#include "Server.hpp"
#include "Client.hpp"
#include "utils.hpp"
#include "commands/ACommand.hpp"
#include "commands/NickCommand.hpp"
#include "commands/UserCommand.hpp"
#include "commands/PassCommand.hpp"
#include "commands/JoinCommand.hpp"
#include "commands/PrivmsgCommand.hpp"
#include "commands/TopicCommand.hpp"
#include "commands/InviteCommand.hpp"
#include "commands/KickCommand.hpp"
#include "commands/ModeCommand.hpp"

class CommandHandler
{
private:
    std::map<std::string, ACommand*> _commands;

public:
    CommandHandler();
    ~CommandHandler();

    void handle(Server &server, Client &client, const std::string &line);
};

#endif