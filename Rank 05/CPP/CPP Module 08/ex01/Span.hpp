#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <exception>
# include <limits>

class Span
{
	private:
		unsigned int		_maxSize;
		std::vector<int>	_numbers;
		
		Span();  // Private default constructor
		
	public:
		// Orthodox Canonical Form
		Span(unsigned int N);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();
		
		// Member functions
		void addNumber(int number);
		void addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);
		int shortestSpan() const;
		int longestSpan() const;
		
		// Getters
		unsigned int getSize() const;
		unsigned int getMaxSize() const;
		
		// Exceptions
		class SpanFullException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return "Span is full, cannot add more numbers";
				}
		};
		
		class NoSpanException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return "Not enough numbers to calculate span";
				}
		};
};

#endif
