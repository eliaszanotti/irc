/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/03 16:43:49 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_H
# define SERVER_CLASS_H

# include <iostream>

class Server
{
	private:
		int			_port;
		std::string	_password;

	public:
		// Constructors
		Server();
		~Server();
		Server(int port, std::string password);

		// Methods
		
};

#endif