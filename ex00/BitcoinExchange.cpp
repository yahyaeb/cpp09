/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:43:12 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/18 18:23:36 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};
BitcoinExchange::~BitcoinExchange() {
};

bool BitcoinExchange::isValidHeader(const std::string& header) const 
{
	return (header.compare("date | value") == 0);
}

bool BitcoinExchange::isValidValue(const std::string& valueStr) const
{
    size_t start = 0, len = valueStr.size();
	// std::cout << "Value str: " << valueStr << std::endl; 
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
	if(temp < 1 || temp > 31)
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
	std::cout << "dataBase file opened successfully!" << std::endl;

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
	std::cout << "dataBase file closed properly!" << std::endl;
}

void BitcoinExchange::processInput(const std::string& filename) const
{
	std::ifstream input(filename.c_str());
	if (!input)
		throw std::runtime_error("Error: could not open data file.");
	std::cout << "Input file opened successfully!" << std::endl;
	std::string line;
	std::getline(input, line);
	if(!isValidHeader(line))
		std::cout << "Header file doesn't match: date | value" << std::endl;
	while(std::getline(input, line))
	{
		if(line.empty())
			std::cout << "Error: no data available" << std::endl;
		std::size_t pos = line.find('|');
		if (pos == std::string::npos && !line.empty())
		{
			std::cout << "Error: missing '|' " << std::endl;
			std::cout << "Bad input => " << line << std::endl;
		}
		else if (pos != 11)
			std::cout << "Invalid date: '|' not in the right position" << std::endl;
		if(!isValidDate(line.substr(0, 10)))
			std::cout << "";
		if(!isValidValue(&line[12]))
			std::cout << "Invalid value" << std::endl;
			
		// std::istringstream iss(line);
		// std::string date, value_str;
		// if(isValidDate())
	}
	
	
	input.close();
	std::cout << "Input file closed properly!" << std::endl;
}

// void BitcoinExchange::loadData()
// {
// 	// std::string mytext;
// 	std::ifstream in("./bitcoin_database/data.csv");
// 	// int counter = 0;
// 	if (!in)
// 		throw std::runtime_error("Error: could not open data file.");
// 	// (void)exchange_db;
// 	std::cout << "file opened successfully!" << std::endl;
// 	// std::getline(in, mytext);
// 	// if(!isValidHeader(mytext))
// 	// 	throw std::invalid_argument("Invalid Header! Make sure the header respects the following format: date,exchange_rate");
// 	// while(std::getline(in, mytext))
// 	// {
// 	// 	// std::cout << mytext << std::endl;
// 	// 	std::size_t pos = mytext.find(',');
// 	// 	if(pos == std::string::npos || pos != 10
// 	// 		|| std::count(mytext.begin(), mytext.end(), ',') != 1
// 	// 		|| mytext[4] != '-' || mytext[7] != '-'
// 	// 		||std::count(mytext.begin(), mytext.end(), '-') != 2
// 	// 		|| mytext.empty())
// 	// 		throw std::invalid_argument("Invalid Data!");
// 	// 	if (!isValidDate(mytext.substr(0, 10)) || mytext.substr(0, 10).empty())
// 	// 		throw std::invalid_argument("Invalid Date!");
// 	// 	e.date = mytext.substr(0, 10);
// 	// 	if (!isValidValue(&mytext[11]))
// 	// 		throw std::invalid_argument("Invalid Value!");
// 	// 	e.value = std::atof(&mytext[11]);
// 	// 	entries.push_back(e);
// 	// }
// 	in.close();
// 	std::cout << "file closed properly!" << std::endl;
// }
