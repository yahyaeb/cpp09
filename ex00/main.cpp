/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:26:27 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/17 16:46:07 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if(argc != 2)
		std::cout << "invalid" << std::endl;
	else
	try{
		BitcoinExchange file;
		std::vector<Entry> entries;
		file.loadData(argv[1], entries);	
		for (std::size_t i = 0; i < entries.size(); ++i) {
    		std::cout << entries[i].date << " => " << entries[i].value << "\n";
		}

	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}