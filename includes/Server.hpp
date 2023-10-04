/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 17:24:16 by thibaultgir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP

# include "irc.hpp"

class Channel;

class Server
{
	private:
		int						_port;
		std::string				_password;
		int						_serverSocket;
		struct sockaddr_in	 	_serverAddress;
		std::vector<Channel>	_channels;
		std::map<int, User>		_users;
		// PRIVATE METHODS
		void	_processPoll(struct pollfd *pollFD, int pollFDSize);
		void	sendNewUserMsg(int);
		void	createNewUser(pollfd);
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