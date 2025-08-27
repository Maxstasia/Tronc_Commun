/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:10:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 11:55:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Animal.hpp"
#include "include/Dog.hpp"
#include "include/Cat.hpp"
#include "include/Brain.hpp"

void testBasicRequirements()
{
	std::cout << "\n========== TEST DES EXIGENCES DE BASE ==========" << std::endl;
	
	// Test du code fourni dans le sujet
	std::cout << "\n--- Test de base (fourni dans le sujet) ---" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << "\n--- Destruction (ne doit pas créer de fuite) ---" << std::endl;
	delete j; // Ne doit pas créer de fuite
	delete i; // Ne doit pas créer de fuite
}

void testArrayOfAnimals()
{
	std::cout << "\n========== TEST TABLEAU D'ANIMAUX ==========" << std::endl;
	
	const int arraySize = 6;
	Animal* animals[arraySize];
	
	std::cout << "\n--- Création du tableau (moitié Dog, moitié Cat) ---" << std::endl;
	// Remplir la moitié avec des chiens
	for (int i = 0; i < arraySize / 2; i++)
	{
		std::cout << "Création Dog[" << i << "]:" << std::endl;
		animals[i] = new Dog();
	}
	
	// Remplir l'autre moitié avec des chats
	for (int i = arraySize / 2; i < arraySize; i++)
	{
		std::cout << "Création Cat[" << i << "]:" << std::endl;
		animals[i] = new Cat();
	}
	
	std::cout << "\n--- Test des sons de tous les animaux ---" << std::endl;
	for (int i = 0; i < arraySize; i++)
	{
		std::cout << "Animal[" << i << "] (" << animals[i]->getType() << ") fait: ";
		animals[i]->makeSound();
	}
	
	std::cout << "\n--- Destruction du tableau (directement en tant qu'Animal) ---" << std::endl;
	for (int i = 0; i < arraySize; i++)
	{
		std::cout << "Destruction Animal[" << i << "]:" << std::endl;
		delete animals[i]; // Destructeur virtuel appelé dans le bon ordre
	}
}

void testDeepCopy()
{
	std::cout << "\n========== TEST DE LA COPIE PROFONDE ==========" << std::endl;
	
	std::cout << "\n--- Création d'un chien original ---" << std::endl;
	Dog* originalDog = new Dog();
	
	// Modifier les idées du chien original
	originalDog->getBrain()->setIdea(0, "Idée originale du chien");
	originalDog->getBrain()->setIdea(1, "Autre idée originale");
	
	std::cout << "\nIdées du chien original:" << std::endl;
	originalDog->getBrain()->printIdeas();
	
	std::cout << "\n--- Test du constructeur de copie ---" << std::endl;
	Dog* copiedDog = new Dog(*originalDog);
	
	std::cout << "\nIdées du chien copié (avant modification):" << std::endl;
	copiedDog->getBrain()->printIdeas();
	
	std::cout << "\n--- Modification des idées du chien copié ---" << std::endl;
	copiedDog->getBrain()->setIdea(0, "Idée modifiée du chien copié");
	copiedDog->getBrain()->setIdea(1, "Autre idée modifiée");
	
	std::cout << "\nIdées du chien original (après modification de la copie):" << std::endl;
	originalDog->getBrain()->printIdeas();
	
	std::cout << "\nIdées du chien copié (après modification):" << std::endl;
	copiedDog->getBrain()->printIdeas();
	
	// Test de copie profonde réussi si les deux sont différents
	if (originalDog->getBrain()->getIdea(0) != copiedDog->getBrain()->getIdea(0))
	{
		std::cout << "\n✓ COPIE PROFONDE RÉUSSIE : Les cerveaux sont indépendants!" << std::endl;
	}
	else
	{
		std::cout << "\n✗ ÉCHEC : Copie superficielle détectée!" << std::endl;
	}
	
	std::cout << "\n--- Destruction des objets de test ---" << std::endl;
	delete originalDog;
	delete copiedDog;
}

int main()
{
std::cout << "======================================" << std::endl;
std::cout << "     TESTS CPP MODULE 04 - EX01      " << std::endl;
std::cout << "    JE NE VEUX PAS BRÛLER LE MONDE    " << std::endl;
std::cout << "======================================" << std::endl;

// Tests complets selon les exigences
testBasicRequirements();
testArrayOfAnimals();
testDeepCopy();

std::cout << "\n======================================" << std::endl;
std::cout << "         FIN DES TESTS                " << std::endl;
std::cout << "======================================" << std::endl;

return 0;
}
