/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:59:17 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/20 15:45:44 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <sstream>

#ifndef PMERGEME_HPP
#define PMERGEME_HPP


class PmergeMe {

	private:
		std::vector<int> _vec;
		std::deque<int> _deq;

		// Templated recursive Ford-Johnson sort for both vector and deque
		template<typename Container>
		void fordJohnsonSort(Container& container);
	public:
		PmergeMe(const std::vector<int>& input);

		void sortAll();
		void printResults() const;
};

#endif
