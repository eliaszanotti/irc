/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numerics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:44:24 by lpupier           #+#    #+#             */
/*   Updated: 2023/10/11 16:00:00 by elias            ###   ########.fr       */
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
# define SHORT_MESSAGE(client, message, num) \
SEND client, SERVER(num) + ((std::string(num)).empty() ? "" : " ") + client->getNickname() \
SPACE ":" + message RN

# define BASIC_MESSAGE(client, arg, message, num) \
SEND client, SERVER(num) + ((std::string(num)).empty() ? "" : " ") + client->getNickname() \
SPACE arg SPACE ":" + message RN

# define CHANNEL_MESSAGE(client, channel, message, num) \
SEND client, SERVER(num) + ((std::string(num)).empty() ? "" : " ") + client->getNickname() \
SPACE channel->getName() SPACE ":" + message RN

// NUMERICS COMMANDS
# define RPL_CMD(client, cmd, msg) \
SEND client, ":" + client->getNickname() + "!" + client->getName() + "@" + IP_ADDR SPACE cmd SPACE msg RN

// PRIVMSG
# define RPL_CMD_CHAN_OTHER(client, other, cmd, channel, msg) \
SEND client, ":" + other->getNickname() + "!" + other->getName() + "@" + IP_ADDR SPACE cmd SPACE channel->getName() SPACE msg RN

# define RPL_CMD_TARGET(client, target, cmd, msg) \
SEND target, ":" + client->getNickname() + "!" + client->getName() + "@" + IP_ADDR SPACE cmd SPACE ":" SPACE msg RN

// KICK
# define KICK_WITHOUT_REASON(client, channel, banned_user) \
SEND client, ":" + client->getNickname() + "!" + client->getName() + "@" + IP_ADDR SPACE "KICK" \
SPACE channel->getName() SPACE banned_user->getNickname() RN

# define KICK_WITH_REASON(client, channel, banned_user, reason) \
SEND client, ":" + client->getNickname() + "!" + client->getName() + "@" + IP_ADDR SPACE "KICK" \
SPACE channel->getName() SPACE banned_user->getNickname() SPACE reason RN

// 001
# define RPL_WELCOME(client) SHORT_MESSAGE(client, "Welcome to the IRC Network " + client->getNickname() + " !", "001")

// 221
# define RPL_UMODEIS

// 315
# define RPL_ENDOFWHO(client, target) BASIC_MESSAGE(client, target, "End of /WHO list", "315")

// 324
# define RPL_CHANNELMODEIS(client, channel) \
SEND client, SERVER("324") SPACE client->getNickname() SPACE channel->getName() SPACE channel->getModes() RN

// 331
# define RPL_NOTOPIC(client, channel) CHANNEL_MESSAGE(client, channel, "No topic is set", "331")

// 332
# define RPL_TOPIC(client, channel) CHANNEL_MESSAGE(client, channel, channel->getTopic(), "332")

// 333
# define RPL_TOPICWHOTIME(client, channel) \
SEND client, SERVER("333") SPACE client->getNickname() SPACE channel->getName() SPACE channel->getTopicInfos() RN

// 341
# define RPL_INVITING(client, channel, nickname) \
SEND client, ":" + client->getNickname() + "!" + client->getName() + "@" + IP_ADDR SPACE "INVITE" SPACE nickname SPACE channel->getName() RN

// 336
# define RPL_INVITELIST(client, channelName) \
SEND client, SERVER("336") SPACE client->getNickname() SPACE channelName RN

// 337
# define RPL_ENDOFINVITELIST(client) SHORT_MESSAGE(client, "End of /INVITE list", "337")

// INVITE
# define INVITE_MESSAGE(client, channelName, senderName) \
SEND client, "You have been invited to " + channelName + " by " + senderName RN

// 352
#define RPL_WHOREPLY(client, user, channel) \
SEND client, SERVER("352") SPACE client->getNickname() SPACE channel \
SPACE user->getName() SPACE SERVER_NAME SPACE IP_ADDR SPACE user->getNickname() \
SPACE "H" SPACE ":1" SPACE user->getRealName() RN

// 353
# define RPL_NAMREPLY(client, channel, user) \
SEND client, SERVER("353") SPACE client->getNickname() SPACE channel->getSymbol() SPACE channel->getName() \
SPACE ":" + channel->getPrivilegeFor(user) + user->getNickname() RN

// 366
# define RPL_ENDOFNAMES(client, channel) CHANNEL_MESSAGE(client, channel, "End of /NAMES list", "366")

// 401
# define ERR_NOSUCHNICK(client, nickName) BASIC_MESSAGE(client, nickName, "No such nick/channel", "401")

// 403
# define ERR_NOSUCHCHANNEL(client, channelName) BASIC_MESSAGE(client, channelName, "No such channel", "403")

// 411
# define ERR_NORECIPIENT(client) SHORT_MESSAGE(client, "No recipient given", "411")

// 412
# define ERR_NOTEXTTOSEND(client) SHORT_MESSAGE(client, "No text to send", "412")

// 421
# define ERR_UNKNOWNCOMMAND(client, cmd) BASIC_MESSAGE(client, cmd, "Unknown command", "421")

// 431
# define ERR_NONICKNAMEGIVEN(client) SHORT_MESSAGE(client, "No nickname given", "431")

// 432
# define ERR_ERRONEUSNICKNAME(client, nickname) BASIC_MESSAGE(client, nickname, "Erroneus nickname", "432")

// 433
# define ERR_NICKNAMEINUSE(client, nickname) BASIC_MESSAGE(client, nickname, "Nickname is already in use", "433")

// 441
# define ERR_USERNOTINCHANNEL(client, nickname) BASIC_MESSAGE(client, nickname, "They aren't on that channel", "441")

// 442
# define ERR_NOTONCHANNEL(client, channel) CHANNEL_MESSAGE(client, channel, "You're not on that channel", "442")

// 443
# define ERR_USERONCHANNEL(client, channel, nick) \
SEND client, SERVER("443") SPACE client->getNickname() SPACE nick SPACE channel->getName() SPACE ":is already on channel" RN

// 461
# define ERR_NEEDMOREPARAMS(client, cmd) BASIC_MESSAGE(client, cmd, "Not enough parameters", "461")

// 462
# define ERR_ALREADYREGISTERED(client) SHORT_MESSAGE(client, "You may not register", "462")

// 464
# define ERR_PASSWDMISMATCH(client) SEND client, SERVER("464") SPACE client->getNickname() SPACE "Password incorrect" RN

// 471
# define ERR_CHANNELISFULL(client, channel) CHANNEL_MESSAGE(client, channel, "Cannot join channel (+l)", "471")

//473
# define ERR_INVITEONLYCHAN(client, channel) CHANNEL_MESSAGE(client, channel, "Cannot join channel (+i)", "473")

// 475
# define ERR_BADCHANNELKEY(client, channel) CHANNEL_MESSAGE(client, channel, "Cannot join channel (+k)", "475")

// 476
# define ERR_BADCHANMASK(client) SHORT_MESSAGE(client, "Bad Channel Mask", "476")

// 482
# define ERR_CHANOPRIVSNEEDED(client, channel) CHANNEL_MESSAGE(client, channel, "You're not channel operator", "482")

#endif