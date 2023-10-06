/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:55 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/06 13:25:59 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_user(int fd, std::vector<std::string> command)
{
	std::cout << "user() called" << std::endl;
	if (command.size() != 5)
		return (send(fd, "USER <realname> 0 * :<realname>\n"), true);
	if (command[2].compare("0"))
		return (send(fd, "USER <realname> 0 * :<realname>\n"), true);
	if (command[3].compare("*"))
		return (send(fd, "USER <realname> 0 * :<realname>\n"), true);
	if (command[4][0] == ':')
	this->_users[fd]->setName(command[1]);
	this->_users[fd]->setRealName(command[4].erase(0));
	this->_users[fd]->newConnection();
	return (true);
}