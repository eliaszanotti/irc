/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendTo.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:55:41 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 08:49:49 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void	sendTo(const User *user, const std::string &message)
{
	size_t byteSent = 0;

	while (byteSent < message.length())
	{
		long len = send(user->getFd(), message.c_str(), message.size(), 0);
		if (len < 0)
		{
			std::cout << WARN_ICON << "Send() error: Server to client" << std::endl;
			break ;
		}
		byteSent += len;
	}
}
