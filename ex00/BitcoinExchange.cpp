/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:43:12 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/21 17:17:48 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	(void) other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	(void) other;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {};

bool BitcoinExchange::isValidHeader(const std::string& header) const 
{
	return (header.compare("date | value") == 0);
}

bool BitcoinExchange::isValidValue(const std::string& valueStr) const
{
	size_t start = 0, len = valueStr.size();

	// Skip leading whitespace
	while (start < len && std::isspace(valueStr[start]))
		start++;

	// Check for empty after trimming
	if (start == len)
		return false;

	// Optional: Check for leading +/-
	if (valueStr[start] == '-' || valueStr[start] == '+')
		start++;

	int dot = 0;
	bool digitFound = false;

	for (size_t i = start; i < len; ++i)
	{
		if (std::isspace(valueStr[i]))
			return false; // Internal or trailing space is not allowed
		if (valueStr[i] == '.')
		{
			if (++dot > 1)
				return false;
		}
		else if (!std::isdigit(valueStr[i]))
		{
			return false;
		}
		else
		{
			digitFound = true;
		}
	}
	// At least one digit must be found
	if (!digitFound)
		return false;
	// Reject strings that are just "."
	if (dot == 1 && !digitFound)
		return false;
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
	
	temp = strtol(year_str.c_str(), &end, 10);
	if(end != year_str.c_str() + 4)
		return false;
	
	if(temp > 2025 || temp < 2009)
	{
		std::cout << "Year must be between 2009 && 2025" << std::endl;
		return false;
	}
		
	std::string month_str = date.substr(5,2);
	temp = strtol(month_str.c_str(), &end, 10);
	if(end != month_str.c_str() + 2)
		return false;
	if(temp > 12 || temp < 1)
	{
		std::cout << "Month must be between 01 && 12" << std::endl;
		return false;
	}
		
	std::string day_str = date.substr(8,2);
	temp = strtol(day_str.c_str(), &end, 10);
	if(end != day_str.c_str() + 2)
		return false;
	if(temp > 31 || temp < 1 || (month_str == "02" && temp > 29)
		|| ((month_str == "04" || month_str == "06" || month_str == "09" || month_str == "11") && temp > 30))
	{
		std::cout << "day must be valid" << std::endl;
		return false;
	}

	return true;
}

void BitcoinExchange::loadData(std::map<std::string, double>& exchange_db)
{
	std::string mytext;
	std::ifstream in("./bitcoin_database/data.csv");
	if (!in)
		throw std::runtime_error("Error: could not open data file.");
	// std::cout << "dataBase file opened successfully!" << std::endl;

	std::getline(in, mytext);
	while(std::getline(in, mytext))
	{
		std::istringstream iss(mytext);
		std::string date, value_str;

		if(std::getline(iss, date, ',') && std::getline(iss, value_str))
		{
			std::stringstream ss(value_str);
			double value;/* = std::stod(value_str); */
			ss >> value;
			if(ss.fail())
			{
				throw std::invalid_argument("Value conversion failed");
			}
			exchange_db[date] = value;
		}
	}
	in.close();
	// std::cout << "dataBase file closed properly!" << std::endl;
}
void BitcoinExchange::processInput(std::map<std::string, double> &exchange_db, const std::string& filename) const
{
	std::ifstream input(filename.c_str());
	if (!input)
		throw std::runtime_error("Error: could not open data file.");

	std::string line;
	std::getline(input, line);
	if (!isValidHeader(line)) {
		std::cout << "Header file doesn't match: date | value" << std::endl;
		return;
	}

	while (std::getline(input, line))
	{
		if (line.empty()) {
			std::cout << "Error: no data available" << std::endl;
			continue;
		}

		std::size_t pos = line.find('|');
		if (pos == std::string::npos) {
			std::cout << "Error: missing '|' \nBad input => " << line << std::endl;
			continue;
		}
		if (pos != 11) {
			std::cout << "Invalid date: '|' not in the right position" << std::endl;
			continue;
		}

		std::string date = line.substr(0, 10);
		std::string value_str = line.substr(12);

		if (!isValidDate(date)) {
			std::cout << "Error: invalid date" << std::endl;
			continue;
		}

		if (!isValidValue(value_str)) {
			std::cout << "Error: invalid value" << std::endl;
			continue;
		}

		double value = atof(value_str.c_str());
		if (value < 0) {
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000) {
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}

		std::map<std::string, double>::const_iterator it = exchange_db.find(date);
		if (it != exchange_db.end()) {
			// Direct date match
			std::cout << date << " => " << value << " = " << (it->second * value) << std::endl;
		} else {
			// Find closest lower date
			it = exchange_db.lower_bound(date);
			if (it != exchange_db.begin())
				--it;
			if (it == exchange_db.end() || it->first > date) {
				std::cout << "Error: date out of range" << std::endl;
			} else {
				std::cout << date << " => " << value << " = " << (it->second * value) << std::endl;
			}
		}
	}
	input.close();
}

