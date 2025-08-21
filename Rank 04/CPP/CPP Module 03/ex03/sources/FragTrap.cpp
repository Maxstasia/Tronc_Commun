/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:55:20 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 18:51:42 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FragTrap.hpp"

// Constructeur par défaut
FragTrap::FragTrap(void) : ClapTrap("Default FragTrap") {
	_hitPoints = 100; // FragTrap a plus de points de vie
	_energyPoints = 100; // FragTrap a plus d'énergie
	_attackDamage = 30; // FragTrap a plus de dégâts d'attaque
	std::cout << "FragTrap default constructor called" << std::endl;
}

// Constructeur avec nom
FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	_hitPoints = 100; // FragTrap a plus de points de vie
	_energyPoints = 100; // FragTrap a plus d'énergie
	_attackDamage = 30; // FragTrap a plus de dégâts d'attaque
	std::cout << "FragTrap parameterized constructor called for " << _name << std::endl;
}

// Constructeur de recopie
FragTrap::FragTrap(const FragTrap& src) : ClapTrap(src) {
	std::cout << "FragTrap copy constructor called" << std::endl;
	*this = src; // Utilise l'opérateur d'affectation
}

// Destructeur
FragTrap::~FragTrap(void) {
	std::cout << "FragTrap destructor called for " << _name << std::endl;
}

// Opérateur d'affectation
FragTrap&		FragTrap::operator=(const FragTrap& rhs) {
	std::cout << "FragTrap assignment operator called" << std::endl;
	if (this != &rhs) { // Vérifie l'auto-affectation
		ClapTrap::operator=(rhs); // Appelle l'opérateur d'affectation de ClapTrap
	}
	return *this;
}

// Méthode d'attaque redéfinie
void			FragTrap::attack(const std::string& target) {
	if (_energyPoints > 0 && _hitPoints > 0) {
		std::cout << "FragTrap " << _name << " attacks " << target 
				  << ", causing " << _attackDamage << " points of damage!" << std::endl;
		_energyPoints--;
	} else {
		std::cout << "FragTrap " << _name << " cannot attack!" << std::endl;
	}
}

// Méthode spéciale à FragTrap
void			FragTrap::highFivesGuys(void) {
	std::cout << "FragTrap " << _name << " requests a high five!" << std::endl;
}

// Surcharge d'opérateur chevron pour l'affichage
std::ostream& operator<<(std::ostream& os, const FragTrap& fragTrap) {
	os << "FragTrap Name: " << fragTrap.getName() << "\n"
	   << "Hit Points: " << fragTrap.getHitPoints() << "\n"
	   << "Energy Points: " << fragTrap.getEnergyPoints() << "\n"
	   << "Attack Damage: " << fragTrap.getAttackDamage();
	return os;
}
