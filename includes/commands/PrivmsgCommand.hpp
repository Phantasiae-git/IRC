#ifndef PRIVMSGCOMMAND_HPP
#define PRIVMSGCOMMAND_HPP

#include "ACommand.hpp"

class PrivmsgCommand : public ACommand
{
public:

	void execute(Server &server, Client &client, const std::vector<std::string> &args);
	PrivmsgCommand();
	~PrivmsgCommand();
};

#endif