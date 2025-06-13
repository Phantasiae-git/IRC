#ifndef UTILS_HPP
# define UTILS_HPP

#include <netdb.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sstream>
#include <map>
#include "Client.hpp"

int                         get_listen_sock(int port);
void                        *get_in_addr(sockaddr *sa);
bool                        isValidPort(const char* portStr, int& portOut);
std::vector<std::string>    split(const std::string &line);
std::string                 toUpper(const std::string& input);
void signalHandler(int signum);
bool	is_validNickName(const std::string &nickname);
void	sendMessage(int fd, std::string msg);

#endif