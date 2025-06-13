#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include "Channel.hpp"
#include <vector>

class Channel;

class Client
{
private:
    int         _fd;
    bool        _registered;
    bool        _authenticated;
    std::string _nickname;
    std::string _username;

    std::string _password;
	  std::vector<Channel *> channels;


public:
    Client(int fd);
    ~Client();

    int getFd() const;

    const std::string &getNickname() const;
    const std::string &getUsername() const;
    const std::string &getRealname() const;
    void setNickname(const std::string &nickname);
    void setUsername(const std::string &username);

    void setPassword(const std::string &password);

    void setRegistered(bool registered);
    bool isRegistered() const;
    void setAuthentication(bool auth);
    bool isAthenticated() const;

	void addChannel(Channel *channel);
	std::vector<Channel *> getChannels();
	
    std::string getPassword();

};

#endif