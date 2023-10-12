/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toString.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:00:12 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/10/11 18:01:54 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

std::string toString(int number)
{
    std::string str;
    std::stringstream ss;
    ss << number;
    ss >> str;
    return (str);
}