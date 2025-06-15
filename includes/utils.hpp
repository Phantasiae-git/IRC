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
#include <csignal>

int                         get_listen_sock(int port);
void                        *get_in_addr(sockaddr *sa);
bool                        isValidPort(const char* portStr, int& portOut);
std::vector<std::string>    split(const std::string &line);
std::string                 toUpper(const std::string& input);
void signalHandler(int signum);
bool	is_validNickOrUser(const std::string &nickoruser);
void	sendMessage(int fd, std::string msg);
void sendError(int fd, int errorn, std::string nickname, std::string channelname, std::string msg);
std::string formatMessage(const Client& client, const std::string& user, std::string cmd, const std::string args, const std::string& trailing);
std::string getHostname(const sockaddr* sa, socklen_t sa_len);

#endif