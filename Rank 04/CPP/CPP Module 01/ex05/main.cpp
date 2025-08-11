/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:47:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Harl.hpp"

int main()
{
	Harl harl;
	
	std::cout << "=== HARL 2.0 - Complaint System ===" << std::endl;
	std::cout << "Testing all complaint levels..." << std::endl;
	std::cout << std::endl;
	
	// Test de tous les niveaux valides
	std::cout << "=== Valid Complaint Levels ===" << std::endl;
	
	harl.complain("DEBUG");
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("ERROR");
	
	// Test des cas invalides
	std::cout << "=== Invalid Complaint Levels ===" << std::endl;
	
	harl.complain("CRITICAL");
	harl.complain("debug");  // Case sensitive
	harl.complain("");       // Empty string
	harl.complain("RANDOM");
	
	// Test interactif simple
	std::cout << "=== Interactive Test ===" << std::endl;
	std::cout << "Enter a complaint level (DEBUG, INFO, WARNING, ERROR) or 'EXIT' to quit:" << std::endl;
	
	std::string input;
	while (std::cout << "> " && std::getline(std::cin, input))
	{
		if (input == "EXIT" || input == "exit")
			break;
		
		harl.complain(input);
	}
	
	std::cout << "Thanks for testing Harl 2.0!" << std::endl;
	
	return 0;
}
