/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/06 14:01:26 by elias            ###   ########.fr       */
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
		void	_processMessage(std::string buffer, int currentIndex);
		void	_closeCurrentUser(int currentIndex);
		void	_connectEachUser(void);
		bool	_checkCommandInsideMessage(int fd, std::string message);
		void	_sendTo(const User *user, const std::string &message);
		// COMMANDS
		bool	_cap(int fd);
		bool	_invite(void);
		bool	_join(int fd, std::vector<std::string>);
		bool	_kick(void);
		bool	_mode(void);
		bool	_nick(int fd, std::vector<std::string> command);
		bool	_pass(int fd, std::vector<std::string>);
		bool	_privmsg(int fd, std::vector<std::string>);
		bool	_topic(void);
        bool	_user(int fd, std::vector<std::string> command);

	public:
		// CONSTRUCTORS
		~Server();
		Server(int port, std::string password);

		// GETTERS
		int			getServerSocket(void) const;

		// METHODS
		void	init(void);
		void	waitingForNewUsers(void);
};

#endif