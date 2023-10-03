/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/03 17:23:07 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "irc.hpp"

class User 
{
	private:
		std::string				_name;
		std::string				_nickname;
		std::map<int, int>		_permission;
	public:
		//  CONSTRUCTORS
		User();
		User(std::string nickname);
		~User();
		//	SETTERS & GETTERS
		std::string			getName(void);
		std::string			getNickname(void);
		std::map<int, int>	getPermission(void);
		void				setName(std::string);
		void				setNickname(std::string);
		void				setPermission(std::map<int, int>);
};

#endif