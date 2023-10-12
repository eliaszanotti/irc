/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/12 09:08:11 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "irc.hpp"

class Channel;

class User 
{
	private:
		struct pollfd				_pollFD;
		std::vector<std::string>	_invitedIn;
		std::vector<Channel *>		_channels;
		int							_connected;
		int							_logged;
		std::string					_name;
		std::string					_realname;
		std::string					_nickname;
		std::map<int, int>			_permission;
		std::string					_lastChannel;
	
	public:
		// CONSTRUCTORS
		User();
		User(pollfd	pollFD);
		~User();
		
		// METHODS
		void						newConnection(void);
		void						sendToAll(std::vector<User *>, std::string, Channel *, std::string);
		void						eraseInvitation(std::string str);
		void						removeChannel(Channel *);
		void						clearChannels(void);
		
		// GETTERS
		std::string					getName(void) const;
		std::string					getRealName(void) const;
		std::string					getNickname(void) const;
		std::map<int, int>			getPermission(void) const;
		int							getLogged(void) const;
		int							getConnected(void) const;
		pollfd						getPollFd(void) const;
		int							getFd(void) const;
		std::vector<std::string>	getInvitedIn(void) const;
		std::string					getLastChannel(void) const;
		std::vector<Channel *>		getChannels(void) const;

		// SETTERS
		void						setName(std::string);
		void						setRealName(std::string);
		void						setNickname(std::string);
		void						setPermission(std::map<int, int>);
		void						setLogged(int);
		void						setConnected(int);
		void						setInvitedIn(std::string);
		void						setLastChannel(std::string lastChannel);
		void						setChannels(Channel *);
};

#endif