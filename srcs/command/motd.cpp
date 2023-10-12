/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:43:16 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/12 10:05:06 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool    Server::_motd(int fd, std::vector<std::string> command)
{
	std::string		path = "srcs/motd.config";
	std::ifstream	infile;
	std::string		line;

	infile.open(path.c_str(), std::ios::in);
	RPL_MOTDSTART(this->_users[fd]);
	while (getline(infile, line))
		RPL_MOTD(this->_users[fd], line);
	RPL_ENDOFMOTD(this->_users[fd]);
	(void)command;
	return (true);
}