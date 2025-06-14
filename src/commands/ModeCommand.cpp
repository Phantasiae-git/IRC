#include "../../includes/commands/ModeCommand.hpp"

ModeCommand::ModeCommand()
{
}
ModeCommand::~ModeCommand()
{
}

void	ModeCommand::sendModeMessage(Channel* channel, Client* client, std::string mode) {
	std::string modeMsg = formatMessage(*client, client->getNickname(), "MODE", channel->getName(), mode);
	sendMessage(client->getFd(), modeMsg);
	channel->broadcast(client, modeMsg);
}

bool ModeCommand::is_allNumbers(const char *str)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		if(!isdigit(str[i]))
			return false;
	}
	return true;
}
void ModeCommand::execute(Server &server, Client &client, const std::vector<std::string> &args)
{
	if (!client.isAthenticated()) {
		return ;
	}
	if(args.size()<3)
	{
		sendError(client.getFd(), 461, client.getNickname(), " ", "Needs more parameters");
		return;
	}
	if(server.channels.find(args[1])==server.channels.end())
	{
		sendError(client.getFd(), 403, client.getNickname(), " ", "No such channel");
		return;
	}

	std::map<std::string, Channel *> channels;
	channels=client.getChannels();
	std::map<std::string, Channel *>::iterator it=channels.find(args[1]);

	if(it==channels.end())
	{
		sendError(client.getFd(), 442, client.getNickname(), " ", "You're not on the channel");
		return;
	}
	Channel *channel =it->second;
	if(!channel->isOperator(&client))
	{
		sendError(client.getFd(), 482, client.getNickname(), " ", "You're not a channel operator");
		return;
	}

	size_t indexFlagArgs = 3; //MODE #canal +k+ PASS 10
	char sign = 0;
	bool mode_after_sign = false;
	const std::string validModes = "itkol";

	for(size_t i = 0; i < args[2].size(); i++)
	{
		char c = args[2][i];
		if(c == '+' || c == '-')
		{
			if(sign == 0)
				sign = c;
			else if(c == sign && !mode_after_sign)
			{	
				sendError(client.getFd(), 101, client.getNickname(), args[1], "Sinal repetido"); //atualizar msg
				return;
			}
			else if(c != sign && !mode_after_sign)
			{	
				sendError(client.getFd(), 102, client.getNickname(), args[1], "Mal formatado"); //atualizar msg
				return;
			}
			else
			{
				sign = c;
				mode_after_sign = false;
			}
		}
		else
		{
			if(sign == 0)
			{	
				sendError(client.getFd(), 103, client.getNickname(), args[1], "No signal set '+' or '-'"); //atualizar msg
				return;
			}
			if(validModes.find(c) == std::string::npos)
			{	
				sendError(client.getFd(), 103, client.getNickname(), args[1], "Invalid MODE flag"); //atualizar msg
				return;
			}

			mode_after_sign = true;
			
			std::string arg = "";
			if ((c == 'k' && sign == '+') || c == 'o' || (c == 'l' && sign == '+'))
			{
				if (indexFlagArgs >= args.size())
				{
					sendError(client.getFd(), 461, client.getNickname(), " ", "Not enough parameters for mode");
					return;
				}
				arg = args[indexFlagArgs++];
			}

			if(c == 'i')
			{
				if(sign == '+')
					sendModeMessage(channel, &client, "+i");
				else
					sendModeMessage(channel, &client, "-i");
				channel->setInviteOnly(sign == '+');
			}
			else if(c == 't')
			{
				if(sign == '+')
					sendModeMessage(channel, &client, "+t");
				else
					sendModeMessage(channel, &client, "-t");
				channel->setT(sign == '+');
			}
			
			else if(c == 'k')
			{
				if(sign == '+')
				{
					if(!channel->getPassword().empty())
					{
						sendError(client.getFd(), 467, client.getNickname(), channel->getName(), "Channel key already set");
						return;
					}
					channel->setPassword(arg);
					sendModeMessage(channel, &client, "+k " + arg);
				}
				else if(sign == '-')
				{
					channel->setPassword("");
					sendModeMessage(channel, &client, "-k");
				}
			}
			else if(c == 'l')
			{
				if(sign == '+')
				{
					if(!is_allNumbers(arg.c_str()))
					{
						sendError(client.getFd(), 666, client.getNickname(), channel->getName(), "Only numbers pls"); //mudar msg
						return;
					}
					int limit = atoi(arg.c_str());
					if(limit < (int)channel->getUsers().size())
					{
						sendError(client.getFd(), 666, client.getNickname(), channel->getName(), "Set a bigger limit or kick some people first"); //mudar msg
						return;
					}
					channel->setLimitUsers(limit);
					std::stringstream ss;
					ss << limit;
					sendModeMessage(channel, &client, "+l " + ss.str());
				}
				else if(sign == '-')
				{
					channel->setLimitUsers(0);
					sendModeMessage(channel, &client, "-l");
				}
			}
			else if(c == 'o')
			{
				std::map<std::string, Client *> users = channel->getUsers();
				std::map<std::string, Client *>::iterator targetClient = users.find(arg);
				if(targetClient == users.end())
				{
					sendError(client.getFd(), 666, client.getNickname(), channel->getName(), "No such user on the channel"); //mudar msg
					return;
				}
				if(sign=='+')
				{
					sendModeMessage(channel, &client, "+o " + targetClient->second->getNickname());
					channel->addToOperators(targetClient->second);
				}
				else
				{
					sendModeMessage(channel, &client, "-o " + targetClient->second->getNickname());
					if(!channel->removeOp(targetClient->second))
						sendError(client.getFd(), 666, client.getNickname(), channel->getName(), "Target is not an operator on this channel");
				}
			}
		}		
	}
	if(!mode_after_sign)
	{
		sendError(client.getFd(), 999, client.getNickname(), channel->getName(), "Last signal dont have flag"); //mudar msg
		return;
	}
}