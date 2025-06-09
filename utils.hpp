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

#define PORT 6667

int get_listen_sock();
void *get_in_addr(sockaddr *sa);

#endif