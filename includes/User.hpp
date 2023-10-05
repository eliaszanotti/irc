/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/05 10:50:59 by tgiraudo         ###   ########.fr       */
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
		
		// METHODS
		void				newConnection(void);
		
		// GETTERS
		std::string			getName(void);
		std::string			getRealName(void);
		std::string			getNickname(void);
		std::map<int, int>	getPermission(void);
		int					getLogged(void);
		int					getConnected(void);
		
		// SETTERS
		void				setName(std::string);
		void				setRealName(std::string);
		void				setNickname(std::string);
		void				setPermission(std::map<int, int>);
		void				setLogged(int);
		void				setConnected(int);
};

#endif