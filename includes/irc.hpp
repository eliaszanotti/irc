/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:04:36 by tgiraudo          #+#    #+#             */
/*   Updated: 2024/02/14 15:04:47 by lpupier          ###   ########.fr       */
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
# define WARN_ASCII		"[⚠] "
# define PLUS_ICON		GREEN "[+] " RST
# define DEL_ICON		RED "[-] " RST
# define L_ARROW_ICON	YELLOW "[←]" RST
# define WARN_ICON		RED WARN_ASCII RST
# define ERROR_STRING	RED "[Error] " RST

# include <arpa/inet.h>
# include <algorithm>
# include <csignal>
# include <cstring>
# include <iostream>
# include <fstream>
# include <map>
# include <netinet/in.h>
# include <sstream>
# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <sys/ioctl.h>
# include <sys/poll.h>
# include <sys/socket.h>
# include <sstream>
# include <vector>
# include <ctime>
# include <unistd.h>
# include "Server.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "numerics.hpp"

# define MAX_USERS		42
# define POLL_TIMEOUT	-1

enum {
	ADMIN,
	RW
}; 

enum {
	OPEN,
	INVITE
};

std::vector<std::string>	split(std::string str, char delimiter);
std::string					toString(int number);
void						sendTo(const User *user, const std::string &message);

#endif