/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:04:36 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 12:32:01 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# define RED			"\e[31m"
# define GREEN			"\e[32m"
# define YELLOW			"\e[33m"
# define BLUE			"\e[34m"
# define MAGENTA		"\e[35m"
# define CYAN			"\e[36m"
# define RST			"\e[0m"
# define ERROR_STRING	RED "[Error] " RST

# include <arpa/inet.h>
# include <cstring>
# include <errno.h>
# include <iostream>
# include <map>
# include <netinet/in.h>
# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <sys/ioctl.h>
# include <sys/poll.h>
# include <sys/socket.h>
# include <vector>
# include <unistd.h>
# include "Server.hpp"
# include "User.hpp"
# include "Channel.hpp"

# define MAX_USERS		42
# define POLL_TIMEOUT	-1

enum {
	ADMIN,
	RW
}; 

enum {
	OPEN,
	INVITE_MODE
};

std::vector<std::string>	split(std::string s, char delimiter);

#endif