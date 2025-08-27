/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:35:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 11:37:54 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Animal.hpp"
#include "include/Dog.hpp"
#include "include/Cat.hpp"
#include "include/WrongAnimal.hpp"
#include "include/WrongCat.hpp"

void testPolymorphism()
{
	std::cout << "\n========== TEST DU POLYMORPHISME CORRECT ==========" << std::endl;
	
	// Test du code fourni dans le sujet
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << "\n--- Tests des types ---" << std::endl;
	std::cout << "Type de j (Dog): " << j->getType() << std::endl;
	std::cout << "Type de i (Cat): " << i->getType() << std::endl;
	std::cout << "Type de meta (Animal): " << meta->getType() << std::endl;
	
	std::cout << "\n--- Tests des sons (polymorphisme correct) ---" << std::endl;
	std::cout << "Cat fait: ";
	i->makeSound();
	std::cout << "Dog fait: ";
	j->makeSound();
	std::cout << "Animal fait: ";
	meta->makeSound();
	
	std::cout << "\n--- Destruction des objets ---" << std::endl;
	delete meta;
	delete j;
	delete i;
}

void testWrongPolymorphism()
{
	std::cout << "\n========== TEST DU POLYMORPHISME INCORRECT ==========" << std::endl;
	
	// Test avec les classes Wrong pour montrer le problème
	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongCat = new WrongCat();
	
	std::cout << "\n--- Tests des types (Wrong) ---" << std::endl;
	std::cout << "Type de wrongCat: " << wrongCat->getType() << std::endl;
	std::cout << "Type de wrongMeta: " << wrongMeta->getType() << std::endl;
	
	std::cout << "\n--- Tests des sons (polymorphisme INCORRECT) ---" << std::endl;
	std::cout << "WrongCat fait: ";
	wrongCat->makeSound();
	std::cout << "WrongAnimal fait: ";
	wrongMeta->makeSound();
	
	std::cout << "\n--- Destruction des objets (Wrong) ---" << std::endl;
	delete wrongMeta;
	delete wrongCat; // Problème: seul le destructeur de WrongAnimal sera appelé!
}

void testDirectInstances()
{
	std::cout << "\n========== TEST DES INSTANCES DIRECTES ==========" << std::endl;
	
	std::cout << "\n--- Création d'instances directes ---" << std::endl;
	Animal animal;
	Dog dog;
	Cat cat;
	
	std::cout << "\n--- Tests des sons (instances directes) ---" << std::endl;
	std::cout << "Animal direct fait: ";
	animal.makeSound();
	std::cout << "Dog direct fait: ";
	dog.makeSound();
	std::cout << "Cat direct fait: ";
	cat.makeSound();
	
	std::cout << "\n--- Tests des types (instances directes) ---" << std::endl;
	std::cout << "Type animal: " << animal.getType() << std::endl;
	std::cout << "Type dog: " << dog.getType() << std::endl;
	std::cout << "Type cat: " << cat.getType() << std::endl;
	
	std::cout << "\n--- Fin du scope (destruction automatique) ---" << std::endl;
}

void testCopyAndAssignment()
{
	std::cout << "\n========== TEST DE COPIE ET ASSIGNATION ==========" << std::endl;
	
	std::cout << "\n--- Test de constructeur de copie ---" << std::endl;
	Dog originalDog;
	Dog copiedDog(originalDog);
	
	std::cout << "\n--- Test d'opérateur d'assignation ---" << std::endl;
	Cat cat1;
	Cat cat2;
	cat2 = cat1;
	
	std::cout << "\n--- Tests des types après copie ---" << std::endl;
	std::cout << "Type original dog: " << originalDog.getType() << std::endl;
	std::cout << "Type copied dog: " << copiedDog.getType() << std::endl;
	std::cout << "Type cat1: " << cat1.getType() << std::endl;
	std::cout << "Type cat2: " << cat2.getType() << std::endl;
	
	std::cout << "\n--- Fin du scope (destruction automatique) ---" << std::endl;
}

void testArrayOfAnimals()
{
	std::cout << "\n========== TEST AVEC TABLEAU D'ANIMAUX ==========" << std::endl;
	
	// Création d'un tableau d'animaux
	const Animal* animals[4];
	animals[0] = new Animal();
	animals[1] = new Dog();
	animals[2] = new Cat();
	animals[3] = new Dog();
	
	std::cout << "\n--- Tests en boucle ---" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Animal[" << i << "] est un " << animals[i]->getType() << " et fait: ";
		animals[i]->makeSound();
	}
	
	std::cout << "\n--- Destruction du tableau ---" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		delete animals[i];
	}
}

int main()
{
	std::cout << "======================================" << std::endl;
	std::cout << "     TESTS CPP MODULE 04 - EX00      " << std::endl;
	std::cout << "          POLYMORPHISME               " << std::endl;
	std::cout << "======================================" << std::endl;
	
	// Tests complets
	testPolymorphism();
	testWrongPolymorphism();
	testDirectInstances();
	testCopyAndAssignment();
	testArrayOfAnimals();
	
	std::cout << std::endl;
	std::cout << "======================================" << std::endl;
	std::cout << "            FIN DES TESTS             " << std::endl;
	std::cout << "======================================" << std::endl;
	
	return 0;
}
