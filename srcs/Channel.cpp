/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/09 17:23:14 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

// Constructors
Channel::Channel() {}
Channel::~Channel() {}

Channel::Channel(std::string name): _name(name)
{
	this->_mode = OPEN;
	this->_password = "";
	this->_max_users = -1;
	this->_symbol = SECRET_CHANNEL;
}

// Getters
std::vector<User *>			Channel::getUsers(void) { return this->_users; }
std::vector<std::string>	Channel::getMessages(void) { return this->_messages; }
std::string					Channel::getPassword(void) { return this->_password; }
int							Channel::getMode(void) { return this->_mode; }
std::string					Channel::getName(void) { return this->_name; }
int							Channel::getMaxUsers(void) { return this->_max_users; }
std::string					Channel::getTopic(void) { return this->_topic; }
std::string					Channel::getSymbol(void) { return this->_symbol; }
char						Channel::getPrivilegeFor(User *user) { return this->_usersPrivileges[user]; }
std::string					Channel::getTopicInfos(void) { return (this->_topicInfos); }

// Setters
void	Channel::setUsers(std::vector<User *> users) { this->_users = users; }
void	Channel::setMessages(std::vector<std::string> messages) { this->_messages = messages; }
void	Channel::setPassword(std::string password) { this->_password = password; }
void	Channel::setMode(int mode) { this->_mode = mode; }
void	Channel::setMaxUsers(int max_users) { this->_max_users = max_users; }
void	Channel::setTopic(std::string topic) { this->_topic = topic; }
void	Channel::setSymbol(std::string symbol) { this->_symbol = symbol; }
void	Channel::setPrivilegeFor(User *user, char privilege) { this->_usersPrivileges[user] = privilege; }
void	Channel::setTopicInfos(std::string topicInfos) { this->_topicInfos = topicInfos; }

// Methods
void	Channel::addUser(User *user)
{
	this->_users.push_back(user);
}

void	Channel::removeUser(User *user)
{
	for (size_t i = 0; i < this->_users.size(); i++)
	{
		if (this->_users[i]->getName() == user->getName())
		{
			this->_users.erase(this->_users.begin() + i);
			return ;
		}
	}
}
