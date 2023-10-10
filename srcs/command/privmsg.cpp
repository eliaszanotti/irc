/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:18:52 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 09:14:49 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool    Server::_privmsg(int fd, std::vector<std::string> command)
{
	if (command.size() < 3)
	{
		ERR_NEEDMOREPARAMS(this->_users[fd], "PRIVMSG");
		return (false);
	}
	return (true);
}