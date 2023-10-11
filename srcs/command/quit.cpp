/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:28:46 by lpupier           #+#    #+#             */
/*   Updated: 2023/10/11 11:38:26 by lpupier          ###   ########.fr       */
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

	// Send the optionnal quit reason to others
	std::map<int, User *>::iterator it = this->_users.find(fd);
	if (command.size() == 2 && it != this->_users.end())
	{
			std::cout << DEL_ICON << fd << " leaved the server" << std::endl;
			this->_closeCurrentUser(fd);
	}

	// Quit the server
	
	return (true);
}