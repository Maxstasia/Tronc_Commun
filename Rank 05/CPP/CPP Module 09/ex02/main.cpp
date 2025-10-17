#include "PmergeMe.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: no input provided" << std::endl;
		std::cerr << "Usage: ./PmergeMe [positive integers]" << std::endl;
		return (1);
	}
	
	try
	{
		PmergeMe pmm;
		pmm.parseInput(argc, argv);
		
		// Afficher avant le tri
		pmm.displayBefore();
		
		// Trier avec std::vector
		clock_t startVector = clock();
		pmm.sortVector();
		clock_t endVector = clock();
		double timeVector = static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1000000;
		
		// Trier avec std::deque
		clock_t startDeque = clock();
		pmm.sortDeque();
		clock_t endDeque = clock();
		double timeDeque = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000;
		
		// Afficher après le tri
		pmm.displayAfter();
		
		// Afficher les temps
		std::cout << std::fixed << std::setprecision(5);
		std::cout << "Time to process a range of " << pmm.getVector().size() 
				  << " elements with std::vector : " << timeVector << " us" << std::endl;
		std::cout << "Time to process a range of " << pmm.getDeque().size() 
				  << " elements with std::deque  : " << timeDeque << " us" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	
	return (0);
}
