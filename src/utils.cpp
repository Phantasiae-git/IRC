#include "../includes/utils.hpp"

std::string toUpper(const std::string &input)
{
	std::string result = input;
	for (std::string::size_type i = 0; i < result.size(); ++i)
	{
		result[i] = std::toupper(static_cast<unsigned char>(result[i]));
	}
	return (result);
}

std::vector<std::string> split(const std::string &line)
{
	std::vector<std::string> result;
	std::istringstream iss(line);
	std::string word;
	while (iss >> word)
	{
		if (word[0] == ':')
		{
			std::string rest;
			std::getline(iss, rest);
			std::string trailing = word.substr(1) + rest;
			result.push_back(trailing);
			break ;
		}
		result.push_back(word);
	}
	return (result);
}

bool	isValidPort(const char *portStr, int &portOut)
{
	long	port;

	port = atol(portStr);
	if (port < 1024 || port > 65535)
	{
		return (false);
	}
	portOut = static_cast<int>(port);
	return (true);
}

void	*get_in_addr(sockaddr *sa)
{
	return (&(((sockaddr_in *)sa)->sin_addr));
}

int	get_listen_sock(int port)
{
	int			listener_fd;
	int			yes;
	sockaddr_in	server_addr;

	yes = 1;
	listener_fd = socket(AF_INET, SOCK_STREAM, 0);
		// not sure se precisamos do getaddrinfo e checkar todos os nodes msm sendo só ipv4? :/
	if (listener_fd < 0)
	{
		std::cerr << "socket: " << errno << std::endl;
		return (-1);
	}
	if (setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &yes,
			sizeof(int)) < 0)
	{
		std::cerr << "sockopt: " << errno << std::endl;
		return (-1);
	}
	memset(&server_addr, 0, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if (fcntl(listener_fd, F_SETFL, O_NONBLOCK) != 0)
	{
		std::cerr << "setting non-block error: " << errno << std::endl;
		return (1);
	}
	if (bind(listener_fd, (sockaddr *)&server_addr, sizeof server_addr) < 0)
	{
		std::cerr << "bind: " << errno << std::endl;
		return (-1);
	}
	if (listen(listener_fd, 20) < 0)
	{
		std::cerr << "listen: " << errno << std::endl;
		return (-1);
	}
	return (listener_fd);
}

void sendMessage(int fd, const std::string msg) {

	std::string newMsg = msg + "\r\n";
	send(fd, newMsg.c_str(), newMsg.size(), 0);
}

void sendError(int fd, int errorn, std::string nickname, std::string channelname, std::string msg) {
	std::ostringstream oss;
	oss << ":" << nickname << " " 
		<< errorn << " "
		<< channelname << " :"
		<< msg;

	std::string newMsg = oss.str() + "\r\n";
	send(fd, newMsg.c_str(), newMsg.size(), 0);
}

bool	is_validNickOrUser(const std::string &nickoruser)
{
	if (nickoruser.empty() || nickoruser.length() > 9)
		return (false);

	const std::string specialChars = "_[]\\`^{}";

	if (!isalpha(nickoruser[0]) && specialChars.find(nickoruser[0]) == std::string::npos)
		return (false);

	for (size_t i = 1; i < nickoruser.length(); ++i)
	{
        if(nickoruser[i] <= 32 || nickoruser[i] == 127)
            return (false);
		if (!isalnum(nickoruser[i]) && specialChars.find(nickoruser[i]) == std::string::npos && nickoruser[i] != '-')
			return (false);
	}
	return (true);
}

std::string formatMessage(const Client& client, const std::string& user, std::string cmd, const std::string args, const std::string& trailing)
{
	std::string prefix = ":" + user + "!" + client.getUsername() + "@localhost";
	std::string msg = prefix + " " + cmd + " " + args;
	if (!trailing.empty())
		msg += " :" + trailing;
	return msg + "\r\n";
}