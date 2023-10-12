/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:41:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/12 08:21:40 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_kick(int fd, std::vector<std::string> command)
{
	size_t		i = 0;
	size_t		j = 0;
	std::string	ban_reason;

	// Bad command format
	if (command.size() < 3)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "KICK");
		return (false);
	}

	// Bad channel format
	if (command[1][0] != '#')
	{
		ERR_BADCHANMASK(this->_users[fd]);
		return (false);
	}

	// The channel doesn't exist
	for (i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i]->getName() == command[1])
			break ;
	}
	if (i == this->_channels.size())
	{
		ERR_NOSUCHCHANNEL(this->_users[fd], command[1]);
		return (false);
	}

	// The user who executed the command is not on the provided channel
	if (!this->_channels[i]->haveTheUser(this->_users[fd]->getNickname()))
	{
		ERR_NOTONCHANNEL(this->_users[fd], this->_channels[i]);
		return (false);
	}

	// The provided user who will be banned is not on the provided channel
	for (j = 0; j < this->_channels[i]->getUsers().size(); j++)
	{
		if (this->_channels[i]->getUsers()[j]->getNickname() == command[2])
			break ;
	}
	if (j == this->_channels[i]->getUsers().size())
	{
		ERR_USERNOTINCHANNEL(this->_users[fd], command[2]);
		return (false);
	}

	// Check the privilege of the user who executed the command
	if (this->_channels[i]->getPrivilegeFor(this->_users[fd]) != OPERATOR)
	{
		ERR_CHANOPRIVSNEEDED(this->_users[fd], this->_channels[i]);
		return (false);
	}

	// Send the confirmation of the kick
	if (command.size() >= 4)
	{
		// Send the optionnal ban reason
		for (size_t k = 3; k < command.size(); k++)
			ban_reason.append(command[k] + " ");
		ban_reason = ban_reason.substr(0, ban_reason.size() - 1);
		
		for (size_t k = 0; k < this->_channels[i]->getUsers().size(); k++)
			KICK_WITH_REASON(this->_channels[i]->getUsers()[k], this->_users[fd], this->_channels[i], this->_channels[i]->getUsers()[j], ban_reason);
	}
	else
	{
		for (size_t k = 0; k < this->_channels[i]->getUsers().size(); k++)
			KICK_WITHOUT_REASON(this->_channels[i]->getUsers()[k], this->_users[fd], this->_channels[i], this->_channels[i]->getUsers()[j]);
	}

	// Kick the user in the data of the provided channel
	this->_channels[i]->removeUser(this->_channels[i]->getUsers()[j]);

	// Remove the channel in the channels list of the user
	this->_channels[i]->getUsers()[j]->removeChannel(this->_channels[i]);

	// Send the new user's list of the provided channel
	this->_channels[i]->sendUsersList();
	
	return (true);
}