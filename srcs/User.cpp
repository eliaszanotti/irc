/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 18:20:22 by thibaultgir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

User::User() {}
User::~User() {}

User::User(pollfd pollfd)
{
	this->_pollfd = pollfd;
	this->_name = "";
}

// Getters
std::string			User::getName(void) { return this->_name; }
std::string			User::getNickname(void) { return this->_nickname; }
std::map<int, int>	User::getPermission(void) { return this->_permission; }
int					User::getLogged(void) { return this->_logged; }
int					User::getConnected(void) { return this->_connected; }

// Setters
void	User::setName(std::string name) { this->_name = name; }
void	User::setNickname(std::string nickname) { this->_nickname = nickname; }
void	User::setPermission(std::map<int, int> permission) { this->_permission = permission; }
void	User::setLogged(int logged) { this->_logged = logged; }
void	User::setConnected(int connected) { this->_connected = connected; }
