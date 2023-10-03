/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/03 17:43:32 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

Channel::Channel() {}
Channel::~Channel() {}

Channel::Channel(int id): _id(id)
{
	this->_mode = OPEN;
	this->_password = "";
	this->_max_users = -1;
}

std::vector<User>	Channel::getUsers(void) { return this->_users; }

std::vector<std::string>	Channel::getMessages(void) { return this->_messages; }

std::string	Channel::getPassword(void) { return this->_password; }

int	Channel::getMode(void) { return this->_mode; }

int	Channel::getId(void) { return this->_id; }

int	Channel::getMaxUsers(void) { return this->_max_users; }

std::string	Channel::getTopic(void) { return this->_topic; }

void	Channel::setUsers(std::vector<User> users)
{
	this->_users = users;
	return ;
}

void	Channel::setMessages(std::vector<std::string> messages)
{
	this->_messages = messages;
	return ;
}

void	Channel::setPassword(std::string password)
{
	this->_password = password;
	return ;
}

void	Channel::setMode(int mode)
{
	this->_mode = mode;
	return ;
}

void	Channel::setMaxUsers(int max_users)
{
	this->_max_users = max_users;
	return ;
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
	return ;
}
