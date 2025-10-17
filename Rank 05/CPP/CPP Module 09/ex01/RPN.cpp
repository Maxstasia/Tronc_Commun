#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

RPN::RPN(void)
{
}

RPN::RPN(RPN const &src)
{
	*this = src;
}

RPN::~RPN(void)
{
}

RPN &RPN::operator=(RPN const &rhs)
{
	if (this != &rhs)
		this->_stack = rhs._stack;
	return (*this);
}

bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isDigit(char c) const
{
	return (c >= '0' && c <= '9');
}

double RPN::performOperation(double a, double b, char op)
{
	switch (op)
	{
		case '+':
			return (a + b);
		case '-':
			return (a - b);
		case '*':
			return (a * b);
		case '/':
			if (b == 0)
				throw std::runtime_error("Error: division by zero");
			return (a / b);
		default:
			throw std::runtime_error("Error: invalid operator");
	}
}

void RPN::calculate(std::string const &expression)
{
	std::istringstream iss(expression);
	std::string token;
	
	while (iss >> token)
	{
		// Si c'est un nombre (un seul chiffre selon le sujet)
		if (token.length() == 1 && isDigit(token[0]))
		{
			_stack.push(token[0] - '0');
		}
		// Si c'est un opérateur
		else if (token.length() == 1 && isOperator(token[0]))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error: insufficient operands");
			
			double b = _stack.top();
			_stack.pop();
			double a = _stack.top();
			_stack.pop();
			
			double result = performOperation(a, b, token[0]);
			_stack.push(result);
		}
		else
		{
			throw std::runtime_error("Error: invalid token");
		}
	}
	
	if (_stack.size() != 1)
		throw std::runtime_error("Error: invalid expression");
	
	std::cout << _stack.top() << std::endl;
}
