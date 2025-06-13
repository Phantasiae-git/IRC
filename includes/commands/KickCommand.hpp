#ifndef KICKCOMMAND_HPP
#define KICKCOMMAND_HPP

#include "ACommand.hpp"

class KickCommand : public ACommand
{
public:
    void execute(Server &server, Client &client, const std::vector<std::string> &args);
    KickCommand();
    ~KickCommand();
};

#endif