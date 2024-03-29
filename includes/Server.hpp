/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2024/02/14 12:56:33 by lpupier          ###   ########.fr       */
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
		std::string				_message;
		
		// PRIVATE METHODS
		void	_processPoll(void);
		void	_addNewUser(void);
		void	_processMessage(std::string buffer, int currentIndex);
		void	_closeCurrentUser(int currentIndex);
		void	_connectEachUser(void);
		bool	_isExecutableCommand(std::string message);
		void	_executeUserCommand(int fd, std::string message);
		void	_sendModeToAllUsers(int fd, Channel *channel, std::string modestring);

		// COMMANDS
		bool	_cap(int fd);
		bool	_invite(int fd, std::vector<std::string> command);
		bool	_join(int fd, std::vector<std::string> command);
		bool	_kick(int fd, std::vector<std::string> command);
		bool	_list(int fd, std::vector<std::string> command);
		bool	_mode(int fd, std::vector<std::string> command);
		bool	_motd(int fd, std::vector<std::string> command);
		bool	_nick(int fd, std::vector<std::string> command);
		bool	_pass(int fd, std::vector<std::string> command);
		bool	_ping(int fd, std::vector<std::string> command);
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

		// SIGNALS
		static void	ctrlc(int sig);

		// METHODS
		void	init(void);
		void	waitingForNewUsers(void);
		void	deleteAllUsers(void);
};

#endif