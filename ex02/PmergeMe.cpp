/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:59:13 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/21 17:16:26 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{};

PmergeMe::PmergeMe(const PmergeMe& other)
{
	(void) other;
};

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	(void) other;
	return *this;
};

PmergeMe::~PmergeMe()
{};
		
PmergeMe::PmergeMe(const std::vector<int>& input) : _vec(input),
												_deq(input.begin(), input.end())
{}

void PmergeMe::sortAll()
{
	std::clock_t start_vec = std::clock();
	fordJohnsonSort(_vec);
	std::clock_t end_vec = std::clock();
	double elapsed_secs_vec = double(end_vec - start_vec) / CLOCKS_PER_SEC;
	double elapsed_us_vec = elapsed_secs_vec * 1e6;

	vec_timeelapsed = elapsed_us_vec;
	
	std::clock_t start_deq = std::clock();
	fordJohnsonSort(_deq);
	std::clock_t end_deq = std::clock();
	double elapsed_secs_deq = double(end_deq - start_deq) / CLOCKS_PER_SEC;
	double elapsed_us_deq = elapsed_secs_deq * 1e6;
	
	deq_timeelapsed = elapsed_us_deq;
}

void PmergeMe::printResults() const
{
	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
}

template <typename Container>
void PmergeMe::fordJohnsonSort(Container& container)
{
	typedef typename Container::value_type T;

	// check if there 1 or less elements. If thatś the case there is nothing to sort;
	if (container.size() <= 1)
		return;

	// We create a vector of pairs using the class template to store pairs 
	std::vector< std::pair<T, T> > pairs;
	pairs.reserve(container.size() / 2 + 1); // pairs is a vector of pairs (T, T)

	// we push pairs to our contaier(vector)
	typename Container::size_type i;
	for (i = 0; i + 1 < container.size(); i += 2) {
		T a = container[i];
		T b = container[i + 1];
		if (a > b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}
	// If odd count, we duplicate the last to keep pairs aligned
	if (i < container.size()) {
		T x = container.back();
		pairs.push_back(std::make_pair(x, x));
	}

	// Recursively sorting the first elements of each pair
	std::vector<T> firsts;
	firsts.reserve(pairs.size());
	for (size_t k = 0; k < pairs.size(); ++k)
		firsts.push_back(pairs[k].first);


	// This template instantiates fine for std::vector<T> as well
	fordJohnsonSort(firsts);

	// insterts all sorted firsts 
	std::vector<T> sorted;
	sorted.reserve(container.size());
	sorted.insert(sorted.end(), firsts.begin(), firsts.end());


	for (size_t k = 0; k < pairs.size(); ++k) {
		if (k == pairs.size() - 1 && pairs[k].first == pairs[k].second && container.size() % 2 != 0)
			continue;
		typename std::vector<T>::iterator it =
			std::upper_bound(sorted.begin(), sorted.end(), pairs[k].second);
		sorted.insert(it, pairs[k].second);
	}
	
	// // Write back to the original container 
	container.assign(sorted.begin(), sorted.end());
}

void valid_input(char *argv[])
{
	for(int i = 1; argv[i]; i++)
		for(int j = 0; argv[i][j]; j++)
			if(!std::isdigit(argv[i][j]))
				throw std::invalid_argument("Invalid input. Must be numbers only (positive)");
}
