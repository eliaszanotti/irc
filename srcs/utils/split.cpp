/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:08:45 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/10 14:13:07 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

# include <sstream> //TODO move in irc.hpp

std::vector<std::string> split(std::string str, char delimiter)
{
	// TODO add secu quand on a "NICK         " -> [NICK][][][] 

	str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    std::vector<std::string> splitString;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        splitString.push_back(token);
    }
	return (splitString);
}

// std::vector<std::string> split(std::string str, std::string delimiter)
// // {
// // 	std::vector<std::string>    split_str;
// // 	std::string					token;
// // 	size_t						pos_start = 0, pos_end;
	
// // 	while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
// // 		token = str.substr (pos_start, pos_end - pos_start);
// // 		pos_start = pos_end + delimiter.size();
// // 		split_str.push_back (token);
// // 	}
// // 	split_str.push_back (str.substr (pos_start));
// // 	return split_str;
// // }