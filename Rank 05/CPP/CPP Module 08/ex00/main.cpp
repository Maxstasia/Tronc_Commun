#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>

void testVector()
{
	std::cout << "\n=== Testing with std::vector ===" << std::endl;
	std::vector<int> vec;
	
	for (int i = 0; i < 10; i++)
		vec.push_back(i * 2);
	
	std::cout << "Container: [";
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i];
		if (i < vec.size() - 1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
	
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 8);
		std::cout << "Found 8 at position: " << std::distance(vec.begin(), it) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 15);
		std::cout << "Found 15 at position: " << std::distance(vec.begin(), it) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "15 not found: " << e.what() << std::endl;
	}
}

void testList()
{
	std::cout << "\n=== Testing with std::list ===" << std::endl;
	std::list<int> lst;
	
	for (int i = 1; i <= 5; i++)
		lst.push_back(i * 3);
	
	std::cout << "Container: [";
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
	{
		std::cout << *it;
		std::list<int>::iterator next = it;
		++next;
		if (next != lst.end())
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
	
	try
	{
		std::list<int>::iterator it = easyfind(lst, 9);
		std::cout << "Found 9 at position: " << std::distance(lst.begin(), it) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	try
	{
		std::list<int>::iterator it = easyfind(lst, 7);
		std::cout << "Found 7 at position: " << std::distance(lst.begin(), it) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "7 not found: " << e.what() << std::endl;
	}
}

void testDeque()
{
	std::cout << "\n=== Testing with std::deque ===" << std::endl;
	std::deque<int> deq;
	
	deq.push_back(42);
	deq.push_back(21);
	deq.push_back(84);
	
	std::cout << "Container: [";
	for (size_t i = 0; i < deq.size(); i++)
	{
		std::cout << deq[i];
		if (i < deq.size() - 1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
	
	try
	{
		std::deque<int>::iterator it = easyfind(deq, 42);
		std::cout << "Found 42 at position: " << std::distance(deq.begin(), it) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	try
	{
		easyfind(deq, 100);
	}
	catch (std::exception& e)
	{
		std::cout << "100 not found: " << e.what() << std::endl;
	}
}

int main()
{
	std::cout << "╔═════════════════════════════════╗" << std::endl;
	std::cout << "║   CPP Module 08 - Exercise 00   ║" << std::endl;
	std::cout << "║            Easy find            ║" << std::endl;
	std::cout << "╚═════════════════════════════════╝" << std::endl;
	
	testVector();
	testList();
	testDeque();
	
	std::cout << "\n=== All tests completed ===" << std::endl;
	
	return 0;
}
