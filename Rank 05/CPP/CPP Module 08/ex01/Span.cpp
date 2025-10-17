#include "Span.hpp"
#include <algorithm>
#include <climits>

// Orthodox Canonical Form

Span::Span(unsigned int N) : _maxSize(N)
{
}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers)
{
}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}

Span::~Span()
{
}

// Member functions

void Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw SpanFullException();
	_numbers.push_back(number);
}

void Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	while (begin != end)
	{
		if (_numbers.size() >= _maxSize)
			throw SpanFullException();
		_numbers.push_back(*begin);
		++begin;
	}
}

int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw NoSpanException();
	
	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());
	
	int minSpan = INT_MAX;
	for (size_t i = 1; i < sorted.size(); i++)
	{
		int span = sorted[i] - sorted[i - 1];
		if (span < minSpan)
			minSpan = span;
	}
	
	return minSpan;
}

int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw NoSpanException();
	
	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());
	
	return sorted.back() - sorted.front();
}

// Getters

unsigned int Span::getSize() const
{
	return _numbers.size();
}

unsigned int Span::getMaxSize() const
{
	return _maxSize;
}
