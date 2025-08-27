/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:18:32 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 11:50:33 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"

// Constructeur par défaut
Dog::Dog() : brain(new Brain())
{
	this->type = "Dog";
	std::cout << "Dog: Constructeur par défaut appelé" << std::endl;
	// Initialiser quelques idées spécifiques aux chiens
	brain->setIdea(0, "Je veux jouer !");
	brain->setIdea(1, "Où est ma balle ?");
	brain->setIdea(2, "J'adore mon maître !");
}

// Constructeur de copie (copie profonde)
Dog::Dog(const Dog& other) : Animal(other), brain(new Brain(*other.brain))
{
	std::cout << "Dog: Constructeur de copie appelé" << std::endl;
}

// Opérateur d'assignation (copie profonde)
Dog& Dog::operator=(const Dog& other)
{
	std::cout << "Dog: Opérateur d'assignation appelé" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*other.brain);
	}
	return *this;
}

// Destructeur
Dog::~Dog()
{
	std::cout << "Dog: Destructeur appelé" << std::endl;
	delete this->brain;
}

// Méthode makeSound surchargée
void Dog::makeSound() const
{
	std::cout << "Dog: Woof! Woof!" << std::endl;
}

// Getter pour le cerveau
Brain* Dog::getBrain() const
{
	return this->brain;
}

