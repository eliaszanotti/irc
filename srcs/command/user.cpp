/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:55 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 11:03:57 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_user(int fd, std::vector<std::string> command)
{
	std::cout << "user() called" << std::endl;
	if (command.size() != 6)
		return (send(fd, "USER <realname> 0 * : <realname>\n"), true);
	if (command[2].compare("0"))
		return (send(fd, "USER <realname> 0 * : <realname>\n"), true);
	if (command[3].compare("*"))
		return (send(fd, "USER <realname> 0 * : <realname>\n"), true);
	if (command[4].compare(":"))
		return (send(fd, "USER <realname> 0 * : <realname>\n"), true);
	this->_users[fd]->setName(command[1]);
	this->_users[fd]->setRealName(command[5]);
	this->_users[fd]->newConnection();
	return (true);
}