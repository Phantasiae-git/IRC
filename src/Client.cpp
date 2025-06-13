#include "../includes/Client.hpp"

Client::Client(int fd)
: _fd(fd) {}

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

void Client::setRegistered(bool registered) {
	_registered = registered;
}

bool Client::isRegistered() const {
	return _registered;
}

