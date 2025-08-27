/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 11:31:43 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongCat.hpp"

// Constructeur par défaut
WrongCat::WrongCat()
{
	this->type = "WrongCat";
	std::cout << "WrongCat: Constructeur par défaut appelé" << std::endl;
}

// Constructeur de copie
WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
	std::cout << "WrongCat: Constructeur de copie appelé" << std::endl;
}

// Opérateur d'assignation
WrongCat& WrongCat::operator=(const WrongCat& other)
{
	std::cout << "WrongCat: Opérateur d'assignation appelé" << std::endl;
	if (this != &other)
	{
		WrongAnimal::operator=(other);
	}
	return *this;
}

// Destructeur (PAS virtual)
WrongCat::~WrongCat()
{
	std::cout << "WrongCat: Destructeur appelé" << std::endl;
}

// Méthode makeSound surchargée (PAS virtual)
void WrongCat::makeSound() const
{
	std::cout << "WrongCat: Meow! Meow! (mais ça ne marchera pas en polymorphisme)" << std::endl;
}
