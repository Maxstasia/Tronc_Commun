/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:38 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 16:24:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
private:
	int	_fixedPointValue;
	static const int _fractionalBits = 8;

public:
	// Constructeur par défaut
	Fixed(void);
	// Destructeur
	~Fixed(void);


	// Constructeur de recopie
	Fixed(const Fixed& src);
	// Constructeur depuis un int
	Fixed(const int srcInt);
	// Constructeur depuis un float
	Fixed(const float srcFloat);


	// Opérateur d'affectation
	Fixed&	operator=(const Fixed& rhs);


	// Fonctions membres pour manipuler la valeur brute
	int		getRawBits(void) const;
	void	setRawBits(int const raw);

	// Fonctions membres pour convertir
	int		toInt(void) const;
	float	toFloat(void) const;
};

// Opérateur d’insertion
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
