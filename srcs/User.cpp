/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/05 11:05:22 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

User::User() {}
User::~User() {}

User::User(pollfd pollfd)
{
	this->_pollfd = pollfd;
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
		send(this->_pollfd.fd, GREEN"----- You are now connected -----\n"RST);
	}
}

// Getters
std::string			User::getName(void) { return this->_name; }
std::string			User::getRealName(void) { return this->_name; }
std::string			User::getNickname(void) { return this->_nickname; }
std::map<int, int>	User::getPermission(void) { return this->_permission; }
int					User::getLogged(void) { return this->_logged; }
int					User::getConnected(void) { return this->_connected; }

// Setters
void	User::setName(std::string name) { this->_name = name; }
void	User::setRealName(std::string realname) { this->_realname = realname; }
void	User::setNickname(std::string nickname) { this->_nickname = nickname; }
void	User::setPermission(std::map<int, int> permission) { this->_permission = permission; }
void	User::setLogged(int logged) { this->_logged = logged; }
void	User::setConnected(int connected) { this->_connected = connected; }
