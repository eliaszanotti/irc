/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:18:52 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 08:51:36 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool    Server::_privmsg(int fd, std::vector<std::string> command)
{
	for (size_t i = 0; i < command.size(); i++)
	{
		std::cout << command[i] << std::endl;
	}
		
	if (command.size() < 3)
	{
		sendTo(this->_users[fd], "Wrong command usage: PRIVMSG <user|#channel> :<msg>\n");
		return (false);
	}
	return (true);
}