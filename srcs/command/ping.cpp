/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:25:16 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/12 10:46:11 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool    Server::_ping(int fd, std::vector<std::string> command)
{
    if (command.size() < 2)
    {
        ERR_NEEDMOREPARAMS(this->_users[fd], "PING");
        return (false);
    }
    RPL_PONG(this->_users[fd], command[1]);
    return (true);
}