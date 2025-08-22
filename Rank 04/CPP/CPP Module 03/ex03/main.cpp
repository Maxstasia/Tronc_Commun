/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/22 10:04:19 by mstasiak         ###   ########.fr       */
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

	std::cout << "\n=== Testing DiamondTrap ===" << std::endl;
	DiamondTrap diamondTrap1;
	DiamondTrap diamondTrap2("Diamond");

	std::cout << "\n" << diamondTrap1 << std::endl;
	std::cout << "\n" << diamondTrap2 << std::endl << std::endl;

	// Test des méthodes héritées
	diamondTrap1.attack("Diamond");
	diamondTrap2.takeDamage(diamondTrap1.getAttackDamage());
	diamondTrap2.beRepaired(20);

	std::cout << "\n" << diamondTrap1 << std::endl;
	std::cout << "\n" << diamondTrap2 << std::endl << std::endl;

	// Test des méthodes spéciales héritées
	diamondTrap1.guardGate();     // de ScavTrap
	diamondTrap2.highFivesGuys(); // de FragTrap

	// Test de la méthode spéciale de DiamondTrap
	diamondTrap1.whoAmI();
	diamondTrap2.whoAmI();

	std::cout << "\n=== Testing DiamondTrap copy constructor ===" << std::endl;
	DiamondTrap diamondTrap3(diamondTrap2);
	diamondTrap3.whoAmI();

	std::cout << "\n=== Testing DiamondTrap assignment operator ===" << std::endl;
	DiamondTrap diamondTrap4;
	diamondTrap4 = diamondTrap2;
	diamondTrap4.whoAmI();

	std::cout << "\n=== Testing DiamondTrap destruction chaining ===" << std::endl;
	{
		DiamondTrap tempDiamond("Temporary");
		tempDiamond.whoAmI();
	} // Le destructeur sera appelé ici

	std::cout << "\n=== End of program ===" << std::endl;
	return 0;
}
