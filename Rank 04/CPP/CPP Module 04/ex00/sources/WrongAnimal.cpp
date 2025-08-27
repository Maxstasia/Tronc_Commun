/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 11:31:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongAnimal.hpp"

// Constructeur par défaut
WrongAnimal::WrongAnimal() : type("WrongAnimal")
{
	std::cout << "WrongAnimal: Constructeur par défaut appelé" << std::endl;
}

// Constructeur de copie
WrongAnimal::WrongAnimal(const WrongAnimal& other) : type(other.type)
{
	std::cout << "WrongAnimal: Constructeur de copie appelé" << std::endl;
}

// Opérateur d'assignation
WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	std::cout << "WrongAnimal: Opérateur d'assignation appelé" << std::endl;
	if (this != &other)
	{
		this->type = other.type;
	}
	return *this;
}

// Destructeur (PAS virtual)
WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal: Destructeur appelé" << std::endl;
}

// Méthode makeSound (PAS virtual)
void WrongAnimal::makeSound() const
{
	std::cout << "WrongAnimal: *son générique de wrong animal*" << std::endl;
}

// Getter pour le type
std::string WrongAnimal::getType() const
{
	return this->type;
}
