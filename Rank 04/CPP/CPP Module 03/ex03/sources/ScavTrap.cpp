/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:39:18 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 17:46:52 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScavTrap.hpp"

// Constructeur par défaut
ScavTrap::ScavTrap(void) : ClapTrap() {
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
	std::cout << "ScavTrap default constructor called" << std::endl;
}

// Constructeur avec nom
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
	std::cout << "ScavTrap parameterized constructor called for " << _name << std::endl;
}

// Constructeur de recopie
ScavTrap::ScavTrap(const ScavTrap& src) : ClapTrap(src) {
	std::cout << "ScavTrap copy constructor called" << std::endl;
	*this = src;
}

// Destructeur
ScavTrap::~ScavTrap(void) {
	std::cout << "ScavTrap destructor called for " << _name << std::endl;
}

// Opérateur d'affectation
ScavTrap& ScavTrap::operator=(const ScavTrap& rhs) {
	std::cout << "ScavTrap assignment operator called" << std::endl;
	if (this != &rhs) {
		ClapTrap::operator=(rhs);
	}
	return *this;
}

// Méthode d'attaque redéfinie
void ScavTrap::attack(const std::string& target) {
	if (_energyPoints > 0 && _hitPoints > 0) {
		std::cout << "ScavTrap " << _name << " attacks " << target 
				  << ", causing " << _attackDamage << " points of damage!" << std::endl;
		_energyPoints--;
	} else {
		std::cout << "ScavTrap " << _name << " cannot attack!" << std::endl;
	}
}

// Méthode spéciale à ScavTrap
void ScavTrap::guardGate(void) {
	std::cout << "ScavTrap " << _name << " is now in Gate keeper mode." << std::endl;
}

// Surcharge d'opérateur chevron pour l'affichage
std::ostream& operator<<(std::ostream& os, const ScavTrap& scavTrap) {
	os << "ScavTrap Name: " << scavTrap.getName() << "\n"
	   << "Hit Points: " << scavTrap.getHitPoints() << "\n"
	   << "Energy Points: " << scavTrap.getEnergyPoints() << "\n"
	   << "Attack Damage: " << scavTrap.getAttackDamage();
	return os;
}
