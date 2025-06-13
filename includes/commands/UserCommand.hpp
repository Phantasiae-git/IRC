#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "ACommand.hpp"

class UserCommand : public ACommand
{
public:
    void execute(Server &server, Client &client, const std::vector<std::string> &args);
    UserCommand();
    ~UserCommand();
};

#endif