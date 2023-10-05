/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:45:50 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 10:07:09 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool	Server::_cap(int fd)
{
	std::cout << "cap() called" << std::endl;
    send(fd, "Welcome to irc, to login use: \nPASS <password>\nNICK <nickname>\nUSER <name> 0 * : <realname>\n", 93, 0);
	return (true);
}