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

int     get_listen_sock(int port);
void    *get_in_addr(sockaddr *sa);
bool    isValidPort(const char* portStr, int& portOut);

#endif