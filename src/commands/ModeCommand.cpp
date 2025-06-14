#include "../../includes/commands/ModeCommand.hpp"

ModeCommand::ModeCommand()
{
}
ModeCommand::~ModeCommand()
{
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
			if(c == 'k' || c == 'o' || c == 'l')
			{
				if((sign == '+' || c == 'o') && indexFlagArgs >= args.size())
				{
					sendError(client.getFd(), 461, client.getNickname(), " ", "Needs more parameters");
					return;
				}
				arg = args[indexFlagArgs++];
			}

			if(c == 'i')
				channel->setInviteOnly(sign == '+');
			else if(c == 't')	
				channel->setT(sign == '+');
			
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

				}
				else if(sign == '-')
					channel->setPassword("");
			}
			else if(c == 'l')
			{
				if(sign == '+')
				{
					if(!is_allNumbers(arg.c_str()))
					{
                        sendError(client.getFd(), 666, client.getNickname(), channel->getName(), "Only numbers plss"); //mudar msg
                        return;
                    }
					int limit = atoi(arg.c_str());
					if(limit < channel->getUsers().size())
					{
                        sendError(client.getFd(), 666, client.getNickname(), channel->getName(), "Set a bigger limit or kick some people first"); //mudar msg
                        return;
                    }
					channel->setLimitUsers(limit);
				}
				else if(sign == '-')
					channel->setLimitUsers(0);
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
				channel->addToOperators(targetClient->second);
			}
		}
		
	}
	if(!mode_after_sign)
	{
		sendError(client.getFd(), 999, client.getNickname(), channel->getName(), "Last signal dont have flag"); //mudar msg
		return;
	}
}