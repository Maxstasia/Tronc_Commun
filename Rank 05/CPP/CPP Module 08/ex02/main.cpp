#include "MutantStack.hpp"
#include <iostream>
#include <list>

void testSubject()
{
	std::cout << "\n=== Test from Subject ===" << std::endl;
	
	MutantStack<int> mstack;
	
	mstack.push(5);
	mstack.push(17);
	
	std::cout << "Top: " << mstack.top() << std::endl;
	
	mstack.pop();
	
	std::cout << "Size after pop: " << mstack.size() << std::endl;
	
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	
	// Prouve que l'itérateur fonctionne correctement
	++it;
	--it;
	
	// Affichage des éléments de la pile via les itérateurs
	std::cout << "Iterating through stack: ";
	while (it != ite)
	{
		std::cout << *it;
		if (++it != ite)
			std::cout << " ";
	}
	std::cout << std::endl;
	
	std::stack<int> s(mstack);
}

void testWithList()
{
	std::cout << "\n=== Same Test with std::list ===" << std::endl;
	
	std::list<int> mlist;
	
	mlist.push_back(5);
	mlist.push_back(17);
	
	std::cout << "Back: " << mlist.back() << std::endl;
	
	mlist.pop_back();
	
	std::cout << "Size after pop: " << mlist.size() << std::endl;
	
	mlist.push_back(3);
	mlist.push_back(5);
	mlist.push_back(737);
	mlist.push_back(0);
	
	std::list<int>::iterator it = mlist.begin();
	std::list<int>::iterator ite = mlist.end();
	
	++it;
	--it;
	
	std::cout << "Iterating through list: ";
	while (it != ite)
	{
		std::cout << *it;
		if (++it != ite)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void testReverseIterators()
{
	std::cout << "\n=== Testing Reverse Iterators ===" << std::endl;
	
	MutantStack<int> mstack;
	
	for (int i = 1; i <= 5; i++)
		mstack.push(i * 10);
	
	std::cout << "Forward iteration: ";
	for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	std::cout << "Reverse iteration: ";
	for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
		std::cout << *rit << " ";
	std::cout << std::endl;
}

void testCopyConstructor()
{
	std::cout << "\n=== Testing Copy Constructor ===" << std::endl;
	
	MutantStack<int> mstack1;
	mstack1.push(42);
	mstack1.push(21);
	mstack1.push(84);
	
	MutantStack<int> mstack2(mstack1);
	
	std::cout << "Original stack: ";
	for (MutantStack<int>::iterator it = mstack1.begin(); it != mstack1.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	std::cout << "Copied stack: ";
	for (MutantStack<int>::iterator it = mstack2.begin(); it != mstack2.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	mstack2.push(168);
	
	std::cout << "After modifying copy:" << std::endl;
	std::cout << "Original size: " << mstack1.size() << std::endl;
	std::cout << "Copy size: " << mstack2.size() << std::endl;
}

void testWithStrings()
{
	std::cout << "\n=== Testing with Strings ===" << std::endl;
	
	MutantStack<std::string> mstack;
	
	mstack.push("Hello");
	mstack.push("World");
	mstack.push("42");
	mstack.push("School");
	
	std::cout << "String stack: ";
	for (MutantStack<std::string>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	std::cout << "Top element: " << mstack.top() << std::endl;
	std::cout << "Size: " << mstack.size() << std::endl;
}

void testConstIterators()
{
	std::cout << "\n=== Testing Const Iterators ===" << std::endl;
	
	MutantStack<int> mstack;
	
	for (int i = 0; i < 5; i++)
		mstack.push(i * 2);
	
	const MutantStack<int>& constStack = mstack;
	
	std::cout << "Const iteration: ";
	for (MutantStack<int>::const_iterator it = constStack.begin(); it != constStack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main()
{
	std::cout << "╔═════════════════════════════════╗" << std::endl;
	std::cout << "║   CPP Module 08 - Exercise 02   ║" << std::endl;
	std::cout << "║           MutantStack           ║" << std::endl;
	std::cout << "╚═════════════════════════════════╝" << std::endl;
	
	testSubject();
	testWithList();
	testReverseIterators();
	testCopyConstructor();
	testWithStrings();
	testConstIterators();
	
	std::cout << "\n=== All tests completed ===" << std::endl;
	
	return 0;
}
