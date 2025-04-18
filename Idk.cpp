#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <cstring>
#include <iostream>
#include <cstdlib>

int start_serv()
{

    struct sockaddr_storage client_addr;
    socklen_t addr_size;
    struct addrinfo ai;
    struct addrinfo *aiptr;
    int sockfd;
    int clientfd;
    int status;

    memset(&ai, 0, sizeof(ai));
    ai.ai_family=AF_INET;
    ai.ai_socktype=SOCK_STREAM;
    ai.ai_flags=AI_PASSIVE;
    if(status= getaddrinfo(NULL, "6697", &ai, &aiptr)!=0)
    {
        std::cerr << "getaddrinfo error: "<< gai_strerror(status) << std::endl;
        return(1);
    }

if(sockfd=socket(ai.ai_family, ai.ai_socktype, ai.ai_protocol)==-1)
    {
        std::cerr << "socket error: "<< errno << std::endl;
        return(1);
    }
    if(bind(sockfd, ai.ai_addr, ai.ai_addrlen)!=0)
    {
        std::cerr << "bind error: "<< errno << std::endl;
        return(1);
    }

    if(listen(sockfd, 20)!=0)
    {
        std::cerr << "listen error: "<< errno << std::endl;
        return(1);
    }
    addr_size=sizeof client_addr;

if(clientfd= accept(sockfd, (sockaddr *)&client_addr, &addr_size)==-1)
    {
        std::cerr << "accept error: "<< errno << std::endl;
        return(1);
    }

    //communicate with socket

freeaddrinfo(aiptr);
return(0);
}