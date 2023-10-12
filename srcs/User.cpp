/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/12 10:22:06 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"
# include "User.hpp"

User::User() {}
User::~User() {}

User::User(pollfd pollFD)
{
	this->_pollFD = pollFD;
	this->_connected = 0;
	this->_logged = 0;
	this->_nickname = "";
	this->_realname = "";
	this->_name = "";
	this->_lastChannel = "*";
}

// METHODS
void	User::newConnection(void)
{
	if (this->getConnected() && !this->getNickname().empty() && !this->getName().empty() && !this->getRealName().empty())
	{
		this->_logged = 1;
		std::string		path = "srcs/motd.config";
		std::ifstream	infile;
		std::string		line;

		infile.open(path.c_str(), std::ios::in);
		RPL_MOTDSTART(this);
		while (getline(infile, line))
			RPL_MOTD(this, line);
		RPL_ENDOFMOTD(this);
	}
}

void	User::sendToAll(std::vector<User *> users, std::string cmd, Channel *channel, std::string msg)
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (this->getNickname() != users[i]->getNickname())
			RPL_CMD_CHAN_OTHER(users[i], this, cmd, channel, msg);
	}
}

void	User::eraseInvitation(std::string str)
{
	std::vector<std::string>::iterator it;
	it = std::find(this->_invitedIn.begin(), this->_invitedIn.end(), str);
	if (it != this->_invitedIn.end())
		this->_invitedIn.erase(it);
}

void	User::removeChannel(Channel *channel)
{
	for (size_t	i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i]->getName() == channel->getName())
			this->_channels.erase(this->_channels.begin() + i);
	}
}

void	User::clearChannels(void)
{
	this->_channels.clear();
}

// Getters
std::string					User::getName(void) const { return this->_name; }
std::string					User::getRealName(void) const { return this->_name; }
std::string					User::getNickname(void) const { return this->_nickname; }
std::map<int, int>			User::getPermission(void) const { return this->_permission; }
int							User::getLogged(void) const { return this->_logged; }
int							User::getConnected(void) const { return this->_connected; }
pollfd						User::getPollFd(void) const { return this->_pollFD; }
int							User::getFd(void) const { return this->_pollFD.fd; }
std::vector<std::string>	User::getInvitedIn(void) const { return this->_invitedIn; }
std::string					User::getLastChannel(void) const { return this->_lastChannel; }
std::vector<Channel *>		User::getChannels(void) const { return this->_channels; }

// Setters
void	User::setName(std::string name) {this->_name = name; }
void	User::setRealName(std::string realname) {this->_realname = realname; }
void	User::setNickname(std::string nickname) {this->_nickname = nickname; }
void	User::setPermission(std::map<int, int> permission) {this->_permission = permission; }
void	User::setLogged(int logged) {this->_logged = logged; }
void 	User::setConnected(int connected) {this->_connected = connected; }
void	User::setInvitedIn(std::string channelName) {this->_invitedIn.push_back(channelName); }
void	User::setLastChannel(std::string lastChannel) {this->_lastChannel = lastChannel; }
void	User::setChannels(Channel *channel) { this->_channels.push_back(channel); }
