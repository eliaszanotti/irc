/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:03 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 13:13:42by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	Server::_nick(int fd, std::vector<std::string> command)
{
	// Check args
	if (command.size() < 2 || command[1].empty()) //TODO fix split when >> "NICK " -> ["NICK", ""]
	{
		ERR_NONICKNAMEGIVEN(this->_users[fd]);
		return (false);
	}
	if (command.size() != 2)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "NICK");
		return (false);
	}
	// Check if nickname contain forbiden chars
	std::string	forbidenChars = " &#:\r\n\t\v";
	for (size_t i = 0; i < forbidenChars.size(); i++)
	{
        if (command[1].find(forbidenChars[i]) != std::string::npos)
		{
			ERR_ERRONEUSNICKNAME(this->_users[fd], command[1]);
			return (false);
        }
    }
	// Check if nickname is already used
	for (size_t i = 0; i < this->_users.size(); i++)
	{
		if (this->_users[i] && this->_users[i]->getNickname() == command[1])
		{
			ERR_NICKNAMEINUSE(this->_users[fd], command[1]);
			return (false);
		}
	}
	this->_users[fd]->setNickname(command[1]);
	this->_users[fd]->newConnection();
	return (true);
}