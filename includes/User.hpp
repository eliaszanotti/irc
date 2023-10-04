/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 18:20:31 by thibaultgir      ###   ########.fr       */
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
		std::string				_nickname;
		std::map<int, int>		_permission;
	
	public:
		// CONSTRUCTORS
		User();
		User(pollfd	pollfd);
		~User();
		
		// GETTERS
		std::string			getName(void);
		std::string			getNickname(void);
		std::map<int, int>	getPermission(void);
		int					getLogged(void);
		int					getConnected(void);
		
		// SETTERS
		void				setName(std::string);
		void				setNickname(std::string);
		void				setPermission(std::map<int, int>);
		void				setLogged(int);
		void				setConnected(int);
};

#endif