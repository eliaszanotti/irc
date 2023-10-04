/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 09:35:16 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

Channel::Channel() {}
Channel::~Channel() {}

Channel::Channel(std::string name): _name(name)
{
	this->_mode = OPEN;
	this->_password = "";
	this->_max_users = -1;
}

// Getters
std::vector<User>			Channel::getUsers(void) { return this->_users; }
std::vector<std::string>	Channel::getMessages(void) { return this->_messages; }
std::string					Channel::getPassword(void) { return this->_password; }
int							Channel::getMode(void) { return this->_mode; }
std::string					Channel::getName(void) { return this->_name; }
int							Channel::getMaxUsers(void) { return this->_max_users; }
std::string					Channel::getTopic(void) { return this->_topic; }

// Setters
void	Channel::setUsers(std::vector<User> users) { this->_users = users; }
void	Channel::setMessages(std::vector<std::string> messages) { this->_messages = messages; }
void	Channel::setPassword(std::string password) { this->_password = password; }
void	Channel::setMode(int mode) { this->_mode = mode; }
void	Channel::setMaxUsers(int max_users) { this->_max_users = max_users; }
void	Channel::setTopic(std::string topic) { this->_topic = topic; }
