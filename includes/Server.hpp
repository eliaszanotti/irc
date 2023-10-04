/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 10:09:47 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_H
# define SERVER_CLASS_H

# include "irc.hpp"

class Channel;

class Server
{
	private:
		int						_port;
		std::string				_password;
		int						_serverSocket;
		struct sockaddr_in 		_serverAddress;
		std::vector<Channel>	_channels;

	public:
		// CONSTRUCTORS
		Server();
		~Server();
		Server(int port, std::string password);

		// METHODS
		void	init(void);
};

#endif