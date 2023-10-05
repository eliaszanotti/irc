/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:18:52 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 11:49:21 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool    Server::_privmsg(int fd, std::vector<std::string> command)
{
	std::map<int, User *>::iterator it = this->_users.begin();
	for (; it != this->_users.end(); it++)
	{
		if (it->second->getNickname() == command[1])
			break ;
	}
	if (it == this->_users.end())
		send(fd, RED"no such user found\n"RST);
	else
	{
		send(it->first, BLUE);
		send(it->first, this->_users[fd]->getNickname());
		send(it->first, " > "RST);
		for (size_t i = 2; i < command.size(); i++)
		{
			send(it->first, command[i]);
			send(it->first, " ");
		}
		send(it->first, "\n");
	}
	return (true);
}