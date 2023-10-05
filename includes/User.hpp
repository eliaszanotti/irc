/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/05 10:55:12 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "irc.hpp"

class User 
{
	private:
		struct pollfd			_pollfd;
		int						_connected;
		int						_logged;
		std::string				_name;
		std::string				_realname;
		std::string				_nickname;
		std::map<int, int>		_permission;
	
	public:
		// CONSTRUCTORS
		User();
		User(pollfd	pollfd);
		~User();
		
		// GETTERS
		std::string			getName(void) const;
		std::string			getRealName(void) const;
		std::string			getNickname(void) const;
		std::map<int, int>	getPermission(void) const;
		int					getLogged(void) const;
		int					getConnected(void) const;
		pollfd				getPollFd(void) const;
		int					getFd(void) const;
		
		// SETTERS
		void				setName(std::string);
		void				setRealName(std::string);
		void				setNickname(std::string);
		void				setPermission(std::map<int, int>);
		void				setLogged(int);
		void				setConnected(int);
};

#endif