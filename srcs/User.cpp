/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/05 10:55:59 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

User::User() {}
User::~User() {}

User::User(pollfd pollfd)
{
	this->_pollfd = pollfd;
}

// Getters
std::string			User::getName(void) const { return this->_name; }
std::string			User::getRealName(void) const { return this->_name; }
std::string			User::getNickname(void) const { return this->_nickname; }
std::map<int, int>	User::getPermission(void) const { return this->_permission; }
int					User::getLogged(void) const { return this->_logged; }
int					User::getConnected(void) const { return this->_connected; }
pollfd				User::getPollFd(void) const { return this->_pollfd; }
int					User::getFd(void) const { return this->_pollfd.fd; }

// Setters
void	User::setName(std::string name) { this->_name = name; }
void	User::setRealName(std::string realname) { this->_realname = realname; }
void	User::setNickname(std::string nickname) { this->_nickname = nickname; }
void	User::setPermission(std::map<int, int> permission) { this->_permission = permission; }
void	User::setLogged(int logged) { this->_logged = logged; }
void	User::setConnected(int connected) { this->_connected = connected; }
