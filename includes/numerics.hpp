/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numerics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:44:24 by lpupier           #+#    #+#             */
/*   Updated: 2023/10/09 17:31:33 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICS_HPP
# define NUMERICS_HPP

// SERVER INFORMATIONS
# define IP_ADDR "localhost"
# define SERVER_NAME "localhost"

# define SEND Server::_sendTo(
# define RN + "\r\n")
# define SPACE + " " +
# define SERVER(num) std::string(":localhost") SPACE num

// MESSAGES
#define SHORT_MESSAGE(client, message, num) \
SEND client, SERVER(num) + ((std::string(num)).empty() ? "" : " ") + client->getNickname() \
SPACE ":" + message RN

#define BASIC_MESSAGE(client, arg, message, num) \
SEND client, SERVER(num) + ((std::string(num)).empty() ? "" : " ") + client->getNickname() \
SPACE arg SPACE ":" + message RN

#define CHANNEL_MESSAGE(client, channel, message, num) \
SEND client, SERVER(num) + ((std::string(num)).empty() ? "" : " ") + client->getNickname() \
SPACE channel->getName() SPACE ":" + message RN

// NUMERICS COMMANDS
# define RPL_CMD(client, cmd, msg) \
SEND client, ":" + client->getNickname() + "!" + client->getName() + "@" + IP_ADDR SPACE cmd SPACE msg RN

// 353
# define RPL_NAMREPLY(client, channel, user) \
SEND client, SERVER("353") SPACE client->getNickname() SPACE channel->getSymbol() SPACE channel->getName() \
SPACE ":" + channel->getPrivilegeFor(user) + user->getNickname() RN

// 366
# define RPL_ENDOFNAMES(client, channel) CHANNEL_MESSAGE(client, channel, "End of /NAMES list", "366")

// 421
# define ERR_UNKNOWNCOMMAND(client, cmd) BASIC_MESSAGE(client, cmd, "Unknown command", "421")

#endif