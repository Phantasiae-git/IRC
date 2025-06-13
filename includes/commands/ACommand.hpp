#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include "../Server.hpp"
#include "../Client.hpp"
#include "../Channel.hpp"
#include <vector>

class ACommand
{
public:
    ACommand();
    virtual ~ACommand();

    virtual void execute(Server &server, Client &client, const std::vector<std::string> &args) = 0;
};

#endif