#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

// Génère aléatoirement une instance de A, B ou C et retourne un pointeur sur la classe de base
Base* generate(void)
{
	int random = std::rand() % 3;

	switch (random)
	{
		case 0:
			std::cout << "Generated: A" << std::endl;
			return new A();
		case 1:
			std::cout << "Generated: B" << std::endl;
			return new B();
		case 2:
			std::cout << "Generated: C" << std::endl;
			return new C();
		default:
			return NULL;
	}
}

// Identifie le type de l'objet pointé par p et affiche A, B ou C
void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A";
	else if (dynamic_cast<B*>(p))
		std::cout << "B";
	else if (dynamic_cast<C*>(p))
		std::cout << "C";
	else
		std::cout << "Unknown type";
}

// Interdit d'utiliser un pointeur dans cette fonction (sinon c'est trop facile)
// Identifie le type de l'objet référencé par p et affiche A, B ou C
void identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A";
		return;
	}
	catch (std::exception)
	{
	}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B";
		return;
	}
	catch (std::exception)
	{
	}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C";
		return;
	}
	catch (std::exception)
	{
	}

	std::cout << "Unknown type";
}

int main(void)
{
	std::srand(std::time(NULL));

	std::cout << "=== Test 1: Identify by pointer ===" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		Base* ptr = generate();
		std::cout << "Identified by pointer: ";
		identify(ptr);
		std::cout << std::endl;
		std::cout << "Identified by reference: ";
		identify(*ptr);
		std::cout << std::endl;
		delete ptr;
		std::cout << std::endl;
	}

	std::cout << "=== Test 2: Specific types ===" << std::endl;
	
	A* a = new A();
	std::cout << "Created A:" << std::endl;
	std::cout << "  By pointer: ";
	identify(a);
	std::cout << std::endl;
	std::cout << "  By reference: ";
	identify(*a);
	std::cout << std::endl;
	delete a;

	B* b = new B();
	std::cout << "\nCreated B:" << std::endl;
	std::cout << "  By pointer: ";
	identify(b);
	std::cout << std::endl;
	std::cout << "  By reference: ";
	identify(*b);
	std::cout << std::endl;
	delete b;

	C* c = new C();
	std::cout << "\nCreated C:" << std::endl;
	std::cout << "  By pointer: ";
	identify(c);
	std::cout << std::endl;
	std::cout << "  By reference: ";
	identify(*c);
	std::cout << std::endl;
	delete c;

	return 0;
}
