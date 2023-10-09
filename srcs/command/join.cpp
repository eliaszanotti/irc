/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:24:15 by lpupier           #+#    #+#             */
/*   Updated: 2023/10/09 10:07:10 by lpupier          ###   ########.fr       */
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
							
						}
						else
						{
							
						}
					}
				}
				break ;
			}
		}

		// Create the channel and join it
		if (j == this->_channels.size())
		{
			Channel	*channel = new Channel(channels[i]);
			this->_channels.push_back(channel);

			std::string	output;
			output = ":" + this->_users[fd]->getNickname() + "!" + this->_users[fd]->getName() + "@" + IP_ADDR + " JOIN " + channel->getName() + "\r\n";

			for (std::map<int,User *>::iterator it = this->_users.begin(); it != this->_users.end(); ++it)
				send(it->second->getFd(), output.c_str());

			// 353
			output = ":" + SERVER("353") + this->_users[fd]->getNickname() + " " + "MODE" + " " + channel->getName() + " :" + "+nt" + this->_users[fd]->getNickname() + "\r\n";
			send(fd, output.c_str());
			// 366
			output = ":" + SERVER("366") + this->_users[fd]->getNickname() + " " + channel->getName() + " :End of /NAMES list\r\n";
			send(fd, output.c_str());
		}
	}
	return (true);
}