/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:46:23 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 10:08:41 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_pass(int fd, std::vector<std::string> command)
{
	std::cout << "pass() called" << std::endl;
	if (command.size() != 2)
		return (send(fd, "Wrong amount of argument: usage:\nPASS <password>\n", 50, 0), true);
	if (command[1].compare(this->_password))
		return (send(fd, "Wrong password\n", 16, 0), true);
	send(fd, "You're connected to the server\n", 32, 0);
	this->_users[fd]->setConnected(1);
	return (true);
}