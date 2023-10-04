/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:59:12 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 09:42:35 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define MAGENTA "\e[35m"
# define CYAN "\e[36m"
# define RST "\e[0m"
# define ERROR_STRING RED "[Error] " RST

# include <iostream>
# include <sys/socket.h>
# include <map>
# include <vector>
# include <string>
# include <stdlib.h>
# include "Server.hpp"
# include "User.hpp"
# include "Channel.hpp"

enum {
	ADMIN,
	USER
}; 

enum {
	OPEN,
	INVITE
}; 

#endif