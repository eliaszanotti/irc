/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/12 09:02:22 by tgiraudo         ###   ########.fr       */
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
		std::vector<User *>			_invitedUsers;
		std::map<User *, char>		_usersPrivileges;
		std::vector<std::string>	_messages;
		std::string					_password;
		std::string					_nb_users;
		std::string const			_name;
		std::vector<char>			_modes;
		int							_max_users;
		std::string					_symbol;
		std::string					_topic;
		std::string					_topicInfos;
	
	public:
		// CONSTRUCTOR
		Channel();
		Channel(std::string);
		~Channel();

		// METHODS
		void						addUser(User *);
		void						addMode(char c);
		bool						isMode(char c);
		void						removeMode(char c);
		void						removeUser(User *);
		void						sendUsersList(void);
		bool						haveTheUser(std::string);
		bool						isTheUserInvited(std::string);
		void						eraseInvitation(User *);
		
		// GETTERS
		User						*getUser(std::string);
		std::vector<User *>			getInvitedUsers(void);
		std::vector<User *>			getUsers(void);
		std::vector<std::string>	getMessages(void);
		std::string					getPassword(void);
		std::string					getModes(void);
		std::string					getName(void);
		int							getMaxUsers(void);
		std::string					getTopic(void);
		std::string					getSymbol(void);
		char						getPrivilegeFor(User *);
		std::string					getTopicInfos(void);
		

		// SETTERS
		void						setUsers(std::vector<User *>);
		void						setMessages(std::vector<std::string>);
		void						setPassword(std::string);
		void						setMode(int);
		void						setMaxUsers(int);
		void						setTopic(std::string);
		void						setSymbol(std::string);
		void						setPrivilegeFor(User *, char);
		void						setTopicInfos(std::string);
		void						setInvitationFor(User *);

};

#endif