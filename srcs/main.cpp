/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:33:18 by elias             #+#    #+#             */
/*   Updated: 2023/10/03 17:23:32 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw std::invalid_argument("Wrong number of arguments "
				"(usage: ./ircserv <port> <password>)");
		int	port = std::strtod(argv[1], NULL);
		if (port < 1024 || port > 65535)
			throw std::invalid_argument("Port must be between 1024 and 65535");
		std::string	password = std::string(argv[2]);
		std::cout << port << std::endl;
		std::cout << password << std::endl;
	}
	catch(const std::exception& error)
	{
		return (std::cerr << ERROR_STRING << error.what() << std::endl, 1);
	}
    return (0);
}