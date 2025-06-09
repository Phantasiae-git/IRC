#include "Server.hpp"
#include "utils.hpp"

// int start_serv()
// {

//     struct sockaddr_storage client_addr;
//     socklen_t addr_size;
//     struct addrinfo ai;
//     struct addrinfo *aiptr;
//     int sockfd;
//     int clientfd;
//     int status;

//     memset(&ai, 0, sizeof(ai));
//     ai.ai_family=AF_INET;
//     ai.ai_socktype=SOCK_STREAM;
//     ai.ai_flags=AI_PASSIVE;
//     if(status= getaddrinfo(NULL, "6697", &ai, &aiptr)!=0)
//     {
//         std::cerr << "getaddrinfo error: "<< gai_strerror(status) << std::endl;
//         return(1);
//     }
// //check with aiptr every node of ai, sometimes the first isn't the right one
// if(sockfd=socket(ai.ai_family, ai.ai_socktype, ai.ai_protocol)==-1)
//     {
//         std::cerr << "socket error: "<< errno << std::endl;
//         return(1);
//     }
	
//     if(fcntl(sockfd, F_SETFL, O_NONBLOCK)!=0)
//     {
//         std::cerr << "setting non-block error: "<< errno << std::endl;
//         return(1);
//     }
//     if(bind(sockfd, ai.ai_addr, ai.ai_addrlen)!=0)
//     {
//         std::cerr << "bind error: "<< errno << std::endl;
//         return(1);
//     }

//     if(listen(sockfd, 20)!=0)
//     {
//         std::cerr << "listen error: "<< errno << std::endl;
//         return(1);
//     }
//     addr_size=sizeof client_addr;

// if(clientfd= accept(sockfd, (sockaddr *)&client_addr, &addr_size)==-1)
//     {
//         std::cerr << "accept error: "<< errno << std::endl;
//         return(1);
//     }

//     //communicate with socket

// freeaddrinfo(aiptr);
// close(clientfd);
// close(sockfd);
// return(0);
// }

int main(int argc, char **argv)
{
	if(argc != 3) {
		std::cout << "Usage: ./ircserv Port Password" << std::endl;
		return 1;
	}

	int port;
	if (isValidPort(argv[1], port) == false) {
		std::cerr << "Invalid port: " << argv[1] << " (must be a number between 1024 and 65535)" << std::endl;
		return 1;
	}

	Server server(port, argv[2]);
	if (!server.start()) {
		std::cerr << "failed to start server" << std::endl;
		return 1;
	}
	server.run();
	return 0;
}