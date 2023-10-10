/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:45:50 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 14:26:41 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_cap(int fd)
{
	if (this->_users[fd]->getLogged())
	{
		ERR_ALREADYREGISTERED(this->_users[fd]);
		return (false);
	}
	RPL_CMD(this->_users[fd], "CAP", "Welcome to IRC, to login use: "\
		"\nPASS <password>\nNICK <nickname>\nUSER <name> 0 * :realname\n");
	return (true);
}