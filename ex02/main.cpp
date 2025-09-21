/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:18:21 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/21 17:08:05 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
	if(argc > 1)
	{
		try
		{
			valid_input(argv);
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
			std::cout << "before: ";
			m.printResults();

			m.sortAll();
			std::cout << "after: ";
			m.printResults();
		
			std::cout << "Time to process a range of " << argc-1 << " elements with std::deq : "
					<< m.deq_timeelapsed << " us" << std::endl;
			std::cout << "Time to process a range of " << argc-1 << " elements with std::vec : "
					<< m.vec_timeelapsed << " us" << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
		return 0;
	}
	std::cout << "Missing input argument." << std::endl;
	return 1;
}