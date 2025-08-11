/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 16:59:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
	std::cout << "=== Test 1: Création d'une horde de 5 zombies ===" << std::endl;
	
	// Création d'une horde de 5 zombies
	int hordeSize = 5;
	Zombie* horde = zombieHorde(hordeSize, "Walker");
	
	// Test de l'annonce de chaque zombie
	std::cout << "\n=== Annonces des zombies ===" << std::endl;
	for (int i = 0; i < hordeSize; i++)
	{
		std::cout << "Zombie " << i + 1 << ": ";
		horde[i].announce();
	}
	
	// IMPORTANT: Libérer la mémoire avec delete[]
	std::cout << "\n=== Destruction de la horde ===" << std::endl;
	delete[] horde;
	
	std::cout << "\n=== Test 2: Cas limite - horde de 0 zombie ===" << std::endl;
	Zombie* emptyHorde = zombieHorde(0, "Empty");
	if (emptyHorde == NULL)
		std::cout << "Aucune horde créée (normal)." << std::endl;
	
	std::cout << "\n=== Test 3: Petite horde de 3 zombies ===" << std::endl;
	Zombie* smallHorde = zombieHorde(3, "Runner");
	
	std::cout << "\n=== Annonces de la petite horde ===" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "Zombie " << i + 1 << ": ";
		smallHorde[i].announce();
	}
	
	std::cout << "\n=== Destruction de la petite horde ===" << std::endl;
	delete[] smallHorde;
	
	std::cout << "\n=== Fin des tests ===" << std::endl;
	
	return 0;
}
