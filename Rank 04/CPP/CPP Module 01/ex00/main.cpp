/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 15:51:20 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
	std::cout << "=== Test 1: newZombie (allocation sur le TAS) ===" << std::endl;
	
	// Allocation sur le tas (heap) avec 'new'
	Zombie* heapZombie = newZombie("HeapWalker");
	heapZombie->announce();
	
	// IMPORTANT: On doit libérer manuellement avec 'delete'
	delete heapZombie;
	
	std::cout << "\n=== Test 2: randomChump (allocation sur la PILE) ===" << std::endl;
	
	// Allocation sur la pile (stack) - destruction automatique
	randomChump("StackWalker");
	
	std::cout << "\n=== Test 3: Zombie local (sur la pile) ===" << std::endl;
	
	{
		Zombie localZombie("LocalWalker");
		localZombie.announce();
		// localZombie sera détruit automatiquement ici
	}
	
	std::cout << "\n=== Fin des tests ===" << std::endl;
	
	return 0;
}
