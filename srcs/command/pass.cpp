/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:46:23 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 08:50:58 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_pass(int fd, std::vector<std::string> command)
{
	if (command.size() != 2)
		return (sendTo(this->_users[fd], "Wrong amount of argument: usage:\nPASS <password>\n"), true);
	if (command[1].compare(this->_password))
		return (sendTo(this->_users[fd], "Wrong password\n"), true);
	this->_users[fd]->setConnected(1);
	this->_users[fd]->newConnection();
	return (true);
}