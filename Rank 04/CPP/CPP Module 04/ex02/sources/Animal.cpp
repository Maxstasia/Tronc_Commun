/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:18:23 by mstasiak          #+#    #+#             */
/*   Updated: 2025/09/03 13:13:00 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"

// Constructeur par défaut
Animal::Animal() : type("Animal")
{
	std::cout << "Animal: Constructeur par défaut appelé" << std::endl;
}

// Constructeur de copie
Animal::Animal(const Animal& other) : type(other.type)
{
	std::cout << "Animal: Constructeur de copie appelé" << std::endl;
}

// Opérateur d'assignation
Animal& Animal::operator=(const Animal& other)
{
	std::cout << "Animal: Opérateur d'assignation appelé" << std::endl;
	if (this != &other)
	{
		this->type = other.type;
	}
	return *this;
}

// Destructeur
Animal::~Animal()
{
	std::cout << "Animal: Destructeur appelé" << std::endl;
}

void Animal::makeSound() const
{
	std::cout << "Animal: Bruit indéfini" << std::endl;
}

// Getter pour le type
std::string Animal::getType() const
{
	return this->type;
}

