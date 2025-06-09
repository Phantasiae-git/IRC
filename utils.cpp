#include "utils.hpp"

void *get_in_addr(sockaddr *sa)
{
	return &(((sockaddr_in*)sa)->sin_addr);
}

int get_listen_sock()
{
	int listener_fd;
	int yes = 1;

	sockaddr_in server_addr;

	listener_fd=socket(AF_INET, SOCK_STREAM, 0);//not sure se precisamos do getaddrinfo e checkar todos os nodes msm sendo só ipv4? :/
	if(listener_fd < 0) {
		std::cerr << "socket: " << errno << std::endl;
		return -1;
	}
	if(setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
		std::cerr << "sockopt: " << errno << std::endl;
		return -1;
	}
	memset(&server_addr, 0, sizeof server_addr);
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=INADDR_ANY;

	if(bind(listener_fd, (sockaddr *)&server_addr, sizeof server_addr) < 0) {
		std::cerr << "bind: " << errno << std::endl;
		return -1;
	}

	if(listen(listener_fd, 20) < 0) {
		std::cerr << "listen: " << errno << std::endl;
		return -1;
	}

	return listener_fd;
}