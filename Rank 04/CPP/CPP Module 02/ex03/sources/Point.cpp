/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:49 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 11:21:44 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Point.hpp"

// ------------------------------------------------------------------------------------------------------------------------------------------
// Constructeur par défaut : initialise la valeur à 0
Point::Point(void) : _x(0), _y(0) {}

// Constructeur de recopie : copie la valeur brute d'un autre objet
Point::Point(const Point& src) {
	*this = src;
}

// Constructeur depuis deux float
Point::Point(const float x, const float y) : _x(x), _y(y) {}

// Destructeur
Point::~Point(void) {}
// ------------------------------------------------------------------------------------------------------------------------------------------




// ------------------------------------------------------------------------------------------------------------------------------------------
// Opérateur d'affectation
Point&		Point::operator=(const Point& rhs) {
	if (this != &rhs) // Vérifie l’auto-affectation
	{
		_x = rhs.getX();
		_y = rhs.getY();
	}
	return (*this);
}

// Accesseurs
const Fixed&	Point::getX(void) const {
	return (_x);
}

const Fixed&	Point::getY(void) const {
	return (_y);
}