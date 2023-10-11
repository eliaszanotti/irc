/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:42:04 by elias             #+#    #+#             */
/*   Updated: 2023/10/11 15:40:45 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_invite(int fd, std::vector<std::string> command)
{
	std::map<int, User *>::iterator	it;
	size_t							i_channel = 0;

	// Bad command format
	if (command.size() > 3)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "INVITE");
		return (false);
	}

	// Invite is on display list mode
	if (command.size() == 1)
	{
		for (size_t i = 0; i < this->_users[fd]->getInvitedIn().size(); i++)
		{
			RPL_INVITELIST(this->_users[fd], this->_users[fd]->getInvitedIn()[i]);
		}
		RPL_ENDOFINVITELIST(this->_users[fd]);
		return (true);
	}

	// Get the invited channel
	for (i_channel = 0; i_channel < this->_channels.size(); i_channel++)
	{
		if (this->_channels[i_channel]->getName() == command[2])
			break ;
	}
	if (i_channel == this->_channels.size())
	{
		ERR_NOSUCHCHANNEL(this->_users[fd], command[2]);
		return (false);
	}

	// Get the invited user
	for (it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if (it->second->getNickname() == command[1])
			break ;
	}
	if (it == this->_users.end())
		return (false);

	// Check if the user who executed the command is on the channel
	if (!this->_channels[i_channel]->haveTheUser(this->_users[fd]->getNickname()))
	{
		ERR_NOTONCHANNEL(this->_users[fd], this->_channels[i_channel]);
		return (false);
	}

	// Check if the user who executed the command is an operator
	if (this->_channels[i_channel]->getPrivilegeFor(this->_users[fd]) != OPERATOR)
	{
		ERR_CHANOPRIVSNEEDED(this->_users[fd], this->_channels[i_channel]);
		return (false);
	}

	// Check if the invited user is already in the invited channel
	if (this->_channels[i_channel]->haveTheUser(this->_users[it->first]->getNickname()))
	{
		ERR_USERONCHANNEL(this->_users[fd], this->_channels[i_channel], this->_users[it->first]->getNickname());
		return (false);
	}

	// Send the invitation
	this->_channels[i_channel]->setInvitationFor(this->_users[it->first]);
	this->_users[it->first]->setInvitedIn(this->_channels[i_channel]->getName());

	INVITE_MESSAGE(this->_users[it->first], this->_channels[i_channel]->getName(), this->_users[fd]->getNickname());
	RPL_INVITING(this->_users[fd], this->_channels[i_channel], this->_users[it->first]->getNickname());
	
	return (true);
}