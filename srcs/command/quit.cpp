/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:28:46 by lpupier           #+#    #+#             */
/*   Updated: 2024/02/14 09:38:51 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_quit(int fd, std::vector<std::string> command)
{
	
	// Bad command format
	if (command.size() > 2)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "QUIT");
		return (false);
	}

	// Quit the server
	std::map<int, User *>::iterator it = this->_users.find(fd);
	if (command.size() == 2 && it != this->_users.end())
	{
			std::cout << DEL_ICON << fd << " left the server" << std::endl;
			this->_closeCurrentUser(fd);
	}
	
	
	return (true);
}