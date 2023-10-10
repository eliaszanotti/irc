/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:08:45 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 14:18:53 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

# include <sstream> //TODO move in irc.hpp

std::vector<std::string> split(std::string str, char delimiter)
{
	str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    std::vector<std::string> splitString;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) 
    {
        if (!token.empty())
            splitString.push_back(token);
    }
	return (splitString);
}