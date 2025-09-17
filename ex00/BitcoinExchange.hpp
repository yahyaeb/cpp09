/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:43:15 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/16 09:54:56 by yel-bouk         ###   ########.fr       */
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

class BitcoinExchange {
	private:
		std::map<std::string, float> data;

		bool isValidDate(const std::string& date) const;
		bool isValidValue(const std::string& valueStr, float& value) const;
		float getExchangeRate(const std::string& date) const;
	public:
		BitcoinExchange();
		~BitcoinExchange();
		void loadData(const std::string& filename);
		void processInput(const std::string& filename) const;
	
};

#endif