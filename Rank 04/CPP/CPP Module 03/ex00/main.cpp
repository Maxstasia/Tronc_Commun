/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 14:13:12 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ClapTrap.hpp"

int main( void ) {
	ClapTrap clapTrap1;
	ClapTrap clapTrap2("Max");

	std::cout << std::endl << std::endl << clapTrap1 << std::endl;
	std::cout << std::endl << clapTrap2 << std::endl << std::endl << std::endl;

	clapTrap1.attack("Max");
	clapTrap2.takeDamage(clapTrap1.getAttackDamage());

	std::cout << std::endl << std::endl << clapTrap1 << std::endl;
	std::cout << std::endl << clapTrap2 << std::endl << std::endl << std::endl;

	clapTrap2.beRepaired(5);
	clapTrap1.attack("Max");
	clapTrap2.takeDamage(clapTrap1.getAttackDamage());

	std::cout << std::endl << std::endl << clapTrap1 << std::endl;
	std::cout << std::endl << clapTrap2 << std::endl << std::endl << std::endl;

	clapTrap2.beRepaired(10);
	clapTrap1.attack("Max");
	clapTrap2.takeDamage(clapTrap1.getAttackDamage());

	std::cout << std::endl << std::endl << clapTrap1 << std::endl;
	std::cout << std::endl << clapTrap2 << std::endl << std::endl << std::endl;

	return 0;
}