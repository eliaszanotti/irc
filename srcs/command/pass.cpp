/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:46:23 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 11:03:54 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_pass(int fd, std::vector<std::string> command)
{
	std::cout << "pass() called" << std::endl;
	if (command.size() != 2)
		return (send(fd, "Wrong amount of argument: usage:\nPASS <password>\n"), true);
	if (command[1].compare(this->_password))
		return (send(fd, "Wrong password\n"), true);
	this->_users[fd]->setConnected(1);
	this->_users[fd]->newConnection();
	return (true);
}