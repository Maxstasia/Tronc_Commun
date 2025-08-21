/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:49 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 14:10:55 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"

// Constructeur par défaut
ClapTrap::ClapTrap(void) : _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap default constructor called" << std::endl;
}

// Constructeur avec nom
ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap parameterized constructor called for " << _name << std::endl;
}

// Constructeur de recopie
ClapTrap::ClapTrap(const ClapTrap& src) {
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = src; // Utilise l'opérateur d'affectation
}

// Destructeur
ClapTrap::~ClapTrap(void) {
	std::cout << "ClapTrap destructor called for " << _name << std::endl;
}

// Opérateur d'affectation
ClapTrap& ClapTrap::operator=(const ClapTrap& rhs) {
	std::cout << "ClapTrap assignment operator called" << std::endl;
	if (this != &rhs) { // Vérifie l'auto-affectation
		_name = rhs._name;
		_hitPoints = rhs._hitPoints;
		_energyPoints = rhs._energyPoints;
		_attackDamage = rhs._attackDamage;
	}
	return *this;
}

// Méthode d'attaque
void ClapTrap::attack(const std::string& target) {
	if (_energyPoints > 0 && _hitPoints > 0) {
		std::cout << "ClapTrap " << _name << " attacks " << target 
				  << ", causing " << _attackDamage << " points of damage!" << std::endl;
		_energyPoints--;
	} else {
		std::cout << "ClapTrap " << _name << " cannot attack!" << std::endl;
	}
}

// Méthode de réception de dégâts
void ClapTrap::takeDamage(unsigned int amount) {
	if (amount >= _hitPoints) {
		_hitPoints = 0;
		std::cout << "ClapTrap " << _name << " has been destroyed!" << std::endl;
	}
	else {
		_hitPoints -= amount;
		std::cout << "ClapTrap " << _name << " takes " << amount 
				  << " points of damage! Remaining hit points: " 
				  << _hitPoints << std::endl;
	}
}

// Méthode de réparation
void ClapTrap::beRepaired(unsigned int amount) {
	if (_energyPoints > 0 && _hitPoints > 0) {
		_hitPoints += amount;
		_energyPoints--;
		std::cout << "ClapTrap " << _name << " repairs itself for " 
				  << amount << " hit points! Current hit points: " 
				  << _hitPoints << std::endl;
	} else {
		std::cout << "ClapTrap " << _name << " cannot be repaired!" << std::endl;
	}
}

// Getters
std::string ClapTrap::getName(void) const {
	return _name;
}

unsigned int ClapTrap::getHitPoints(void) const {
	return _hitPoints;
}

unsigned int ClapTrap::getEnergyPoints(void) const {
	return _energyPoints;
}

unsigned int ClapTrap::getAttackDamage(void) const {
	return _attackDamage;
}

// Setters
void ClapTrap::setName(const std::string& name) {
	_name = name;
}

void ClapTrap::setHitPoints(unsigned int hitPoints) {
	_hitPoints = hitPoints;
}
void ClapTrap::setEnergyPoints(unsigned int energyPoints) {
	_energyPoints = energyPoints;
}
void ClapTrap::setAttackDamage(unsigned int attackDamage) {
	_attackDamage = attackDamage;
}

// Surcharge d'opérateur chevron pour l'affichage
std::ostream& operator<<(std::ostream& os, const ClapTrap& clapTrap) {
	os << "ClapTrap Name: " << clapTrap.getName() << "\n"
	   << "Hit Points: " << clapTrap.getHitPoints() << "\n"
	   << "Energy Points: " << clapTrap.getEnergyPoints() << "\n"
	   << "Attack Damage: " << clapTrap.getAttackDamage();
	return os;
}
