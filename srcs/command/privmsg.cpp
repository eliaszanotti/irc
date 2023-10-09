/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:18:52 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/09 17:11:33 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool    Server::_privmsg(int fd, std::vector<std::string> command)
{
	for (size_t i = 0; i < command.size(); i++)
	{
		std::cout << command[i] << std::endl;
	}
		
	if (command.size() < 3)
		return (send(fd, "Wrong command usage: PRIVMSG <user|#channel> :<msg>\n"));
	(void)fd;
	return (true);
}