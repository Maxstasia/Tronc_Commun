/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/25 11:00:50 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Zombie.hpp"

int main()
{
	std::cout << "=== Test 1: newZombie (allocation sur le TAS) ===" << std::endl;

	Zombie* heapZombie = newZombie("HeapWalker");
	heapZombie->announce();
	
	// Libération avec 'delete'
	delete heapZombie;
	
	std::cout << "\n=== Test 2: randomChump (allocation sur la PILE) ===" << std::endl;

	randomChump("StackWalker");
	
	std::cout << "\n=== Test 3: Zombie local (sur la pile) ===" << std::endl;
	
	{
		Zombie localZombie("LocalWalker");
		localZombie.announce();
	}
	
	std::cout << "\n=== Fin des tests ===" << std::endl;
	
	return 0;
}
