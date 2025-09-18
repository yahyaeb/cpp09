/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:26:27 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/18 17:02:29 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	std::map<std::string, double> exchange_db;
	if(argc != 2)
		std::cout << "Missing file argument" << std::endl;
	else
	{
		
		try
		{
			BitcoinExchange file;
			// 	// std::map<Entry> entries;
			file.loadData(exchange_db);	
			// for (std::map<std::string, double>::const_iterator it = exchange_db.begin(); it != exchange_db.end(); ++it) {
				// 	std::cout << it->first << " => " << it->second << "\n";
				// }
			file.processInput(exchange_db, argv[1]);
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	return 0;
}