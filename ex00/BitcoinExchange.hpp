/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:43:15 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/17 17:19:26 by yel-bouk         ###   ########.fr       */
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
#include <vector>
#include <algorithm>

struct Entry
{
	std::string date;
	float value;
};

// std::vector<Entry> entries; // holds entry data

class BitcoinExchange {
	private:

		bool isValidDate(const std::string& date) const;
		bool isValidHeader(const std::string& header) const;
 		bool isValidValue(const std::string& valueStr) const;
		// bool isValidYear(const std::string& year) const;
		// bool isVaidMonth(const std::string& month) const;
		// bool isValidDay(const std::string& day) const;
		float getExchangeRate(const std::string& date) const;
	public:
		BitcoinExchange();
		~BitcoinExchange();
		// void dataSpliter(const std::string &data, std::vector<Entry> entries);
		void loadData(const std::string& filename, std::vector<Entry>& entries);
		void processInput(const std::string& filename) const;
	
};

#endif