/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:18:41 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 11:50:33 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"

// Constructeur par défaut
Cat::Cat() : brain(new Brain())
{
	this->type = "Cat";
	std::cout << "Cat: Constructeur par défaut appelé" << std::endl;
	// Initialiser quelques idées spécifiques aux chats
	brain->setIdea(0, "Je veux dormir...");
	brain->setIdea(1, "Où est ma nourriture ?");
	brain->setIdea(2, "Je suis le maître ici !");
}

// Constructeur de copie (copie profonde)
Cat::Cat(const Cat& other) : Animal(other), brain(new Brain(*other.brain))
{
	std::cout << "Cat: Constructeur de copie appelé" << std::endl;
}

// Opérateur d'assignation (copie profonde)
Cat& Cat::operator=(const Cat& other)
{
	std::cout << "Cat: Opérateur d'assignation appelé" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*other.brain);
	}
	return *this;
}

// Destructeur
Cat::~Cat()
{
	std::cout << "Cat: Destructeur appelé" << std::endl;
	delete this->brain;
}

// Méthode makeSound surchargée
void Cat::makeSound() const
{
	std::cout << "Cat: Meow! Meow!" << std::endl;
}

// Getter pour le cerveau
Brain* Cat::getBrain() const
{
	return this->brain;
}

