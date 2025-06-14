#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include "Channel.hpp"
#include <vector>
#include <map>

class Channel;

class Client
{
private:
	int         _fd;
	bool        _registered;
	bool        _authenticated;
	std::string _nickname;
	std::string _username;
	std::string _hostname;

	std::string _password;
	std::map<std::string, Channel *> channels;

public:
	Client(int fd);
	~Client();

	int getFd() const;

	const std::string &getNickname() const;
	const std::string &getUsername() const;
	const std::string &getHostname() const;
	void setNickname(const std::string &nickname);
	void setUsername(const std::string &username);
	void setHostname(const std::string &username);

	void setPassword(const std::string &password);

	void setRegistered(bool registered);
	bool isRegistered() const;
	void setAuthentication(bool auth);
	bool isAthenticated() const;

	void addChannel(std::string name, Channel *channel);
	std::map<std::string, Channel *> getChannels();
	Channel* findChannel(std::string name);
	void removeChannel(Channel *channel);
	void removeFromAll();

	std::string getPassword();
	std::string getPrefix() const;

};

#endif