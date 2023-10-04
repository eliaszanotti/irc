/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 14:23:26 by elias            ###   ########.fr       */
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
		// PRIVATE METHODS
		void	_processPoll(struct pollfd *pollFD, int pollFDSize);

	public:
		// CONSTRUCTORS
		Server();
		~Server();
		Server(int port, std::string password);

		// METHODS
		void	init(void);
		void	waitingForNewUsers(void);
};

#endif