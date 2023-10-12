/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:45:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/12 08:50:31 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_mode(int fd, std::vector<std::string> command)
{
	std::string	modestring;
	size_t		args_num = 3;
	size_t		i;
	char		op;
	
	if (command.size() < 3)
	{
		if (command.size() == 2)
		{
			if (command[1][0] == '+' || command[1][0] == '-')
			{
				for (i = 0; i < this->_channels.size(); i++)
				{
					if (command[1] == this->_channels[i]->getName())
						break ;
				}
				if (i == this->_channels.size())
				{
					ERR_NOSUCHCHANNEL(this->_users[fd], command[1]);
					return (false);
				}
			}
			RPL_CHANNELMODEIS(this->_users[fd], this->_channels[i]);
			return (false);
		}
		ERR_BADCHANMASK(this->_users[fd]);
		return (false);
	}

	if (command[1][0] != '#')
	{
		ERR_BADCHANMASK(this->_users[fd]);
		return (false);
	}
	
	// search if the channel exist
	for (i = 0; i < this->_channels.size(); i++)
	{
		if (command[1] == this->_channels[i]->getName())
			break ;
	}
	if (i == this->_channels.size())
	{
		ERR_NOSUCHCHANNEL(this->_users[fd], command[1]);
		return (false);
	}
	
	// check if the user is allowed to change the mode
	if (this->_channels[i]->getPrivilegeFor(this->_users[fd]) != OPERATOR)
	{
		ERR_CHANOPRIVSNEEDED(this->_users[fd], this->_channels[i]);
		return (false);
	}
	modestring = command[2];
	if (modestring[0] != '+' && modestring[0] != '-')
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "MODE");
		return (false);
	}
	// en mode charlou
	else if (modestring[0] == '-')
		op = '-';
	else if (modestring[0] == '+')
		op = '+';
	for (size_t j = 1; j < modestring.size(); j++)
	{
		if (isalpha(modestring[j]))
		{
			switch(modestring[j])
			{
				case 'i': 
					if (op == '+')
					{
						if (!this->_channels[i]->isMode('i'))
							this->_channels[i]->addMode('i');
					}
					else if (this->_channels[i]->isMode('i'))
						this->_channels[i]->removeMode('i');
					break;
				case 'k': 
					if (op == '+')
					{
						if (command.size() <= args_num)
						{
							ERR_NEEDMOREPARAMS(this->_users[fd], "MODE");
							return (false);
						}
						if (!this->_channels[i]->isMode('k'))
							this->_channels[i]->addMode('k');
						this->_channels[i]->setPassword(command[args_num++]);
					}
					else if (this->_channels[i]->isMode('k'))
					{
						this->_channels[i]->removeMode('k');
						this->_channels[i]->setPassword("");
					}
					break;
				case 'l':
					if (op == '+')
					{
						if (command.size() <= args_num)
						{
							ERR_NEEDMOREPARAMS(this->_users[fd], "MODE");
							return (false);
						}
						if (!this->_channels[i]->isMode('l'))
							this->_channels[i]->addMode('l');
						this->_channels[i]->setMaxUsers(atol(command[args_num++].c_str()));
					}
					else if (this->_channels[i]->isMode('l'))
					{
						this->_channels[i]->removeMode('l');
						this->_channels[i]->setMaxUsers(-1);
					}
					break;
				case 'o':
					if (command.size() <= args_num)
					{
						ERR_NEEDMOREPARAMS(this->_users[fd], "MODE");
						return (false);
					}
					if (!this->_channels[i]->getUser(command[args_num]))
					{
						ERR_NOSUCHNICK(this->_users[fd], command[args_num]);
						break ;
					}
					if (op == '+')
						this->_channels[i]->setPrivilegeFor(this->_channels[i]->getUser(command[args_num]), OPERATOR);
					else 
						this->_channels[i]->setPrivilegeFor(this->_channels[i]->getUser(command[args_num]), VOICE);
					this->_channels[i]->sendUsersList();
					break;
				case 't':
					if (op == '+')
					{
						if (!this->_channels[i]->isMode('t'))
							this->_channels[i]->addMode('t');
					}
					else if (this->_channels[i]->isMode('t'))
						this->_channels[i]->removeMode('t');
					break;
			}
		}
		else
		{
			if (modestring[j] == '+' || modestring[j] == '-')
				op = modestring[j];
		}
	}
	RPL_CHANNELMODEIS(this->_users[fd], this->_channels[i]);
	return (true);
}