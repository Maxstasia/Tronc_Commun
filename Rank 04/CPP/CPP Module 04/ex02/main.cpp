/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:10:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 13:01:19 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Animal.hpp"
#include "include/Dog.hpp"
#include "include/Cat.hpp"
#include "include/Brain.hpp"

int main()
{
	std::cout << "=== Test de la classe abstraite Animal ===" << std::endl;
	std::cout << std::endl;

	// Cette ligne ne compilerait pas car Animal est maintenant abstraite :
	// Animal animal; // ERROR: Cannot instantiate abstract class
	// 
	// La classe Animal possède maintenant une méthode purement virtuelle :
	// virtual void makeSound() const = 0;
	// 
	// Cela rend la classe abstraite et empêche son instanciation directe.
	// Seules les classes dérivées qui implémentent makeSound() peuvent être instanciées.

	std::cout << "Création d'un tableau d'animaux (pointeurs)..." << std::endl;
	const Animal* animals[4];
	
	std::cout << std::endl << "--- Création des animaux ---" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (i % 2 == 0)
		{
			std::cout << "Création d'un Dog [" << i << "]:" << std::endl;
			animals[i] = new Dog();
		}
		else
		{
			std::cout << "Création d'un Cat [" << i << "]:" << std::endl;
			animals[i] = new Cat();
		}
		std::cout << std::endl;
	}

	std::cout << "--- Test des sons ---" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Animal [" << i << "] (type: " << animals[i]->getType() << "): ";
		animals[i]->makeSound();
	}

	std::cout << std::endl << "--- Test de copie profonde ---" << std::endl;
	Dog* originalDog = new Dog();
	originalDog->getBrain()->setIdea(0, "Je suis un chien original!");
	originalDog->getBrain()->setIdea(1, "J'aime les os!");

	std::cout << "Idée originale [0]: " << originalDog->getBrain()->getIdea(0) << std::endl;
	std::cout << "Idée originale [1]: " << originalDog->getBrain()->getIdea(1) << std::endl;

	Dog* copiedDog = new Dog(*originalDog);
	std::cout << "Idée copiée [0]: " << copiedDog->getBrain()->getIdea(0) << std::endl;
	std::cout << "Idée copiée [1]: " << copiedDog->getBrain()->getIdea(1) << std::endl;

	// Modification de l'original
	originalDog->getBrain()->setIdea(0, "Mon idée a changé!");
	std::cout << "Après modification de l'original:" << std::endl;
	std::cout << "Idée originale [0]: " << originalDog->getBrain()->getIdea(0) << std::endl;
	std::cout << "Idée copiée [0]: " << copiedDog->getBrain()->getIdea(0) << std::endl;

	std::cout << std::endl << "--- Destruction des objets ---" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Suppression de l'animal [" << i << "]:" << std::endl;
		delete animals[i];
	}

	std::cout << "Suppression du chien original:" << std::endl;
	delete originalDog;
	std::cout << "Suppression du chien copié:" << std::endl;
	delete copiedDog;

	std::cout << std::endl << "=== Test terminé ===" << std::endl;
	return 0;
}