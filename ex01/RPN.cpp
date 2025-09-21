/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:15:08 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/09/21 17:18:35 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{}
RPN::RPN(const RPN& other)
{
	(void) other;
}
RPN& RPN::operator=(const RPN& other)
{
	(void) other;
	return *this;
}

RPN::~RPN()
{}

bool RPN::isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int RPN::applyOperator(int a, int b, char op) {
	switch (op) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/':
			if (b == 0)
				throw std::runtime_error("Error: Division by zero");
			return a / b;
		default:
			throw std::runtime_error("Error: Unknown operator");
	}
}

bool RPN::isNumber(const std::string& token) {
	return token.size() == 1 && std::isdigit(token[0]);
}

std::vector<std::string> RPN::tokenize(const std::string& expression) {
	std::vector<std::string> tokens;
	std::istringstream iss(expression);
	std::string token;
	while (iss >> token) {
		tokens.push_back(token);
	}
	return tokens;
}
int RPN::evaluate(const std::string& expression) {
	std::stack<int> st;
	std::vector<std::string> tokens = tokenize(expression);

	for (std::vector<std::string>::const_iterator it = tokens.begin();
		 it != tokens.end(); ++it)
	{
		const std::string &token = *it;

		if (isNumber(token)) {
			// C++98-friendly integer parse
			std::istringstream iss(token);
			int val = 0;
			if (!(iss >> val) || !iss.eof())
				throw std::runtime_error("Error: Invalid number '" + token + "'");
			st.push(val);
		}
		else if (token.size() == 1 && isOperator(token[0])) {
			if (st.size() < 2)
				throw std::runtime_error("Error: Insufficient values in expression");
			int b = st.top();
			st.pop();
			int a = st.top();
			st.pop();
			int result = applyOperator(a, b, token[0]);
			st.push(result);
		}
		else {
			throw std::runtime_error("Error: Invalid token '" + token + "'");
		}
	}

	if (st.size() != 1)
		throw std::runtime_error("Error: The user input has too many values");

	return st.top();
}
