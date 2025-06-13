#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "ACommand.hpp"

class JoinCommand : public ACommand
{
public:
	JoinCommand();
	~JoinCommand();

    void execute(Server &server, Client &client, const std::vector<std::string> &args);
};

#endif