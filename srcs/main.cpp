/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:33:18 by elias             #+#    #+#             */
/*   Updated: 2023/10/03 12:40:21 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ERROR_STRING "\e[31m[Error]\e[0m " // a deplacer dans un .hpp

#include <iostream>

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 3)
        return (std::cout << ERROR_STRING "Wrong number of arguments (usage: ./ircserv <port> <password>)" << std::endl, 1);
    return (0);
}