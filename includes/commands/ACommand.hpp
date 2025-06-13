#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include "../Server.hpp"
#include "../Client.hpp"
#include <vector>

class ACommand
{
public:
    virtual void execute(Server &server, Client &client, const std::vector<std::string> &args) = 0;
    virtual ~ACommand();
};

#endif