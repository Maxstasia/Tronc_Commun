/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 16:59:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// Constructeur par défaut
Zombie::Zombie() : name("")
{
	std::cout << "Zombie (unnamed) has been created." << std::endl;
}

// Constructeur avec nom
Zombie::Zombie(std::string name) : name(name)
{
	std::cout << "Zombie " << this->name << " has been created." << std::endl;
}

// Destructeur
Zombie::~Zombie()
{
	std::cout << "Zombie " << this->name << " has been destroyed." << std::endl;
}

// Setter pour le nom
void Zombie::setName(std::string name)
{
	this->name = name;
	std::cout << "Zombie has been named " << this->name << "." << std::endl;
}

// Fonction pour s'annoncer
void Zombie::announce(void)
{
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
