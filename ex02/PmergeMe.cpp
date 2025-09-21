/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:59:13 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/20 16:23:10 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
PmergeMe::PmergeMe(const std::vector<int>& input) : _vec(input),
												_deq(input.begin(), input.end())
{}

void PmergeMe::sortAll()
{
	std::sort(_vec.begin(), _vec.end());
	std::sort(_deq.begin(), _deq.end());
}

void PmergeMe::printResults() const
{
	std::cout << "Vector: ";
	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;

	std::cout << "Deque: ";
	for (std::deque<int>::const_iterator it = _deq.begin(); it != _deq.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	
}
