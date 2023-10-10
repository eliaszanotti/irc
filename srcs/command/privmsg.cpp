/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:18:52 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 16:01:20 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool    Server::_privmsg(int fd, std::vector<std::string> command)
{
	std::map<int, User *>::iterator	it;
	std::vector<std::string>		targets;
	std::string						messages;
	size_t							j;
	if (command.size() < 3)
	{
		if (command.size() == 2)
		{
			if (command[1][0] == ':')
				ERR_NORECIPIENT(this->_users[fd]);
			else
				ERR_NOTEXTTOSEND(this->_users[fd]);
			return (false);
		}
		ERR_NEEDMOREPARAMS(this->_users[fd], "PRIVMSG");
		return (false);
	}
	targets = split(command[1], ',');
	if (command[2][0] == ':')
		command[2].erase(0, 1);
	else
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "PRIVMSG");
		return (false);
	}
	for (size_t i = 0; i < targets.size(); i++)
	{
		if (targets[i][0] == '#')
		{
			for (j = 0; j < this->_channels.size(); j++)
			{
				if (targets[i] == this->_channels[j]->getName())
					break ;
			}
			if (j == this->_channels.size())
			{
				ERR_NOSUCHNICK(this->_users[fd], targets[i]);
			}
			else
			{
				for (size_t k = 2; k < command.size(); k++)
				{
					messages += command[k];
					messages += " ";
				}
				this->_users[fd]->sendToAll(this->_channels[j]->getUsers(), "PRIVMSG", this->_channels[j], messages);
			}
		}
		else
		{
			for (it = this->_users.begin(); it != this->_users.end(); it++)
			{
				if (it->second->getNickname() == targets[i])
					break ;
			}
			if (it == this->_users.end())
			{
				ERR_NOSUCHNICK(this->_users[fd], targets[i]);
			}
			else
			{
				for (size_t k = 2; k < command.size(); k++)
				{
					messages += command[k];
					messages += " ";
				}
				RPL_CMD_TARGET(this->_users[fd], this->_users[it->first], "PRIVMSG", messages);
			}
		}
		
	}
	return (true);
}