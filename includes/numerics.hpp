/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numerics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:44:24 by lpupier           #+#    #+#             */
/*   Updated: 2023/10/05 12:37:56 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_NUMERICS_H
#define IRC_NUMERICS_H

#define IP_ADDR "127.0.0.1"
#define SERVER_NAME "localhost"

#define SEND Server::sendTo(
#define RN + "\r\n")
#define SPACE + " " +
#define SERVER(num) std::string(":localhost") SPACE num

#define SHORT_MESSAGE(client, message, num) \
SEND client, SERVER(num) + ((std::string(num)).empty() ? "" : " ") + client->getNickname() SPACE ":" + message RN

#define BASIC_MESSAGE(client, arg, message, num) \
SEND client, SERVER(num) + ((std::string(num)).empty() ? "" : " ") + client->getNickname() SPACE arg SPACE ":" + message RN

#define CHANNEL_MESSAGE(client, channel, message, num) \
SEND client, SERVER(num) + ((std::string(num)).empty() ? "" : " ") + client->getNickname() SPACE channel->getName() SPACE ":" + message RN

// 0
# define RPL_CMD(client, cmd, msg) \
SEND client, ":" + client->getNickname() + "!" + client->getName() + "@" + IP_ADDR SPACE cmd SPACE msg RN

// 353
# define RPL_NAMEREPLY(client, channel, user) \
SEND client, SERVER("353") SPACE client->getNickname() SPACE channel->getMode() SPACE channel->getName() SPACE ":" + channel->getPrefixMode(user) + \
user->getNickname() RN

// 366
# define RPL_ENDOFNAME(client, channel) CHANNEL_MESSAGE(client, channel, "End of /NAMES list", "366")

#endif