/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:03 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 08:55:12 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_nick(int fd, std::vector<std::string> command)
{
	if (command.size() != 2)
		return (sendTo(this->_users[fd], "Wrong amount of argument: usage:\nNICK <nickname>\n"), true);
	this->_users[fd]->setNickname(command[1]);
	// sendTo(this->_users[fd], this->_users[fd]->getNickname());
	this->_users[fd]->newConnection();
	return (true);
}