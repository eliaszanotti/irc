/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/06 14:08:00 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

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
}

// METHODS
void	User::newConnection(void)
{
	if (this->getConnected() && !this->getNickname().empty() && !this->getName().empty() && !this->getRealName().empty())
	{
		this->_logged = 1;
		std::string output = "Welcome to our IRC " + this->getNickname() + " !\n";
		send(this->_pollFD.fd, output.c_str());
	}
}

// Getters
std::string			User::getName(void) const { return this->_name; }
std::string			User::getRealName(void) const { return this->_name; }
std::string			User::getNickname(void) const { return this->_nickname; }
std::map<int, int>	User::getPermission(void) const { return this->_permission; }
int					User::getLogged(void) const { return this->_logged; }
int					User::getConnected(void) const { return this->_connected; }
pollfd				User::getPollFd(void) const { return this->_pollFD; }
int					User::getFd(void) const { return this->_pollFD.fd; }

// Setters
void	User::setName(std::string name) { this->_name = name; }
void	User::setRealName(std::string realname) { this->_realname = realname; }
void	User::setNickname(std::string nickname) { this->_nickname = nickname; }
void	User::setPermission(std::map<int, int> permission) { this->_permission = permission; }
void	User::setLogged(int logged) { this->_logged = logged; }
void	User::setConnected(int connected) { this->_connected = connected; }