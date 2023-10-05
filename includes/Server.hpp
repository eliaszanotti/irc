/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/05 11:39:20 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP

# include "irc.hpp"

enum {
	KICK,
	INVITE,
	TOPIC,
	MODE,
	CAP,
	PASS,
	NICK,
	USER,
	JOIN
};

class Channel;

class User;

class Server
{
	private:
		int						_port;
		std::string				_password;
		int						_serverSocket;
		struct sockaddr_in	 	_serverAddress;
		std::vector<Channel *>	_channels;
		std::map<int, User *>	_users;
		
		// PRIVATE METHODS
		void	_processPoll(struct pollfd *pollFD, int pollFDSize);
		bool	_checkCommandInsideMessage(int fd, std::string message);
		void	sendNewUserMsg(int);
		void	createNewUser(pollfd);

		bool	_kick();
		bool	_invite();
		bool	_topic();
		bool	_mode();
		bool	_pass(int, std::vector<std::string>);
		bool	_cap(int);
		bool	_nick(int fd, std::vector<std::string> command);
		bool	_user(int fd, std::vector<std::string> command);
		bool	_join(int, std::vector<std::string>);

	public:
		// CONSTRUCTORS
		~Server();
		Server(int port, std::string password);

		// GETTERS
		std::string	getName(void) const;
		int			getServerSocket(void) const;

		// METHODS
		void	init(void);
		void	waitingForNewUsers(void);

		static void	sendTo(const User *user, const std::string &message);
};

#endif