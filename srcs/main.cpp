/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:33:18 by elias             #+#    #+#             */
/*   Updated: 2023/10/03 17:08:31 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 3)
        return (std::cout << ERROR_STRING "Wrong number of arguments (usage: ./ircserv <port> <password>)" << std::endl, 1);
    return (0);
}