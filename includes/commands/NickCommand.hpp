#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "ACommand.hpp"

class NickCommand : public ACommand
{
public:
    void execute(Server &server, Client &client, const std::vector<std::string> &args);
    NickCommand();
    ~NickCommand();
};

#endif