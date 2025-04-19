#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <vector>
#include <arpa/inet.h>
#include <cerrno>

#define PORT 6667

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

void *get_in_addr(sockaddr *sa)
{
    return &(((sockaddr_in*)sa)->sin_addr);
}

int get_listen_sock()
{
    int listener;
    int yes=1;
    int rv;

    sockaddr_in server_addr;

    listener=socket(AF_INET, SOCK_STREAM, 0);//not sure se precisamos do getaddrinfo e checkar todos os nodes msm sendo só ipv4? :/
    if(listener<0)
    {
        std::cerr << "socket: " << errno << std::endl;
        return -1;
    }
    if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))<0)
    {
        std::cerr << "sockopt: " << errno << std::endl;
        return -1;
    }
    memset(&server_addr, 0, sizeof server_addr);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    if(bind(listener, (sockaddr *)&server_addr, sizeof server_addr)<0)
    {
        std::cerr << "bind: " << errno << std::endl;
        return -1;
    }

    if(listen(listener, 20)<0)
    {
        std::cerr << "listen: " << errno << std::endl;
        return -1;
    }

    return listener;
}

int main(int argc, char **argv)
{
    // if(argc!=3)
    // {
    //     std::cout << "usage: ./ircserv port password" << std::endl;
    //     return 1;
    // }
    // if(argv[1]!="6667")
    // {
    //     std::cout << "port is 6667" << std::endl;
    //     return 1;
    // }

    int listener= get_listen_sock();
    if(listener==-1)
    {
        std::cerr << "failed to create listener socket" << std::endl;
        return 1;
    }

    std::vector<pollfd> pfds;
    pfds.push_back((pollfd){listener, POLLIN, 0});

    while(1)
    {
        if(int act_socks = poll(&pfds[0], pfds.size(), -1)<0)
        {
            std::cerr << "poll failed: "<<errno << std::endl;
            return 1;
        }

        for(int i=0; i<pfds.size(); i++)
        {
            if(pfds[i].revents & (POLLIN | POLLHUP))
            {
                if(pfds[i].fd==listener)
                {
                    sockaddr_in client_addr;
                    socklen_t cl_addr_len =sizeof client_addr;

                    int clientfd= accept(listener, (sockaddr *)&client_addr, &cl_addr_len);
                    if(clientfd <0)
                    {
                        std::cerr << "accept failed: "<<errno << std::endl;
                    }
                    else
                    {
                        pfds.push_back((pollfd){clientfd, POLLIN, 0});
                        std::cout << "yay! new connection from " << inet_ntoa(client_addr.sin_addr) <<" on socket "<< clientfd << std::endl;
                    }

                }
                else
                {
                    char buf[256];
                    int nbytes= recv(pfds[i].fd, buf, sizeof buf, 0);
                    int sender_fd = pfds[i].fd;

                    if(nbytes<1)
                    {
                        if(nbytes<0)
                            std::cerr << "recv error: "<< errno << std::endl;
                        else
                            std::cerr << "socket shutdown"<< std::endl;
                        close(pfds[i].fd);
                        pfds.erase(pfds.begin() + i);
                        i--;
                    }
                    else
                    {
                        for(int j=0; j<pfds.size(); j++)
                        {
                            int dest_fd = pfds[j].fd;
                            if(dest_fd!=listener && dest_fd != sender_fd)
                            {
                                if (send(dest_fd, buf, nbytes, 0) == -1) {
                                    std::cerr << "send error: "<< errno << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}