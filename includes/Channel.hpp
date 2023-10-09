/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/06 14:07:40 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "irc.hpp"

class User;

class Channel
{
	private:
		std::vector<User *>			_users;
		std::vector<std::string>	_messages;
		std::string					_password;
		std::string const			_name;
		int							_mode;
		int							_max_users;
		std::string					_topic;
	
	public:
		// CONSTRUCTOR
		Channel();
		Channel(std::string);
		~Channel();
		// GETTERS
		std::vector<User *>			getUsers(void);
		std::vector<std::string>	getMessages(void);
		std::string					getPassword(void);
		int							getMode(void);
		std::string					getName(void);
		int							getMaxUsers(void);
		std::string					getTopic(void);
		// SETTERS
		void						setUsers(std::vector<User *>);
		void						setMessages(std::vector<std::string>);
		void						setPassword(std::string);
		void						setMode(int);
		void						setMaxUsers(int);
		void						setTopic(std::string);
};

#endif