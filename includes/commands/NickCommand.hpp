#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "ACommand.hpp"

class NickCommand : public ACommand
{
private:
    bool    is_duplicateNick(const Server &server, const std::string &nick);

public:
    void execute(Server &server, Client &client, const std::vector<std::string> &args);
    NickCommand();
    ~NickCommand();
};

#endif