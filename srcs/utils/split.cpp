/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:08:45 by tgiraudo          #+#    #+#             */
/*   Updated: 2024/02/14 14:23:39 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

std::vector<std::string> split(std::string str, char delimiter)
{
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