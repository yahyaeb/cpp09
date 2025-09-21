/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:59:13 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/20 15:38:55 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
PmergeMe::PmergeMe(const std::vector<int>& input) : _vec(input),
												_deq(input.begin(), input.end())
{}

void PmergeMe::sortAll()
{
	// std::sort(_vec.begin(), _vec.end());
	// std::sort(_deq.begin(), _deq.end());
	fordJohnsonSort(_vec);
	fordJohnsonSort(_deq);
}

void PmergeMe::printResults() const
{
	std::cout << "Vecetor: ";
	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;

	std::cout << "Deque: ";
	for (std::deque<int>::const_iterator it = _deq.begin(); it != _deq.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	
}

template <typename Container>
void PmergeMe::fordJohnsonSort(Container& container)
{
    typedef typename Container::value_type T;

    if (container.size() <= 1)
        return;

    // 1) Pair up elements and sort each pair (ascending)
    std::vector< std::pair<T, T> > pairs;
    pairs.reserve(container.size() / 2 + 1); // safe: pairs is a vector

    typename Container::size_type i = 0;
    for (; i + 1 < container.size(); i += 2) {
        T a = container[i];
        T b = container[i + 1];
        if (a > b) {
            T tmp = a; a = b; b = tmp;
        }
        pairs.push_back(std::make_pair(a, b));
    }
    // If odd count, duplicate the last to keep pairs aligned
    if (i < container.size()) {
        T x = container.back();
        pairs.push_back(std::make_pair(x, x));
    }

    // 2) Recursively sort the first elements of each pair
    std::vector<T> firsts;
    firsts.reserve(pairs.size());
    for (size_t k = 0; k < pairs.size(); ++k)
        firsts.push_back(pairs[k].first);

    // This template instantiates fine for std::vector<T> as well
    fordJohnsonSort(firsts);

    // 3) Merge: work in a vector (has reserve + predictable iterators)
    std::vector<T> sorted;
    sorted.reserve(container.size());
    sorted.insert(sorted.end(), firsts.begin(), firsts.end());

	for (size_t k = 0; k < pairs.size(); ++k) {
		typename std::vector<T>::iterator it =
			std::upper_bound(sorted.begin(), sorted.end(), pairs[k].second);
		sorted.insert(it, pairs[k].second);
	}


    // Write back to the original container (vector/deque both support assign)
    container.assign(sorted.begin(), sorted.end());
}