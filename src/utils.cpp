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
			result.push_back(word + rest);
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

void	signalHandler(int signum)
{
	(void)signum;
}

void	sendMessage(int fd, std::string msg) {
    send(fd, msg.c_str(), msg.size(), 0);
}
