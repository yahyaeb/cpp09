/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:43:15 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/21 17:10:25 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
#include <algorithm>

#include <sstream> 

// std::map<std::string, double> exchange_db;

// std::vector<Entry> entries; // holds entry data

class BitcoinExchange {
	private:

		bool isValidDate(const std::string& date) const;
		bool isValidHeader(const std::string& header) const;
 		bool isValidValue(const std::string& valueStr) const;
		float getExchangeRate(const std::string& date) const;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();
		void loadData(std::map<std::string, double> &exchange_db);
		void processInput(std::map<std::string, double> &exchange_db ,const std::string& filename) const;
};

#endif