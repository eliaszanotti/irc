/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/03 17:32:55 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "irc.hpp"

class Channel
{
	private:
		std::vector<User>			_users;
		std::vector<std::string>	_messages;
		std::string					_password;
		int							_mode;
		int							_id;
		std::string					_topic;
	public:
		//  CONSTRUCTOR
		Channel();
		Channel(int);
		~Channel();
		//  SETTER & GETTER
		std::vector<User>			getUsers(void);
		std::vector<std::string>	getMessages(void);
		std::string					getPassword(void);
		int							getMode(void);
		std::string					getTopic(void);
		void						setUsers(std::vector<User>);
		void						setMessages(std::vector<std::string>);
		void						setPassword(std::string);
		void						setMode(int);
		void						setTopic(std::string);
};

#endif