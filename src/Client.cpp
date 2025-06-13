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

void Client::addChannel(Channel *channel)
{
	channels.push_back(channel);
}

std::vector<Channel *> Client::getChannels()
{
	return channels;
}