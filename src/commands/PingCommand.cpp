#include "../../includes/commands/PingCommand.hpp"

PingCommand::PingCommand() {}
PingCommand::~PingCommand() {}

void PingCommand::execute(Server &server, Client &client, const std::vector<std::string> &args) {
	if (client.isAthenticated() == false) {
		return ;
	}
	// por implementar
}