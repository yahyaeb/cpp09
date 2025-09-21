/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:15:20 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/21 17:11:03 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <sstream>

#ifndef RPN_HPP
#define RPN_HPP

class RPN {
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();
		int evaluate(const std::string& expression);
	private:
		std::vector<std::string> tokenize(const std::string& expression);
		bool isOperator(char c);
		int applyOperator(int a, int b, char op);
		bool isNumber(const std::string& token);
};
#endif