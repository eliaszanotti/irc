/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:03 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 17:02:09 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_nick(int fd, std::vector<std::string> command)
{
	if (command.size() != 2)
		return (send(fd, "Wrong amount of argument: usage:\nNICK <nickname>\n"), true);
	this->_users[fd]->setNickname(command[1]);
	// send(fd, this->_users[fd]->getNickname().c_str());
	this->_users[fd]->newConnection();
	return (true);
}