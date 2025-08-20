/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/20 16:56:19 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Fixed.hpp"

int	main( void ) {

	Fixed		a;
	Fixed const	b( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	std::cout << Fixed::max( a, b ) << std::endl << std::endl;

	std::cout << "Test complémentaire :" << std::endl;
	
	std::cout << "Valeurs initiales :" << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;

	std::cout << "Opérations arithmétiques :" << std::endl;
	std::cout << "a + b = " << a + b << std::endl;
	std::cout << "a - b = " << a - b << std::endl;
	std::cout << "a * b = " << a * b << std::endl;
	std::cout << "a / b = " << a / b << std::endl;

	std::cout << "Comparaisons :" << std::endl;
	std::cout << "a > b : " << (a > b) << std::endl;
	std::cout << "a < b : " << (a < b) << std::endl;
	std::cout << "a >= b : " << (a >= b) << std::endl;
	std::cout << "a <= b : " << (a <= b) << std::endl;
	std::cout << "a == b : " << (a == b) << std::endl;
	std::cout << "a != b : " << (a != b) << std::endl;

	std::cout << "Incrémentation :" << std::endl;
	std::cout << "Pré-incrémentation : " << ++a << std::endl;
	std::cout << "Post-incrémentation : " << a++ << std::endl;
	std::cout << "Valeur après post-incrémentation : " << a << std::endl;

	std::cout << "Décrémentation :" << std::endl;
	std::cout << "Pré-décrémentation : " << --a << std::endl;
	std::cout << "Post-décrémentation : " << a-- << std::endl;
	std::cout << "Valeur après post-décrémentation : " << a << std::endl;

	std::cout << "Valeur maximale entre a et b : " << Fixed::max(a, b) << std::endl;
	std::cout << "Valeur minimale entre a et b : " << Fixed::min(a, b) << std::endl;
	
	return 0;
}
