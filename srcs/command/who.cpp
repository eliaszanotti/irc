/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:24:49 by elias             #+#    #+#             */
/*   Updated: 2023/10/10 16:13:00 by elias            ###   ########.fr       */
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
	// size_t i;
	// for (i = 0; i < this->_users.size(); i++)
	// {
	// 	std::cout << "ok" << std::endl;
	// 	// std::cout << this->_users[i]->getName() << std::endl;
	// 	// if (this->_users[i]->getNickname() == command[1])
	// 		// break;
	
	// }
	std::map<int, User *>::iterator	it;
	for (it = this->_users.begin(); it != this->_users.end(); it++) 
	{
		// const int userFD = it->first;
		// const User* user = it->second;
		// std::cout << "ok"  << it->first << std::endl;
		// if (user)
			// std::cout << "ok" << userFD << user->getName() << std::endl;
		// std::cout << "User ID: " << userId << ", User Name: " << user->getName() << std::endl;
	}
		

	// std::cout << i << std::endl;
	// RPL_WHOREPLY(this->_users[fd], "*", "H", this->_users[i]);
	return (true);
}