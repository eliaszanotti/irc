/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:36:56 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/12 09:36:15 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool    Server::_list(int fd, std::vector<std::string> command)
{
    RPL_LISTSTART(this->_users[fd]);
    for (size_t i = 0; i < this->_channels.size(); i++)
        RPL_LIST(this->_users[fd], this->_channels[i]);
    RPL_LISTEND(this->_users[fd]);
    (void)command;
    return (true);
}