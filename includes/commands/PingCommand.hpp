#ifndef PINGCOMMAND_HPP
#define PINGCOMMAND_HPP

#include "ACommand.hpp"

class PingCommand : public ACommand
{
public:
    void execute(Server &server, Client &client, const std::vector<std::string> &args);
    PingCommand();
    ~PingCommand();
};

#endif