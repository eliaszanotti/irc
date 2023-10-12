/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:24:15 by lpupier           #+#    #+#             */
/*   Updated: 2023/10/11 16:47:20 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_join(int fd, std::vector<std::string> command)
{
	std::vector<std::string>	channels;
	std::vector<std::string>	passwords;
	size_t						j = 0;

	if (command.size() < 2 || command.size() > 3)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "JOIN");
		return (false);
	}
	if (command[1][0] != '#')
	{
		ERR_BADCHANMASK(this->_users[fd]);
		return (false);
	}

	// Names and passwords
	channels = split(command[1], ',');
	if (command.size() == 3)
		passwords = split(command[2], ',');
	
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i][0] != '#')
			return (false);

		// Connection to an existing channel
		for (j = 0; j < this->_channels.size(); j++)
		{
			if (channels[i] == this->_channels[j]->getName())
			{
				if (this->_channels[j]->isMode('i'))
				{
					ERR_INVITEONLYCHAN(this->_users[fd], this->_channels[j]);
					break ;
				}
				// The channel is full
				if (this->_channels[j]->getUsers().size() == (size_t)this->_channels[j]->getMaxUsers())
				{
					ERR_CHANNELISFULL(this->_users[fd], this->_channels[j]);
					break ;
				}
				
				if (!this->_channels[j]->getPassword().empty())
				{
					if (i < passwords.size())
					{
						// Password gestion
						if (this->_channels[j]->getPassword() == passwords[i])
						{
							this->_connectToChannel(fd, this->_channels[j]);
						}
						else
						{
							ERR_BADCHANNELKEY(this->_users[fd], this->_channels[j]);
							return (false);
						}
					}
					else
					{
						ERR_BADCHANNELKEY(this->_users[fd], this->_channels[j]);
						return (false);
					}
				}
				else
					this->_connectToChannel(fd, this->_channels[j]);
				break ;
			}
		}

		// Create the channel and join it
		if (j == this->_channels.size())
		{
			Channel	*channel = new Channel(channels[i]);
			this->_channels.push_back(channel);
			this->_connectToChannel(fd, channel);
		}
	}
	return (true);
}

void	Server::_connectToChannel(int fd, Channel *channel)
{
	size_t	i;
	
	// Check if the user is already in the channel
	for (i = 0; i < channel->getUsers().size(); i++)
	{
		if (channel->getUsers()[i]->getNickname() == this->_users[fd]->getNickname())
		{
			std::cout << WARN_ICON << this->_users[fd]->getNickname() \
			<< " is already in " << channel->getName() << std::endl;
			return ;
		}
	}
	
	// Setup the new user
	if (i == channel->getUsers().size())
	{
		channel->addUser(this->_users[fd]);
		if (i == 0)
			channel->setPrivilegeFor(this->_users[fd], OPERATOR);
		else
			channel->setPrivilegeFor(this->_users[fd], VOICE);
	}

	for (size_t i = 0; i < channel->getUsers().size(); i++)
	{
		// Send the joining confirmation
		RPL_CMD(this->_users[fd], "JOIN", channel->getName());
		
		// Send the topic of the channel
		if (!channel->getTopic().empty())
			RPL_TOPIC(channel->getUsers()[i], channel);
		else
			RPL_NOTOPIC(channel->getUsers()[i], channel);
	}
	
	// Add the channel in the channels list of the user
	this->_users[fd]->setChannels(channel);

	// Set the last channel of the user
	this->_users[fd]->setLastChannel(channel->getName());
	
	// Send the list of user in the channel
	channel->sendUsersList();
}
