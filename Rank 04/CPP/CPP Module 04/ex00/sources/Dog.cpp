/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:18:32 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 11:31:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"

// Constructeur par défaut
Dog::Dog()
{
	this->type = "Dog";
	std::cout << "Dog: Constructeur par défaut appelé" << std::endl;
}

// Constructeur de copie
Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout << "Dog: Constructeur de copie appelé" << std::endl;
}

// Opérateur d'assignation
Dog& Dog::operator=(const Dog& other)
{
	std::cout << "Dog: Opérateur d'assignation appelé" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
	}
	return *this;
}

// Destructeur
Dog::~Dog()
{
	std::cout << "Dog: Destructeur appelé" << std::endl;
}

// Méthode makeSound surchargée
void Dog::makeSound() const
{
	std::cout << "Dog: Woof! Woof!" << std::endl;
}

