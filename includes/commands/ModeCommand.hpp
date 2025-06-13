#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "ACommand.hpp"

class ModeCommand : public ACommand
{
public:
    void execute(Server &server, Client &client, const std::vector<std::string> &args);
    ModeCommand();
    ~ModeCommand();
};

#endif