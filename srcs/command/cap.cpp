/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:45:50 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 08:45:51 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_cap(int fd)
{
	if (this->_users[fd]->getLogged())
	{
		sendTo(this->_users[fd], "You are already connected.\r\n");
		return (false);
	}
	sendTo(this->_users[fd], "Welcome to IRC, to login use: "\
		"\nPASS <password>\nNICK <nickname>\nUSER <name> 0 * :realname\n");
	return (true);
}