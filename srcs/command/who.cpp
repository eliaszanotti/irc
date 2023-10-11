/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:24:49 by elias             #+#    #+#             */
/*   Updated: 2023/10/10 17:24:18 by elias            ###   ########.fr       */
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
	for (it = this->_users.begin(); it != this->_users.end(); it++) 
	{
		if (it->second->getNickname() == command[1])
			break;
	}
	if (it == this->_users.end())
	{
		ERR_NOSUCHNICK(this->_users[fd], command[1]);
		return (false);
	}
	RPL_WHOREPLY(this->_users[fd], "*", it->second); // TODO fix cette merde
	return (true);
}