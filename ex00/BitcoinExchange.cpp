/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:43:12 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/16 09:56:20 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};
BitcoinExchange::~BitcoinExchange() {};
void BitcoinExchange::loadData(const std::string& filename)
{
	std::ifstream in("filename", std::ifstream::in);
	if (!in.is_open())
		throw std::runtime_error("Error: could not open data file.");
	
}