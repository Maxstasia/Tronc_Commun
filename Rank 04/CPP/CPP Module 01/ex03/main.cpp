/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:45:58 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Weapon.hpp"
#include "include/HumanA.hpp"
#include "include/HumanB.hpp"

int main()
{
	std::cout << "=== Test officiel du sujet ===" << std::endl;
	
	// Test avec HumanA (référence)
	{
		std::cout << "\n--- Test HumanA (avec référence) ---" << std::endl;
		Weapon club = Weapon("crude spiked club");
		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	
	// Test avec HumanB (pointeur)
	{
		std::cout << "\n--- Test HumanB (avec pointeur) ---" << std::endl;
		Weapon club = Weapon("crude spiked club");
		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
	
	std::cout << "\n=== Tests supplémentaires ===" << std::endl;
	
	// Test HumanB sans arme
	{
		std::cout << "\n--- Test HumanB sans arme ---" << std::endl;
		HumanB alice("Alice");
		alice.attack();  // Doit gérer le cas où il n'y a pas d'arme
	}
	
	// Test changement d'arme pour HumanB
	{
		std::cout << "\n--- Test changement d'arme pour HumanB ---" << std::endl;
		Weapon sword("sharp sword");
		Weapon bow("elven bow");
		
		HumanB charlie("Charlie");
		charlie.setWeapon(sword);
		charlie.attack();
		
		charlie.setWeapon(bow);  // Change d'arme
		charlie.attack();
	}
	
	return 0;
}
