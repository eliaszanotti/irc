/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/05 13:32:24 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP

# define MAX_CHAR 1024
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
	JOIN,
	PRIVMSG
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
		struct pollfd			_pollFD[MAX_CHAR];
		int						_pollFDSize;
		bool					_serverIsRunning;
		
		// PRIVATE METHODS
		void	_processPoll(void);
		void	_addNewUser(void);
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
		bool	_privmsg(int, std::vector<std::string>);

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