#include "Bureaucrat.hpp"

int main()
{
	std::cout << "=== Test 1: Valid Bureaucrat ===" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 50);
		std::cout << alice << std::endl;
		alice.incrementGrade();
		std::cout << alice << std::endl;
		alice.decrementGrade();
		std::cout << alice << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Grade too high (0) ===" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 0);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Grade too low (151) ===" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 151);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Increment from grade 1 ===" << std::endl;
	try
	{
		Bureaucrat dave("Dave", 1);
		std::cout << dave << std::endl;
		dave.incrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Decrement from grade 150 ===" << std::endl;
	try
	{
		Bureaucrat eve("Eve", 150);
		std::cout << eve << std::endl;
		eve.decrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return (0);
}
