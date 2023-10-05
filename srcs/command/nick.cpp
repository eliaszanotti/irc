/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:03 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 10:01:45 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_nick(int fd, std::vector<std::string> command)
{
	std::cout << "nick() called" << std::endl;
	if (command.size() != 2)
		return (send(fd, "Wrong amount of argument: usage:\nNICK <nickname>\n", 50, 0), true);
	this->_users[fd]->setNickname(command[1]);
	send(fd, this->_users[fd]->getNickname().c_str(), this->_users[fd]->getNickname().size(), 0);
	send(fd, " join the server\n", 18, 0);
	return (true);
}