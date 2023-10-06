/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:03 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/06 14:03:29 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_nick(int fd, std::vector<std::string> command)
{
	std::cout << "nick() called" << std::endl;
	if (command.size() != 2)
		return (send(fd, "Wrong amount of argument: usage:\nNICK <nickname>\n"), true);
	this->_users[fd]->setNickname(command[1]);
	// send(fd, this->_users[fd]->getNickname().c_str());
	this->_users[fd]->newConnection();
	return (true);
}