/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:24:49 by elias             #+#    #+#             */
/*   Updated: 2023/10/11 15:53:07 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_who(int fd, std::vector<std::string> command)
{
	if (command.size() != 2)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "WHO");    
		return (false);
	}   
	std::map<int, User *>::iterator	it;
	if (command[1][0] == '#')
	{
		size_t i;
		for (i = 0; i < this->_channels.size(); i++)
		{
			if (command[1] == this->_channels[i]->getName())
			{
				std::vector<User *>	allUsers = this->_channels[i]->getUsers();
				for (size_t j = 0; j < allUsers.size(); j++)
					RPL_WHOREPLY(this->_users[fd], allUsers[j], this->_channels[i]->getName());
				break;
			}
		}		
		if (i == this->_channels.size())
		{
			ERR_NOSUCHCHANNEL(this->_users[fd], command[1]);
			return (false);
		}
	}
	else
	{
		for (it = this->_users.begin(); it != this->_users.end(); it++) 
		{
			if (it->second->getNickname() == command[1])
			{
				RPL_WHOREPLY(this->_users[fd], it->second, it->second->getLastChannel());
				break;
			}
		}
		if (it == this->_users.end())
		{
			ERR_NOSUCHNICK(this->_users[fd], command[1]);
			return (false);
		}
	}
	RPL_ENDOFWHO(this->_users[fd], command[1]);
	return (true);
}