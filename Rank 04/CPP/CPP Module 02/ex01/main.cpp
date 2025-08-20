/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/20 12:06:17 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Fixed.hpp"

int	main( void ) {

	Fixed		a;
	Fixed const	b( 10 );
	Fixed const	c( 42.42f );
	Fixed const	d( b );

	a = Fixed( 1234.4321f );

	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;

	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;

	return 0;
}

/* a. Nombre à virgule fixe (fixed-point number)
Un nombre à virgule fixe stocke un nombre réel dans un entier, avec une partie fractionnaire définie par un nombre fixe de bits (ici, 8 bits). Cela signifie que la valeur entière est multipliée par $2^8 = 256$ pour représenter la partie fractionnaire.

Exemple : Pour représenter $5.75$:

La partie entière est $5$.
La partie fractionnaire est $0.75$. Puisque $0.75 \times 256 = 192$, la valeur stockée est $5 \times 256 + 192 = 1472$.


Conversion inverse (vers flottant) : Si la valeur stockée est $1472$, alors $1472 / 256 = 5.75$.
Conversion vers entier : On ignore la partie fractionnaire, donc $1472 / 256 = 5$.

b. Forme canonique de Coplien
La forme canonique exige que ta classe ait :

Un constructeur par défaut (initialise l’objet à une valeur par défaut, ici $0$).
Un constructeur de recopie (crée une copie d’un objet existant).
Un opérateur d’affectation (permet d’assigner un objet à un autre).
Un destructeur (libère les ressources, ici inutile car pas d’allocation dynamique).

c. Surcharge de l’opérateur <<
Comme expliqué dans la réponse précédente, l’opérateur << permet d’insérer la représentation en virgule flottante de l’objet Fixed dans un flux std::ostream (comme std::cout). On utilise la méthode toFloat() pour obtenir la valeur flottante et on l’insère dans le flux. */