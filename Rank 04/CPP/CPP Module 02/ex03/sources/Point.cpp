/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:49 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/20 17:10:31 by mstasiak         ###   ########.fr       */
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

// Constructeur depuis un int
Point::Point(const int srcInt) : _fixedPointValue(srcInt << _fractionalBits) {}

// Constructeur depuis un int
Point::Point(const float srcFloat) : _fixedPointValue(static_cast<int>(roundf(srcFloat * (1 << _fractionalBits)))) {}

// Destructeur
Point::~Point(void) {}
// ------------------------------------------------------------------------------------------------------------------------------------------

