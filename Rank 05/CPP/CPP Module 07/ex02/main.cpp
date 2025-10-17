#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Array.hpp"

#define MAX_VAL 750

int main(int, char**)
{
	// Test du sujet
	Array<int> numbers(MAX_VAL);
	int* mirror = new int[MAX_VAL];
	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}
	//SCOPE
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			return 1;
		}
	}
	try
	{
		numbers[-2] = 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand();
	}
	delete [] mirror;//

	// Tests supplémentaires
	std::cout << "\n=== Additional tests ===" << std::endl;

	// Test tableau vide
	std::cout << "\n--- Empty array test ---" << std::endl;
	Array<int> emptyArray;
	std::cout << "Empty array size: " << emptyArray.size() << std::endl;
	try
	{
		emptyArray[0] = 42;
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// Test avec des strings
	std::cout << "\n--- String array test ---" << std::endl;
	Array<std::string> strArray(3);
	strArray[0] = "Hello";
	strArray[1] = "World";
	strArray[2] = "42";
	
	std::cout << "String array size: " << strArray.size() << std::endl;
	for (unsigned int i = 0; i < strArray.size(); i++)
		std::cout << "strArray[" << i << "] = " << strArray[i] << std::endl;

	// Test de copie profonde
	std::cout << "\n--- Deep copy test ---" << std::endl;
	Array<int> original(5);
	for (unsigned int i = 0; i < 5; i++)
		original[i] = i * 10;

	Array<int> copy(original);
	std::cout << "Original: ";
	for (unsigned int i = 0; i < original.size(); i++)
		std::cout << original[i] << " ";
	std::cout << std::endl;

	std::cout << "Copy: ";
	for (unsigned int i = 0; i < copy.size(); i++)
		std::cout << copy[i] << " ";
	std::cout << std::endl;

	copy[2] = 999;
	std::cout << "After modifying copy[2] = 999:" << std::endl;
	std::cout << "Original[2]: " << original[2] << std::endl;
	std::cout << "Copy[2]: " << copy[2] << std::endl;

	// Test opérateur d'affectation
	std::cout << "\n--- Assignment operator test ---" << std::endl;
	Array<int> assigned;
	assigned = original;
	std::cout << "Assigned size: " << assigned.size() << std::endl;
	assigned[0] = 12345;
	std::cout << "Original[0]: " << original[0] << " (should be 0)" << std::endl;
	std::cout << "Assigned[0]: " << assigned[0] << " (should be 12345)" << std::endl;

	// Test const
	std::cout << "\n--- Const array test ---" << std::endl;
	Array<int> const constArray(original);
	std::cout << "Const array[0]: " << constArray[0] << std::endl;

	return 0;
}
