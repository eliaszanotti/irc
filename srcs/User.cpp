/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/03 17:28:08 by elias            ###   ########.fr       */
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

std::string			User::getName(void) { return this->_name; }

std::string			User::getNickname(void) { return this->_nickname; }

std::map<int, int>	User::getPermission(void) { return this->_permission; }

void	User::setName(std::string name)
{
	this->_name = name;
	return ;
}

void	User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
	return ;
}
void	User::setPermission(std::map<int, int> permission)
{
	this->_permission = permission;
	return ;
}
