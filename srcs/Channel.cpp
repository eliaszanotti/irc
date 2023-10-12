/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/12 08:47:12 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

// Constructors
Channel::Channel() {}
Channel::~Channel() {}

Channel::Channel(std::string name): _name(name)
{
	this->_password = "";
	this->_max_users = -1;
	this->_symbol = SECRET_CHANNEL;
}

// Methods
void	Channel::addUser(User *user)
{
	this->_users.push_back(user);
}

void	Channel::addMode(char c)
{
	this->_modes.push_back(c);
}

bool	Channel::isMode(char c)
{
	for(std::vector<char>::iterator it = this->_modes.begin(); it != this->_modes.end(); it++)
    {
        if (*it == c)
			return (true);
    }
	return (false);
}

void	Channel::removeMode(char c)
{
	std::cout << "FIND : " << *std::find(_modes.begin(), _modes.end(), c) << std::endl;
	this->_modes.erase(std::find(_modes.begin(), _modes.end(), c)); 
}

void	Channel::removeUser(User *user)
{
	for (size_t i = 0; i < this->_users.size(); i++)
	{
		if (this->_users[i]->getNickname() == user->getNickname())
		{
			this->_users.erase(this->_users.begin() + i);
			return ;
		}
	}
}

void	Channel::sendUsersList(void)
{
	// Send the list of user in the channel
	for (size_t i = 0; i < this->getUsers().size(); i++)
	{		
		for (size_t j = 0; j < this->getUsers().size(); j++)
		{
			RPL_NAMREPLY(this->getUsers()[i], this, this->getUsers()[j]);
		}
		RPL_ENDOFNAMES(this->getUsers()[i], this);
	}
}

bool	Channel::haveTheUser(std::string nickname)
{
	size_t	i = 0;

	for (i = 0; i < this->getUsers().size(); i++)
	{
		if (this->getUsers()[i]->getNickname() == nickname)
			return (true);
	}
	return (false);
}

// Getters
User	*Channel::getUser(std::string nickname)
{
	for (size_t i = 0; i < this->_users.size(); i++)
	{
		if (this->_users[i]->getNickname() == nickname)
			return (this->_users[i]);
	}
	return (NULL);
}
std::vector<User *>			Channel::getUsers(void) { return this->_users; }
std::string					Channel::getPassword(void) { return this->_password; }

std::string	Channel::getModes(void)
{
	std::string	mode;
	mode = "+";
	for (size_t i = 0; i < this->_modes.size(); i++)
	{
		mode += this->_modes[i];
	}
	return (mode);
}

std::string					Channel::getName(void) { return this->_name; }
int							Channel::getMaxUsers(void) { return this->_max_users; }
std::string					Channel::getTopic(void) { return this->_topic; }
std::string					Channel::getSymbol(void) { return this->_symbol; }
char						Channel::getPrivilegeFor(User *user) { return this->_usersPrivileges[user]; }
std::string					Channel::getTopicInfos(void) { return (this->_topicInfos); }
std::vector<User *>			Channel::getInvitedUsers(void) { return (this->_invitedUsers); }

// Setters
void	Channel::setUsers(std::vector<User *> users) { this->_users = users; }
void	Channel::setPassword(std::string password) { this->_password = password; }
void	Channel::setMaxUsers(int max_users) { this->_max_users = max_users; }
void	Channel::setTopic(std::string topic) { this->_topic = topic; }
void	Channel::setSymbol(std::string symbol) { this->_symbol = symbol; }
void	Channel::setPrivilegeFor(User *user, char privilege) { this->_usersPrivileges[user] = privilege; }
void	Channel::setTopicInfos(std::string topicInfos) { this->_topicInfos = topicInfos; }
void	Channel::setInvitationFor(User *user) { this->_invitedUsers.push_back(user); }