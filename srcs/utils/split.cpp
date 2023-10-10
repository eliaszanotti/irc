/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:08:45 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 13:41:27 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

# include <sstream> //TODO move in irc.hpp

std::vector<std::string> split(std::string str, char delimiter)
{
	// TODO add secu quand on a "NICK         " -> [NICK][][][] 

    std::vector<std::string> splitString;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        splitString.push_back(token);
    }
	return (splitString);
}