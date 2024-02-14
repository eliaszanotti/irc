/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:54:14 by lpupier           #+#    #+#             */
/*   Updated: 2024/02/14 10:03:20 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_part(int fd, std::vector<std::string> command)
{
	size_t						i = 0;
	size_t						j = 0;
	std::vector<std::string>	channels;
	

	// Bad command format
	if (command.size() != 3)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "PART");
		return (false);
	}

	// Check the channel
	channels = split(command[1], ',');
	for (i = 0; i < channels.size(); i++)
	{
		for (j = 0; j < this->_channels.size(); j++)
		{
			if (this->_channels[j]->getName() == channels[i])
			{
				for (size_t k = 0; k < this->_channels[j]->getUsers().size(); k++)
				{
					if (this->_channels[j]->getUsers()[k]->getNickname() == this->_users[fd]->getNickname())
					{
						RPL_CMD(this->_users[fd], "PART", this->_channels[j]->getName());

						for (size_t z = 0; z < this->_channels[j]->getUsers().size(); z++)
						{
							if (this->_channels[j]->getUsers()[z]->getNickname() != this->_users[fd]->getNickname())
								RPL_CMD_CHAN_OTHER(this->_channels[j]->getUsers()[z], this->_users[fd], "PART", this->_channels[j], command[2]);
						}

						this->_channels[j]->removeUser(this->_users[fd]);

						return (true);
					}
				}
				// The user is not on the provided channel
				ERR_NOTONCHANNEL(this->_users[fd], this->_channels[j]);
			}
		}
		// No channel with the provided name
		if (j == this->_channels.size())
			ERR_NOSUCHCHANNEL(this->_users[fd], channels[i]);
	}
	return (false);
}