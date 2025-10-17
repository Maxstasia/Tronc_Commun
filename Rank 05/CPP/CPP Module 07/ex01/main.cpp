#include <iostream>
#include "iter.hpp"

template <typename T>
void printElement(T &element)
{
	std::cout << element << " ";
}

template <typename T>
void printElementConst(T const &element)
{
	std::cout << element << " ";
}

template <typename T>
void increment(T &element)
{
	element++;
}

void toUpper(char &c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
}

int main(void)
{
	// Test avec un tableau d'entiers
	std::cout << "=== Test with int array ===" << std::endl;
	int intArray[] = {1, 2, 3, 4, 5};
	size_t intSize = 5;

	std::cout << "Original array: ";
	::iter(intArray, intSize, printElement<int>);
	std::cout << std::endl;

	std::cout << "After increment: ";
	::iter(intArray, intSize, increment<int>);
	::iter(intArray, intSize, printElement<int>);
	std::cout << std::endl;

	// Test avec un tableau de strings
	std::cout << "\n=== Test with string array ===" << std::endl;
	std::string strArray[] = {"Hello", "World", "42", "School"};
	size_t strSize = 4;

	std::cout << "String array: ";
	::iter(strArray, strSize, printElement<std::string>);
	std::cout << std::endl;

	// Test avec un tableau de char
	std::cout << "\n=== Test with char array ===" << std::endl;
	char charArray[] = {'h', 'e', 'l', 'l', 'o'};
	size_t charSize = 5;

	std::cout << "Original: ";
	::iter(charArray, charSize, printElement<char>);
	std::cout << std::endl;

	std::cout << "To upper: ";
	::iter(charArray, charSize, toUpper);
	::iter(charArray, charSize, printElement<char>);
	std::cout << std::endl;

	// Test avec un tableau const
	std::cout << "\n=== Test with const array ===" << std::endl;
	int const constArray[] = {10, 20, 30, 40, 50};
	size_t constSize = 5;

	std::cout << "Const array: ";
	::iter(constArray, constSize, printElementConst<int>);
	std::cout << std::endl;

	return 0;
}
