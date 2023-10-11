/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/11 15:00:24 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "irc.hpp"

class Channel;

class User 
{
	private:
		struct pollfd			_pollFD;
		int						_connected;
		int						_logged;
		std::string				_name;
		std::string				_realname;
		std::string				_nickname;
		std::map<int, int>		_permission;
		std::string				_lastChannel;
	
	public:
		// CONSTRUCTORS
		User();
		User(pollfd	pollFD);
		~User();
		// METHODS
		void				newConnection(void);
		void				sendToAll(std::vector<User *>, std::string, Channel *, std::string);
		// GETTERS
		std::string			getName(void) const;
		std::string			getRealName(void) const;
		std::string			getNickname(void) const;
		std::map<int, int>	getPermission(void) const;
		int					getLogged(void) const;
		int					getConnected(void) const;
		pollfd				getPollFd(void) const;
		int					getFd(void) const;
		std::string			getLastChannel(void) const;
		// SETTERS
		void				setName(std::string name);
		void				setRealName(std::string realname);
		void				setNickname(std::string nickname);
		void				setPermission(std::map<int, int> permission);
		void				setLogged(int logged);
		void				setConnected(int connected);
		void				setLastChannel(std::string lastChannel);
};

#endif