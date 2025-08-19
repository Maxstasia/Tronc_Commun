/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:49 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/19 13:41:47 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"

// Constructeur par défaut : initialise la valeur à 0
Fixed::Fixed(void) : _fixedPointValue(0) {
	std::cout << "Default constructor called" << std::endl;
}

// Constructeur de recopie : copie la valeur brute d'un autre objet
Fixed::Fixed(const Fixed& src) {
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

// Opérateur d'affectation : copie la valeur brute, vérifie l'auto-affectation
Fixed&	Fixed::operator=(const Fixed& rhs) {
	std::cout << "Copy assignment operator called" << std::endl;
	_fixedPointValue = rhs.getRawBits();
	return (*this);
}

// Destructeur : rien à libérer ici, juste un message
Fixed::~Fixed(void) {
	std::cout << "Destructor called" << std::endl;
}

// Retourne la valeur brute
int		Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return(_fixedPointValue);
}

// Définit la valeur brute
void	Fixed::setRawBits(int const raw) {
	std::cout << "setRawBits member function called" << std::endl;
	_fixedPointValue = raw;
}

const int Fixed::_fractionalBits;
