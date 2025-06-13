#ifndef TOPICCOMMAND_HPP
#define TOPICCOMMAND_HPP

#include "ACommand.hpp"

class TopicCommand : public ACommand
{
public:
    void execute(Server &server, Client &client, const std::vector<std::string> &args);
    TopicCommand();
    ~TopicCommand();
};

#endif