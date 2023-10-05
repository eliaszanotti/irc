/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/05 09:23:53 by tgiraudo         ###   ########.fr       */
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
	USER
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
		std::vector<Channel>	_channels;
		std::map<int, User *>		_users;
		
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

	public:
		// CONSTRUCTORS
		~Server();
		Server(int port, std::string password);

		// GETTERS
		int	getServerSocket(void) const;

		// METHODS
		void	init(void);
		void	waitingForNewUsers(void);
};

#endif