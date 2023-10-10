/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numerics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:44:24 by lpupier           #+#    #+#             */
/*   Updated: 2023/10/10 08:44:37 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICS_HPP
# define NUMERICS_HPP

// SERVER INFORMATIONS
# define IP_ADDR "localhost"
# define SERVER_NAME "localhost"

# define SEND sendTo(
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

// 331
# define RPL_NOTOPIC(client, channel) CHANNEL_MESSAGE(client, channel, "No topic is set", "331")

// 332
# define RPL_TOPIC(client, channel) CHANNEL_MESSAGE(client, channel, channel->getTopic(), "332")

// 333
# define RPL_TOPICWHOTIME(client, channel) \
SEND client, SERVER("333") SPACE client->getNickname() SPACE channel->getName() SPACE channel->getTopicInfos() RN

// 353
# define RPL_NAMREPLY(client, channel, user) \
SEND client, SERVER("353") SPACE client->getNickname() SPACE channel->getSymbol() SPACE channel->getName() \
SPACE ":" + channel->getPrivilegeFor(user) + user->getNickname() RN

// 366
# define RPL_ENDOFNAMES(client, channel) CHANNEL_MESSAGE(client, channel, "End of /NAMES list", "366")

// 403
# define ERR_NOSUCHCHANNEL(client, channelName) BASIC_MESSAGE(client, channelName, "No such channel", "403")

// 421
# define ERR_UNKNOWNCOMMAND(client, cmd) BASIC_MESSAGE(client, cmd, "Unknown command", "421")

// 442
# define ERR_NOTONCHANNEL(client, channel) CHANNEL_MESSAGE(client, channel, "You're not on that channel", "442")

// 461
# define ERR_NEEDMOREPARAMS(client, cmd) BASIC_MESSAGE(client, cmd, "Not enough parameters", "461")

// 475
# define ERR_BADCHANNELKEY(client, channel) CHANNEL_MESSAGE(client, channel, "Cannot join channel (+k)", "475")

// 482
# define ERR_CHANOPRIVSNEEDED(client, channel) CHANNEL_MESSAGE(client, channel, "You're not channel operator", "482")

#endif