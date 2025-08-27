/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:18:41 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 11:31:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"

// Constructeur par défaut
Cat::Cat()
{
	this->type = "Cat";
	std::cout << "Cat: Constructeur par défaut appelé" << std::endl;
}

// Constructeur de copie
Cat::Cat(const Cat& other) : Animal(other)
{
	std::cout << "Cat: Constructeur de copie appelé" << std::endl;
}

// Opérateur d'assignation
Cat& Cat::operator=(const Cat& other)
{
	std::cout << "Cat: Opérateur d'assignation appelé" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
	}
	return *this;
}

// Destructeur
Cat::~Cat()
{
	std::cout << "Cat: Destructeur appelé" << std::endl;
}

// Méthode makeSound surchargée
void Cat::makeSound() const
{
	std::cout << "Cat: Meow! Meow!" << std::endl;
}

