/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:03 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 09:44:57 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_nick(int fd, std::vector<std::string> command)
{
	if (command.size() != 2)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "NICK");
		return (false);
	}
	this->_users[fd]->setNickname(command[1]);
	this->_users[fd]->newConnection();
	return (true);
}