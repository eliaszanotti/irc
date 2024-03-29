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
	if (command.size() < 2)
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
	for (std::map<int, User*>::iterator it = this->_users.begin(); it != this->_users.end(); ++it) 
	{
		if (it->second->getNickname() == command[1])
		{
			ERR_NICKNAMEINUSE(this->_users[fd], command[1]);
			this->_users[fd]->setNickname(command[1]);
			return (false);
		}
	}

	// Change the user's nickname

	if (this->_users[fd]->getNickname().empty())
		this->_users[fd]->setNickname(command[1]);
	RPL_CMD(this->_users[fd], "NICK", command[1]);

	// Send to all channels the new nickname of the user
	for (size_t i = 0; i < this->_users[fd]->getChannels().size(); i++)
	{
		for (size_t j = 0; j < this->_users[fd]->getChannels()[i]->getUsers().size(); j++)
		{
			RPL_NICK(this->_users[fd]->getChannels()[i]->getUsers()[j], this->_users[fd], "NICK", command[1]);
		}
	}

	this->_users[fd]->setNickname(command[1]);

	if (!this->_users[fd]->getLogged())
		this->_users[fd]->newConnection();
	
	return (true);
}