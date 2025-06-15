#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "ACommand.hpp"

class NickCommand : public ACommand
{
private:
    bool    is_duplicateNick(const Server &server, const std::string &nick);
    void	sendNickMessage(Channel* channel, Client* client, std::string args);

public:
    void execute(Server &server, Client &client, const std::vector<std::string> &args);
    NickCommand();
    ~NickCommand();
};

#endif