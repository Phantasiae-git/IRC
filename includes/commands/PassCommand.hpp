#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "ACommand.hpp"

class PassCommand : public ACommand
{
public:
    void execute(Server &server, Client &client, const std::vector<std::string> &args);
    PassCommand();
    ~PassCommand();
};

#endif