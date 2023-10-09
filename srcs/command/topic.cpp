/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:44:23 by elias             #+#    #+#             */
/*   Updated: 2023/10/09 17:38:55 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_topic(int fd, std::vector<std::string> command)
{
	size_t		i = 0;
	size_t		j = 0;
	std::string	new_topic;
	time_t		now = time(NULL);
	char*		dt = ctime(&now);

	// Errors
	if (command.size() < 3)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "TOPIC");
		return (false);
	}
	if (command[1][0] != '#')
		return (false);
	
	// Check if the channel exist
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

	// Check if the user is on the given channel
	for (j = 0; j < this->_channels[i]->getUsers().size(); j++)
	{
		if (this->_channels[i]->getUsers()[j] == this->_users[fd])
			break ;
	}
	if (j == this->_channels[i]->getUsers().size())
	{
		ERR_NOTONCHANNEL(this->_users[fd], this->_channels[i]);
		return (false);
	}

	// Check if the user has the privilege to change the topic
	if (this->_channels[i]->getPrivilegeFor(this->_users[fd]) != OPERATOR)
	{
		ERR_CHANOPRIVSNEEDED(this->_users[fd], this->_channels[i]);
		return (false);
	}

	// Update the topic
	for (j = 2; j < command.size(); j++)
	{
		if (j == 2)
			command[2].erase(0, 1);
		new_topic += (command[j] + " ");
	}
	this->_channels[i]->setTopic(new_topic);
	this->_channels[i]->setTopicInfos(this->_users[fd]->getNickname() + " " + dt);
	
	// Display the topic and informations
	for (size_t k = 0; k < this->_channels[i]->getUsers().size(); k++)
	{
		RPL_TOPIC(this->_channels[i]->getUsers()[k], this->_channels[i]);
		RPL_TOPICWHOTIME(this->_channels[i]->getUsers()[k], this->_channels[i]);
	}

	return (true);
}
