/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:33:18 by elias             #+#    #+#             */
/*   Updated: 2023/10/11 10:46:25 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int main(int argc, char **argv)
{
	int port;
	std::string password;
	try
	{
		if (argc != 3)
			throw std::invalid_argument("Wrong number of arguments "
				"(usage: ./ircserv <port> <password>)");
		port = std::strtod(argv[1], NULL);
		password = std::string(argv[2]);
		if (port < 1024 || port > 65535)
			throw std::invalid_argument("Port must be between 1024 and 65535");
		if (password.length() == 0)
			throw (std::invalid_argument("Password cannot be empty"));
	}
	catch(const std::exception& error)
	{
		return (std::cerr << ERROR_STRING << error.what() << std::endl, 1);
	}
	Server server(port, password);
	try
	{
		server.init();
		server.waitingForNewUsers();
	}
	catch(const std::exception& error)
	{
		close(server.getServerSocket());
		return (std::cerr << WARN_ICON << error.what() << std::endl, 1);
	}
	return (0);
}