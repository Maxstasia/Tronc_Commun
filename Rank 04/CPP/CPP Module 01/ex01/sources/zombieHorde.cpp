/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:44:30 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

// Cette fonction alloue N zombies en UNE SEULE allocation
// Utilise 'new[]' pour allouer un tableau d'objets
// ATTENTION: Il faudra utiliser 'delete[]' pour libérer !
Zombie* zombieHorde(int N, std::string name)
{
	// Vérification de la validité du paramètre
	if (N <= 0)
	{
		std::cout << "Error: Cannot create horde of " << N << " zombies!" << std::endl;
		return NULL;
	}
	
	std::cout << "\n=== Creating a horde of " << N << " zombies ===" << std::endl;
	
	// Allocation d'un tableau de N zombies en une seule fois
	Zombie* horde = new Zombie[N];
	
	// Initialisation de chaque zombie avec le même nom
	for (int i = 0; i < N; i++)
	{
		horde[i].setName(name);
	}
	
	std::cout << "=== Horde created successfully! ===" << std::endl;
	
	return horde;
}
