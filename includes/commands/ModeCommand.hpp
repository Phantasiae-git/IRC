#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "ACommand.hpp"
#include <cctype>

class ModeCommand : public ACommand
{
private:
    bool is_allNumbers(const char *str);

public:
    void execute(Server &server, Client &client, const std::vector<std::string> &args);
    ModeCommand();
    ~ModeCommand();
};

#endif