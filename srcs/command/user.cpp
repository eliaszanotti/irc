/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:55 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 13:09:43 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_user(int fd, std::vector<std::string> command)
{
	std::cout << "user() called" << std::endl;
	if (command.size() != 5)
		return (send(fd, "USER <realname> 0 * :<realname>\n", 34, 0), true);
	if (command[2].compare("0"))
		return (send(fd, "USER <realname> 0 * :<realname>\n", 34, 0), true);
	if (command[3].compare("*"))
		return (send(fd, "USER <realname> 0 * :<realname>\n", 34, 0), true);
	if (command[4][0] == ':')
		return (send(fd, "USER <realname> 0 * :<realname>\n", 34, 0), true);
	this->_users[fd]->setName(command[1]);
	this->_users[fd]->setRealName(command[4].erase(0));
	send(fd, this->_users[fd]->getNickname().c_str(), this->_users[fd]->getNickname().size(), 0);
	send(fd, " :", 3, 0);
	send(fd, this->_users[fd]->getName().c_str(), this->_users[fd]->getName().size(), 0);
	send(fd, " join the server\n", 18, 0);
	return (true);
}