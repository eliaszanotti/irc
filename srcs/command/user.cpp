/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:55 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 09:40:54 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_user(int fd, std::vector<std::string> command)
{
	if (this->_users[fd]->getLogged())
	{
		ERR_ALREADYREGISTERED(this->_users[fd]);
		return (false);
	}
	if (command.size() != 5)
	{
		RPL_CMD(this->_users[fd], "CAP", "USER <realname> 0 * :<realname>\n");
		return (false);
	}
	if (command[2].compare("0") || command[3].compare("*") || command[4][0] != ':')
	{
		RPL_CMD(this->_users[fd], "CAP", "USER <realname> 0 * :<realname>\n");
		return (false);
	}
	this->_users[fd]->setName(command[1]);
	this->_users[fd]->setRealName(command[4].erase(0));
	this->_users[fd]->newConnection();
	return (true);
}