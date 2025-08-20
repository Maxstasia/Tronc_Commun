/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:38 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/20 17:08:44 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

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
	// Constructeur depuis Fixed
	Point(const Fixed& x, const Fixed& y);
	// -------------------------------------------------------------

	// -------------------------------------------------------------
	// Opérateur d'affectation
	Point&	operator=(const Point& rhs);

	// Accesseurs
	const Fixed&	getX(void) const;
	const Fixed&	getY(void) const;
	// -------------------------------------------------------------
};

bool bsp( Point const a, Point const b, Point const c, Point const point);

#endif
