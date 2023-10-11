/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/11 11:08:59 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP

# define MAX_CHAR 1024
# include "irc.hpp"

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
		std::vector<pollfd>		_pollFD;
		int						_pollFDSize;
		bool					_serverIsRunning;
		
		// PRIVATE METHODS
		void	_processPoll(void);
		void	_addNewUser(void);
		void	_processMessage(std::string buffer, int currentIndex);
		void	_closeCurrentUser(int currentIndex);
		void	_connectEachUser(void);
		bool	_isExecutableCommand(std::string message);
		void	_executeUserCommand(int fd, std::string message);
		
		// COMMANDS
		bool	_cap(int fd);
		bool	_invite(void);
		bool	_join(int fd, std::vector<std::string> command);
		bool	_kick(int fd, std::vector<std::string> command);
		bool	_mode(int fd, std::vector<std::string> command);
		bool	_nick(int fd, std::vector<std::string> command);
		bool	_pass(int fd, std::vector<std::string> command);
		bool	_privmsg(int fd, std::vector<std::string> command);
		bool	_topic(int fd, std::vector<std::string> command);
        bool	_user(int fd, std::vector<std::string> command);
        bool	_who(int fd, std::vector<std::string> command);
		bool	_part(int fd, std::vector<std::string> command);
		bool	_quit(int fd, std::vector<std::string> command);

		// JOIN
		void	_connectToChannel(int fd, Channel *channel);

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