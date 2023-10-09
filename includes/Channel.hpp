/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/09 13:32:49 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "irc.hpp"

enum prefixChannel {
	SECRET_CHANNEL = '@',
	PUBLIC_CHANNEL = '=',
	PRIVATE_CHANNEL = '*'
};

enum privilege {
	FOUNDER = '~',
	PROTECTED = '&',
	OPERATOR = '@',
	HALFOP = '%',
	VOICE = '+'
};

class User;

class Channel
{
	private:
		std::vector<User *>			_users;
		std::map<User *, char>		_usersPrivileges;
		std::vector<std::string>	_messages;
		std::string					_password;
		std::string const			_name;
		int							_mode;
		int							_max_users;
		std::string					_topic;
		std::string					_symbol;
	
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
		std::string					getSymbol(void);
		char						getPrivilegeFor(User *);

		// SETTERS
		void						setUsers(std::vector<User *>);
		void						setMessages(std::vector<std::string>);
		void						setPassword(std::string);
		void						setMode(int);
		void						setMaxUsers(int);
		void						setTopic(std::string);
		void						setSymbol(std::string);
		void						setPrivilegeFor(User *, char);

		// METHODS
		void						addUser(User *);
		void						removeUser(User *);

};

#endif