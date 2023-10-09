/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:24:15 by lpupier           #+#    #+#             */
/*   Updated: 2023/10/09 15:04:05 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_join(int fd, std::vector<std::string> command)
{
	std::vector<std::string>	channels;
	std::vector<std::string>	passwords;
	size_t						j = 0;

	if (command.size() > 3)
		return (false);
	if (command.size() < 2)
		return (false);
	if (command[1][0] != '#')
		return (false);

	// Names and passwords
	channels = split(command[1], ",");
	if (command.size() == 3)
		passwords = split(command[2], ",");
	
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i][0] != '#')
			return (false);

		// Connection to an existing channel
		for (j = 0; j < this->_channels.size(); j++)
		{
			if (channels[i] == this->_channels[j]->getName())
			{
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
			std::cout << RED << "[⚠] " << RST << this->_users[fd]->getNickname() \
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

		// Send the list of user in the channel
		for (size_t j = 0; j < channel->getUsers().size(); j++)
		{
			RPL_NAMREPLY(channel->getUsers()[i], channel, channel->getUsers()[j]);
		}
		RPL_ENDOFNAMES(this->_users[fd], channel);
	}
}
