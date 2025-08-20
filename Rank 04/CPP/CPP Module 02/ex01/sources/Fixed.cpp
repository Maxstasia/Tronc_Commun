/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:49 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/20 11:55:23 by mstasiak         ###   ########.fr       */
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

Fixed::Fixed(const int srcInt) : _fixedPointValue(srcInt << _fractionalBits) {
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float srcFloat) 
{
	_fixedPointValue = static_cast<int>(roundf(srcFloat * (1 << _fractionalBits)));
	std::cout << "Float constructor called" << std::endl;
}

// Destructeur : rien à libérer ici, juste un message
Fixed::~Fixed(void) {
	std::cout << "Destructor called" << std::endl;
}






// Opérateur d'affectation : copie la valeur brute, vérifie l'auto-affectation
Fixed&			Fixed::operator=(const Fixed& rhs) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs) // Vérifie l’auto-affectation
		_fixedPointValue = rhs.getRawBits();
	return (*this);
}

// Surcharge de l’opérateur d’insertion
std::ostream&	operator<<(std::ostream& os, const Fixed& fixed) {
	os << fixed.toFloat();
	return os;
}






// Retourne la valeur brute
int				Fixed::getRawBits(void) const {
	//std::cout << "getRawBits member function called" << std::endl;
	return(_fixedPointValue);
}

// Définit la valeur brute
void			Fixed::setRawBits(int const raw) {
	//std::cout << "setRawBits member function called" << std::endl;
	_fixedPointValue = raw;
}

// Conversion en flottant
float			Fixed::toFloat(void) const {
    return static_cast<float>(_fixedPointValue) / (1 << _fractionalBits);
}

// Conversion en entier
int				Fixed::toInt(void) const {
    return _fixedPointValue >> _fractionalBits;
}

const int Fixed::_fractionalBits;
