/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:08:02 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/22 10:00:06 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/DiamondTrap.hpp"

// Constructeur par défaut
DiamondTrap::DiamondTrap(void) : ClapTrap("Default_clap_name"), ScavTrap(), FragTrap(), _name("Default") {
	std::cout << "DiamondTrap default constructor called" << std::endl;
	
	// Hit points de FragTrap (100)
	this->_hitPoints = 100;
	// Energy points de ScavTrap (50)  
	this->_energyPoints = 50;
	// Attack damage de FragTrap (30)
	this->_attackDamage = 30;
}

// Constructeur avec nom
DiamondTrap::DiamondTrap(const std::string& name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name) {
	std::cout << "DiamondTrap named constructor called for " << name << std::endl;
	
	// Hit points de FragTrap (100)
	this->_hitPoints = 100;
	// Energy points de ScavTrap (50)
	this->_energyPoints = 50;
	// Attack damage de FragTrap (30)
	this->_attackDamage = 30;
}

// Constructeur de copie
DiamondTrap::DiamondTrap(const DiamondTrap& src) : ClapTrap(src), ScavTrap(src), FragTrap(src), _name(src._name) {
	std::cout << "DiamondTrap copy constructor called" << std::endl;
}

// Destructeur
DiamondTrap::~DiamondTrap(void) {
	std::cout << "DiamondTrap destructor called for " << this->_name << std::endl;
}

// Opérateur d'affectation
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& rhs) {
	std::cout << "DiamondTrap assignment operator called" << std::endl;
	if (this != &rhs) {
		ClapTrap::operator=(rhs);
		this->_name = rhs._name;
	}
	return *this;
}

// Méthode spéciale whoAmI
void DiamondTrap::whoAmI(void) {
	std::cout << "I am " << this->_name << " and my ClapTrap name is " << ClapTrap::_name << std::endl;
}

// Getter pour le nom
std::string DiamondTrap::getName(void) const {
	return this->_name;
}

// Surcharge d'opérateur pour l'affichage
std::ostream& operator<<(std::ostream& os, const DiamondTrap& diamondTrap) {
	os << "DiamondTrap " << diamondTrap.getName() 
		<< " [HP: " << diamondTrap.getHitPoints() 
		<< ", EP: " << diamondTrap.getEnergyPoints() 
		<< ", AD: " << diamondTrap.getAttackDamage() << "]";
	return os;
}


