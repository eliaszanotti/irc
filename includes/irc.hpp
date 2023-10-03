/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:59:12 by elias             #+#    #+#             */
/*   Updated: 2023/10/03 17:13:45 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# define ERROR_STRING "\e[31m[Error]\e[0m "

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

#endif