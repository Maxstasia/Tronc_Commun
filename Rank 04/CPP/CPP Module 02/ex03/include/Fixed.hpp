/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:38 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 11:30:46 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
private:
	int					_fixedPointValue;
	static const int	_fractionalBits = 8;

public:
	// -------------------------------------------------------------
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
	// -------------------------------------------------------------





	// -------------------------------------------------------------
	// Opérateur d'affectation
	Fixed&				operator=(const Fixed& rhs);
	
	// Opérateur de comparaison
	bool				operator>(const Fixed& rhs);
	bool				operator<(const Fixed& rhs);
	bool				operator>=(const Fixed& rhs);
	bool				operator<=(const Fixed& rhs);
	bool				operator==(const Fixed& rhs);
	bool				operator!=(const Fixed& rhs);

	// Opérateur arithmétiques
	Fixed				operator+(const Fixed& rhs) const;
	Fixed				operator-(const Fixed& rhs) const;
	Fixed				operator*(const Fixed& rhs) const;
	Fixed				operator/(const Fixed& rhs) const;

	// Opérateur d'incrémentation
	Fixed&				operator++(void); // Pré-incrémentation
	Fixed&				operator++(int); // Post-incrémentation
	
	// Opérateur de décrémentation
	Fixed&				operator--(void); // Pré-décrémentation
	Fixed&				operator--(int); // Post-décrémentation
	// -------------------------------------------------------------





	// -------------------------------------------------------------
	// Fonctions membres pour manipuler la valeur brute
	int					getRawBits(void) const;
	void				setRawBits(int const raw);

	// Fonctions membres pour convertir
	int					toInt(void) const;
	float				toFloat(void) const;
	// -------------------------------------------------------------



	// -------------------------------------------------------------
	// Fonction statique pour obtenir le maximum entre deux objets Fixed
	static Fixed&		max(Fixed& a, Fixed& b);
	static const Fixed&	max(const Fixed& a, const Fixed& b);

	// Fonction statique pour obtenir le minimum entre deux objets Fixed
	static Fixed&		min(Fixed& a, Fixed& b);
	static const Fixed&	min(const Fixed& a, const Fixed& b);
	// -------------------------------------------------------------
};

// Opérateur d’insertion
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
