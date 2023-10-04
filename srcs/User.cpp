/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 09:26:45 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

User::User() {}
User::~User() {}

User::User(std::string nickname)
{
	this->_nickname = nickname;
	this->_name = "";
}

// Getters
std::string			User::getName(void) { return this->_name; }
std::string			User::getNickname(void) { return this->_nickname; }
std::map<int, int>	User::getPermission(void) { return this->_permission; }

// Setters
void	User::setName(std::string name) { this->_name = name; }
void	User::setNickname(std::string nickname) { this->_nickname = nickname; }
void	User::setPermission(std::map<int, int> permission) { this->_permission = permission; }
