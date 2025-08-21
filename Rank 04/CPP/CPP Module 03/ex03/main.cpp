/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 19:09:26 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ClapTrap.hpp"
#include "include/ScavTrap.hpp"
#include "include/FragTrap.hpp"
#include "include/DiamondTrap.hpp"

int main( void ) {
	std::cout << "=== Testing ClapTrap ===" << std::endl;
	ClapTrap clapTrap1;
	ClapTrap clapTrap2("Max");

	std::cout << "\n" << clapTrap1 << std::endl;
	std::cout << "\n" << clapTrap2 << std::endl << std::endl;

	clapTrap1.attack("Max");
	clapTrap2.takeDamage(clapTrap1.getAttackDamage());
	clapTrap2.beRepaired(5);

	std::cout << "\n" << clapTrap1 << std::endl;
	std::cout << "\n" << clapTrap2 << std::endl << std::endl;

	std::cout << "\n=== Testing ScavTrap ===" << std::endl;
	ScavTrap scavTrap1;
	ScavTrap scavTrap2("Serena");

	std::cout << "\n" << scavTrap1 << std::endl;
	std::cout << "\n" << scavTrap2 << std::endl << std::endl;

	scavTrap1.attack("Serena");
	scavTrap2.takeDamage(scavTrap1.getAttackDamage());
	scavTrap2.beRepaired(10);

	std::cout << "\n" << scavTrap1 << std::endl;
	std::cout << "\n" << scavTrap2 << std::endl << std::endl;

	// Test de la méthode spéciale
	scavTrap1.guardGate();
	scavTrap2.guardGate();

	std::cout << "\n=== Testing FragTrap ===" << std::endl;
	FragTrap fragTrap1;
	FragTrap fragTrap2("Fraggy");

	std::cout << "\n" << fragTrap1 << std::endl;
	std::cout << "\n" << fragTrap2 << std::endl << std::endl;

	fragTrap1.attack("Fraggy");
	fragTrap2.takeDamage(fragTrap1.getAttackDamage());
	fragTrap2.beRepaired(15);

	std::cout << "\n" << fragTrap1 << std::endl;
	std::cout << "\n" << fragTrap2 << std::endl << std::endl;

	// Test de la méthode spéciale
	fragTrap1.highFivesGuys();
	fragTrap2.highFivesGuys();

	std::cout << "\n=== Testing construction/destruction chaining ===" << std::endl;
	{
		FragTrap tempFrag("Temporary");
		tempFrag.highFivesGuys();
	} // Le destructeur sera appelé ici

	std::cout << "\n=== Testing copy constructor ===" << std::endl;
	FragTrap fragTrap3(fragTrap2);
	fragTrap3.highFivesGuys();

	std::cout << "\n=== Testing assignment operator ===" << std::endl;
	FragTrap fragTrap4;
	fragTrap4 = fragTrap2;
	fragTrap4.highFivesGuys();

	std::cout << "\n=== End of program ===" << std::endl;
	return 0;
}
