#include "../includes/Server.hpp"

Server::Server(int port, std::string pswd)
    : _listener_fd(-1), _port(port), _password(pswd) {}

Server::~Server()
{
    std::cout << "Server destructor called" << std::endl;
}

void Server::acceptNewClient()
{
    // novo cliente
    sockaddr_in client_addr;
    socklen_t cl_addr_len = sizeof client_addr;

    int clientfd = accept(_listener_fd, (sockaddr *)&client_addr, &cl_addr_len);
    if (clientfd < 0)
    {
        std::cerr << "accept failed: " << errno << std::endl;
        return;
    }
    pfds.push_back((pollfd){clientfd, POLLIN, 0});
    std::cout << "yay! new connection from " << inet_ntoa(client_addr.sin_addr) << " on socket " << clientfd << std::endl;
    // adicionar cliente a um map
}

void Server::handleClientData(int i)
{
    // obter dados de um cliente existente
    // usar um std::map para guardar os clients e usar os fds como indice e.g., std::map<int, Client*> clients
    char buf[256];
    int nbytes = recv(pfds[i].fd, buf, sizeof buf, 0);
    int sender_fd = pfds[i].fd;

    if (nbytes < 1)
    {
        if (nbytes < 0)
            std::cerr << "recv error: " << errno << std::endl;
        else
            std::cerr << "socket shutdown" << std::endl;
        disconnectClient(i);
    }
    else
    {
        // Guardar mensagem no input_buffer (append()) para ser feita transmissão só de uma mensagens completa "\r\n" de cada vez
        // poderá haver no input_buffer partes da mensagem até estar completa ou mais do que uma mensagem completa obtida pelo recv()
        // loop para obter menssagem completa usar find() e substr()
        // usar outra string e.g, msg, para usar como mensagem completa
        // fazer erase do buffer

        // implementar comandos IMPORTANTANTE!!: é preciso fazer parsing da mensagem!
        for (size_t j = 0; j < pfds.size(); j++)
        {
            int dest_fd = pfds[j].fd;
            if (dest_fd != _listener_fd && dest_fd != sender_fd)
            {
                if (send(dest_fd, buf, nbytes, 0) == -1)
                { // usar a msg em vez de buf
                    std::cerr << "send error: " << errno << std::endl;
                }
            }
        }
    }
}
void Server::disconnectClient(int i)
{
    std::cout << "client disconnected on socket " << pfds[i].fd << std::endl;
    close(pfds[i].fd);
    pfds.erase(pfds.begin() + i);
}

bool Server::start()
{
    _listener_fd = get_listen_sock(_port);
    if (_listener_fd == -1)
    {
        std::cerr << "Failed to create listener socket" << std::endl;
        return false;
    }
    pfds.push_back((pollfd){_listener_fd, POLLIN, 0});
    std::cout << "Server started with port " << _port << std::endl;
    return true;
}

void Server::run()
{

    try
    {
        while (1)
        {
            int act_socks = poll(&pfds[0], pfds.size(), -1);
            if (act_socks < 0)
            {
                std::cerr << "poll failed: " << errno << std::endl;
                break;
            }

            for (size_t i = 0; i < pfds.size(); i++)
            {
                if (pfds[i].revents & (POLLIN))
                {
                    if (pfds[i].fd == _listener_fd)
                    {
                        acceptNewClient();
                    }
                    else
                    {
                        handleClientData(i);
                    }
                }
                else if (pfds[i].revents & POLLHUP)
                {
                    disconnectClient(i);
                    --i;
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        for (size_t i = 0; i < pfds.size(); i++)
            disconnectClient(i--);
        std::cerr << e.what() << '\n';
    }
}