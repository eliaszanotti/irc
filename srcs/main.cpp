/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:33:18 by elias             #+#    #+#             */
/*   Updated: 2023/10/03 17:33:25 by elias            ###   ########.fr       */
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
			throw (std::invalid_argument("Password must be at least 8 characters long"));
	}
	catch(const std::exception& error)
	{
		return (std::cerr << ERROR_STRING << error.what() << std::endl, 1);
	}
	try
	{
		std::cout << "TEST" << std::endl;
		Server server(port, password);
		// server.run();
	}
	catch(const std::exception& error)
	{
		std::cerr << ERROR_STRING << error.what() << std::endl;
	}
    return (0);
}