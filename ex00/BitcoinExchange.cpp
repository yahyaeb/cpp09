/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:43:12 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/17 18:32:41 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};
BitcoinExchange::~BitcoinExchange() {
};

bool BitcoinExchange::isValidHeader(const std::string& header) const 
{
	return (header.compare("date,exchange_rate") == 0);
}

bool BitcoinExchange::isValidValue(const std::string& valueStr) const
{
	if(valueStr.empty())
		return false;
	int dot = 0;
	for(int i = 0; valueStr[i]; i++)
	{
		if(valueStr[i] == ' ' || valueStr[i] == '\r' || valueStr[i] == '\t')
			return false;
		if (valueStr[i] == '.' )
		{
			dot++;
			if (dot > 1)
				return false;
		}
		else if (!std::isdigit(valueStr[i]))
			return false;
	}
	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	long temp;
	char *end;
	for(unsigned int i = 0; i < date.size(); i++)
	{
		if(date[i] == ' ' || date[i] == '\r' || date[i] == '\t')
			return false;
		if (date[i] == '-' )
			continue;
		else if (!std::isdigit(date[i]))
			return false;
	}
	std::string year_str = date.substr(0,4);
	temp = strtol(date.c_str(), &end, 10);
	if(end != year_str.c_str() + 4)
		return false;
	if(temp > 2025 || temp < 2009)
		return false;
		
	std::string month_str = date.substr(5,2);
	temp = strtol(date.c_str(), &end, 10);
	if(end != month_str.c_str() + 2)
		return false;
	if(temp > 12 || temp < 1)
		return false;
		
	std::string day_str = date.substr(8,2);
	temp = strtol(date.c_str(), &end, 10);
	if(end != day_str.c_str() + 2)
		return false;
	if(temp < 1 || temp > 31)
		return false;

	return true;
}

void BitcoinExchange::loadData(const std::string& filename, std::vector<Entry>& entries)
{
	std::string mytext;
	std::ifstream in(filename.c_str());
	// int counter = 0;
	Entry e;
	if (!in.is_open())
		throw std::runtime_error("Error: could not open data file.");
	std::cout << "file opened successfully!" << std::endl;
	std::getline(in, mytext);
	if(!isValidHeader(mytext))
		throw std::invalid_argument("Invalid Header! Make sure the header respects the following format: date,exchange_rate");
	while(std::getline(in, mytext))
	{
		// std::cout << mytext << std::endl;
		std::size_t pos = mytext.find(',');
		if(pos == std::string::npos || pos != 10
			|| std::count(mytext.begin(), mytext.end(), ',') != 1
			|| mytext[4] != '-' || mytext[7] != '-'
			||std::count(mytext.begin(), mytext.end(), '-') != 2
			|| mytext.empty())
			throw std::invalid_argument("Invalid Data!");
		if (!isValidDate(mytext.substr(0, 10)) || mytext.substr(0, 10).empty())
			throw std::invalid_argument("Invalid Date!");
		e.date = mytext.substr(0, 10);
		if (!isValidValue(&mytext[11]))
			throw std::invalid_argument("Invalid Value!");
		e.value = std::atof(&mytext[11]);
		entries.push_back(e);
	}
	std::cout << "file closed properly!" << std::endl;
}
