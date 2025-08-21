/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 17:46:52 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ClapTrap.hpp"
#include "include/ScavTrap.hpp"

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

	std::cout << "\n=== Testing construction/destruction chaining ===" << std::endl;
	{
		ScavTrap tempScav("Temporary");
		tempScav.guardGate();
	} // Le destructeur sera appelé ici

	std::cout << "\n=== Testing copy constructor ===" << std::endl;
	ScavTrap scavTrap3(scavTrap2);
	scavTrap3.guardGate();

	std::cout << "\n=== Testing assignment operator ===" << std::endl;
	ScavTrap scavTrap4;
	scavTrap4 = scavTrap2;
	scavTrap4.guardGate();

	std::cout << "\n=== End of program ===" << std::endl;
	return 0;
}