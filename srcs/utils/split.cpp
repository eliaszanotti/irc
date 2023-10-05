/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:08:45 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/05 13:55:16 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

std::vector<std::string> split(std::string s, std::string delimiter)
{
    std::vector<std::string>    split_str;
    std::string                 token;
    size_t                      pos_start = 0, pos_end;
    
    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delimiter.size();
        split_str.push_back (token);
    }

    split_str.push_back (s.substr (pos_start));
    return split_str;
}

std::string erasechar(std::string s, char erased) 
{
    size_t  pos;
    std::cout << "before: " << s << std::endl;
    while ((pos= s.find(erased, 0)) != std::string::npos) {
        s.erase(pos, 1);
    }
    std::cout << "after: " << s << std::endl;
    return (s);
}