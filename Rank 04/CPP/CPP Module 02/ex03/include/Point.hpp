/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:38 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 16:31:53 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef POINT_HPP
# define POINT_HPP

# include <iostream>
# include <cmath>
# include "Fixed.hpp"

class Point
{
private:
	Fixed	_x;
	Fixed	_y;

public:
	// -------------------------------------------------------------
	// Constructeur par défaut
	Point(void);
	// Destructeur
	~Point(void);

	// Constructeur de recopie
	Point(const Point& src);
	// Constructeur depuis deux float
	Point(const float x, const float y);
	// -------------------------------------------------------------





	// -------------------------------------------------------------
	// Opérateur d'affectation
	Point&			operator=(const Point& rhs);
	// -------------------------------------------------------------






	// -------------------------------------------------------------
	// Accesseurs
	const Fixed&	getX(void) const;
	const Fixed&	getY(void) const;
	// -------------------------------------------------------------
};

bool		bsp( Point const a, Point const b, Point const c, Point const point);

#endif
