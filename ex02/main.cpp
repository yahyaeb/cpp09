/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:18:21 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/20 16:11:53 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main (int argc, char *argv[])
{
	if(argc > 1)
	{
		
		std::vector<int> input;
		for(int i = 1; i < argc; ++i)
		{
			std::istringstream iss(argv[i]);
			int n;
			if(!(iss >> n))
				continue;
			input.push_back(n);	
		}
		PmergeMe m(input);
		std::cout << "before : ";
		m.printResults();
		std::cout << "after : ";
		m.sortAll();
		
		m.printResults();
		
		return 0;
	}
	else
	{
		std::cout << "Missing equation argument." << std::endl;
		return 1;
	}
}