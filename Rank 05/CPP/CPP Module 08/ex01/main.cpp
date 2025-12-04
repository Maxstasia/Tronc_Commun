#include "Span.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

void testBasic()
{
	std::cout << "\n=== Basic Test (from subject) ===" << std::endl;
	
	Span sp = Span(5);
	
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	
	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp.longestSpan() << std::endl;
}

void testExceptions()
{
	std::cout << "\n=== Testing Exceptions ===" << std::endl;
	
	Span sp(3);
	
	sp.addNumber(1);
	sp.addNumber(2);
	sp.addNumber(3);
	
	std::cout << "Span filled with 3 numbers (max capacity)" << std::endl;
	
	try
	{
		sp.addNumber(4);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
	
	Span empty(10);
	try
	{
		std::cout << "Trying to get span with 0 numbers..." << std::endl;
		empty.shortestSpan();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
	
	Span one(10);
	one.addNumber(42);
	try
	{
		std::cout << "Trying to get span with 1 number..." << std::endl;
		one.longestSpan();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
}

void testLargeRange()
{
	std::cout << "\n=== Testing Large Range (10000 numbers) ===" << std::endl;
	
	Span sp(10000);
	std::vector<int> numbers;
	
	std::srand(std::time(NULL));
	
	for (int i = 0; i < 10000; i++)
		numbers.push_back(std::rand());
	
	try
	{
		sp.addNumber(numbers.begin(), numbers.end());
		std::cout << "Successfully added 10000 numbers" << std::endl;
		std::cout << "Current size: " << sp.getSize() << " / " << sp.getMaxSize() << std::endl;
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void testEdgeCases()
{
	std::cout << "\n=== Testing Edge Cases ===" << std::endl;
	
	// Test with negative numbers
	Span sp1(5);
	sp1.addNumber(-10);
	sp1.addNumber(-5);
	sp1.addNumber(0);
	sp1.addNumber(5);
	sp1.addNumber(10);
	
	std::cout << "Span with negative numbers:" << std::endl;
	std::cout << "Shortest span: " << sp1.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp1.longestSpan() << std::endl;
	
	// Test with identical numbers
	Span sp2(3);
	sp2.addNumber(42);
	sp2.addNumber(42);
	sp2.addNumber(42);
	
	std::cout << "\nSpan with identical numbers:" << std::endl;
	std::cout << "Shortest span: " << sp2.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp2.longestSpan() << std::endl;
}

void testCopyConstructor()
{
	std::cout << "\n=== Testing Copy Constructor ===" << std::endl;
	
	Span sp1(5);
	sp1.addNumber(1);
	sp1.addNumber(2);
	sp1.addNumber(3);
	
	Span sp2(sp1);
	
	std::cout << "Original span size: " << sp1.getSize() << std::endl;
	std::cout << "Copied span size: " << sp2.getSize() << std::endl;
	std::cout << "Both spans shortest: " << sp1.shortestSpan() << " and " << sp2.shortestSpan() << std::endl;
}

int main()
{
	std::cout << "╔═════════════════════════════════╗" << std::endl;
	std::cout << "║   CPP Module 08 - Exercise 01   ║" << std::endl;
	std::cout << "║              Span               ║" << std::endl;
	std::cout << "╚═════════════════════════════════╝" << std::endl;
	
	testBasic();
	testExceptions();
	testLargeRange();
	testEdgeCases();
	testCopyConstructor();
	
	std::cout << "\n=== All tests completed ===" << std::endl;
	
	return 0;
}
