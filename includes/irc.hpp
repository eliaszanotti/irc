/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:59:12 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 11:32:12 by tgiraudo         ###   ########.fr       */
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
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/poll.h>
# include <map>
# include <vector>
# include <string>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include "Server.hpp"
# include "User.hpp"
# include "Channel.hpp"

# define MAX_USERS	42
# define MAX_CHAR	1024

enum {
	ADMIN,
	USER
}; 

enum {
	OPEN,
	INVITE
}; 

#endif