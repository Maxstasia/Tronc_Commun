/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:38 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/18 18:32:56 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	// Constructeur de recopie
	Fixed(const int src);
	// Constructeur de recopie
	Fixed(const float src);


	// Opérateur d'affectation
	Fixed&	operator=(const Fixed& rhs);


	// Fonctions membres pour manipuler la valeur brute
	int		getRawBits(void) const;
	void	setRawBits(int const raw);

	int		toInt(void) const;
	float	toFloat(void) const;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
