/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:46:23 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 17:08:23 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_pass(int fd, std::vector<std::string> command)
{
	if (command.size() != 2)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "PASS");
		return (false);
	}
	if (command[1].compare(this->_password))
	{
		ERR_PASSWDMISMATCH(this->_users[fd]);
		return (false);
	}
	this->_users[fd]->setConnected(1);
	this->_users[fd]->newConnection();
	return (true);
}
