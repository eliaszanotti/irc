/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:45:50 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 14:30:45 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_cap(int fd)
{
	if (this->_users[fd]->getLogged())
	{
		send(fd, "You are already connected.\r\n");
		return (false);
	}
	std::cout << "cap() called" << std::endl;
	send(fd, "Welcome to irc, to login use: "\
		"\nPASS <password>\nNICK <nickname>\nUSER <name> 0 * : <realname>\n");
	return (true);
}