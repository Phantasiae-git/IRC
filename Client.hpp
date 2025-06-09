#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
private:
    int         _fd;
    bool        _registered; // o cliente está ou não registado
    std::string _nickname;
    std::string _username;
    std::string _realname;
    //std::string _input_buffer; acho que é necessário guardar os dados recebidos para o caso de estarem incompletos ou appended a várias mensagens

    Client();
    Client(const Client &other);
    Client &operator=(const Client &other);

public:
    Client(int fd);
    ~Client();

    int getFd() const;

    const std::string &getNickname() const;
    const std::string &getUsername() const;
    const std::string &getRealname() const;
    void setNickname(const std::string &nickname);
    void setUsername(const std::string &username);
    void setRealname(const std::string &realname);
    void setRegistered(bool registered);
    bool isRegistered() const;

    //std::string &getInputBuffer();
    //void appendToBuffer(const std::string data)
    //void clearBufferUpTo(size_t pos)
};

#endif