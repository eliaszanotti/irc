/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:24:15 by lpupier           #+#    #+#             */
/*   Updated: 2023/10/09 14:38:57 by elias            ###   ########.fr       */
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
							
						}
					}
				}
				else
				{
					this->_connectToChannel(fd, this->_channels[j]);
				}
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
		if (channel->getUsers()[i]->getName() == this->_users[fd]->getName())
		{
			std::cout << WARN_ICON << this->_users[fd]->getName() \
			<< " is already in " << channel->getName() << std::endl;
			break ;
		}
	}
	
	// Setup the new user
	if (i == channel->getUsers().size())
	{
		channel->addUser(this->_users[fd]);
		channel->setPrivilegeFor(this->_users[fd], FOUNDER);
	}

	// Send the confirmation to the user
	RPL_CMD(this->_users[fd], "JOIN", channel->getName());

	// Send the list of user in the channel
	for (std::map<int, User *>::iterator it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		RPL_NAMREPLY(this->_users[fd], channel, it->second);
	}
	RPL_ENDOFNAMES(this->_users[fd], channel);
}
