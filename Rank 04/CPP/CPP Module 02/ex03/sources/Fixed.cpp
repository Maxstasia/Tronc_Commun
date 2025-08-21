/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:49 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 11:30:46 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"

// ------------------------------------------------------------------------------------------------------------------------------------------
// Constructeur par défaut : initialise la valeur à 0
Fixed::Fixed(void) : _fixedPointValue(0) {}

// Constructeur de recopie : copie la valeur brute d'un autre objet
Fixed::Fixed(const Fixed& src) {
	*this = src;
}

// Constructeur depuis un int
Fixed::Fixed(const int srcInt) : _fixedPointValue(srcInt << _fractionalBits) {}

// Constructeur depuis un float
Fixed::Fixed(const float srcFloat) : _fixedPointValue(static_cast<int>(roundf(srcFloat * (1 << _fractionalBits)))) {}

// Destructeur
Fixed::~Fixed(void) {}
// ------------------------------------------------------------------------------------------------------------------------------------------






// ------------------------------------------------------------------------------------------------------------------------------------------
// Opérateur d'affectation : copie la valeur brute, vérifie l'auto-affectation
Fixed&			Fixed::operator=(const Fixed& rhs) {
    if (this != &rhs) // Vérifie l’auto-affectation
	{
        _fixedPointValue = rhs.getRawBits();
    }
    return (*this);
}



// Opérateur de comparaison
bool			Fixed::operator>(const Fixed& rhs) {
	if (_fixedPointValue > rhs.getRawBits())
		return (true);
	return(false);
}
bool			Fixed::operator<(const Fixed& rhs) {
	if (_fixedPointValue < rhs.getRawBits())
		return (true);
	return(false);
}
bool			Fixed::operator>=(const Fixed& rhs) {
	if (_fixedPointValue >= rhs.getRawBits())
		return (true);
	return(false);
}
bool			Fixed::operator<=(const Fixed& rhs) {
	if (_fixedPointValue <= rhs.getRawBits())
		return (true);
	return(false);
}
bool			Fixed::operator==(const Fixed& rhs) {
	if (_fixedPointValue == rhs.getRawBits())
		return (true);
	return(false);
}
bool			Fixed::operator!=(const Fixed& rhs) {
	if (_fixedPointValue != rhs.getRawBits())
		return (true);
	return(false);
}



// Opérateur arithmétiques
Fixed				Fixed::operator+(const Fixed& rhs) const {
	Fixed result;
	result.setRawBits(_fixedPointValue + rhs.getRawBits());
	return result;
}
Fixed				Fixed::operator-(const Fixed& rhs) const {
	Fixed result;
	result.setRawBits(_fixedPointValue - rhs.getRawBits());
	return result;
}
Fixed				Fixed::operator*(const Fixed& rhs) const {
	Fixed result;
	result.setRawBits((_fixedPointValue * rhs.getRawBits()) >> _fractionalBits);
	return result;
}
Fixed				Fixed::operator/(const Fixed& rhs) const {
	Fixed result;
	if (rhs.getRawBits() == 0) {
		std::cerr << "Error: Division by zero" << std::endl;
		return result;
	}
	result.setRawBits((_fixedPointValue << _fractionalBits) / rhs.getRawBits());
	return result;
}



// Opérateur d'incrémentation
// Pré-incrémentation
Fixed&			Fixed::operator++(void) {
	_fixedPointValue++;
	return (*this);
}
// Post-incrémentation
Fixed&			Fixed::operator++(int) {
	Fixed* temp = new Fixed(*this); // Crée une copie de l'objet actuel
	_fixedPointValue++;
	return (*temp); // Retourne la copie avant l'incrémentation
}

// Opérateur de décrémentation
// Pré-décrémentation
Fixed&			Fixed::operator--(void) {
	_fixedPointValue--;
	return (*this);
}
// Post-décrémentation
Fixed&			Fixed::operator--(int) {
	Fixed* temp = new Fixed(*this); // Crée une copie de l'objet actuel
	_fixedPointValue--;
	return (*temp); // Retourne la copie avant le décrémentation
}

// Surcharge de l’opérateur d’insertion
std::ostream&	operator<<(std::ostream& os, const Fixed& fixed) {
	os << fixed.toFloat();
	return os;
}
// ------------------------------------------------------------------------------------------------------------------------------------------






// ------------------------------------------------------------------------------------------------------------------------------------------
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
// ------------------------------------------------------------------------------------------------------------------------------------------






// -------------------------------------------------------------
// Fonction statique pour obtenir le maximum entre deux objets Fixed
Fixed&			Fixed::max(Fixed& a, Fixed& b) {
	if (a.getRawBits() > b.getRawBits())
		return (a);
	return (b);
}

const Fixed&	Fixed::max(const Fixed& a, const Fixed& b) {
	if (a.getRawBits() > b.getRawBits())
		return (a);
	return (b);
}


// Fonction statique pour obtenir le minimum entre deux objets Fixed
Fixed&			Fixed::min(Fixed& a, Fixed& b) {
	if (a.getRawBits() < b.getRawBits())
		return (a);
	return (b);
}

const Fixed&	Fixed::min(const Fixed& a, const Fixed& b) {
	if (a.getRawBits() < b.getRawBits())
		return (a);
	return (b);
}
// -------------------------------------------------------------

const int Fixed::_fractionalBits;
