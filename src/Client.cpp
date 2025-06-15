#include "../includes/Client.hpp"

Client::Client(int fd)
: _fd(fd), _registered(false), _authenticated(false) {}

Client::~Client() {}

int Client::getFd() const {
	return _fd;
}

const std::string &Client::getNickname() const {
	return _nickname;
}

const std::string &Client::getUsername() const {
	return _username;
}

void Client::setNickname(const std::string &nickname) {
	_nickname = nickname;
}

void Client::setUsername(const std::string &username) {
	_username = username;
}


void Client::setPassword(const std::string &password) {
	_password = password;
}

std::string Client::getPassword() {
	return _password;
}

void Client::setRegistered(bool registered) {
	_registered = registered;
}

bool Client::isRegistered() const {
	return _registered;
}

void Client::setAuthentication(bool auth) {
	_authenticated = auth;
}

bool Client::isAthenticated() const {
	return _authenticated;
}

void Client::addChannel(std::string name, Channel *channel)
{
	channels.insert(std::make_pair(name, channel));
}

std::map<std::string, Channel *> Client::getChannels()
{
	return channels;
}

Channel* Client::findChannel(std::string name) {
	std::map<std::string, Channel*>::iterator it = channels.find(name);
	if (it != channels.end()) {
		return it->second;
	}
	return NULL;
}

void Client::removeChannel(Channel *channel)
{
	std::map<std::string, Channel *>::iterator channelpos= channels.find(channel->getName());
	if(channelpos==channels.end())
		return;
	channels.erase(channelpos);
}

std::string Client::getPrefix() const {
	return _nickname + "!" + _username + "@" + "localhost";
}