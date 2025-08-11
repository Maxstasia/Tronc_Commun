/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:36:21 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int argc, char** argv)
{
	// Vérification du nombre d'arguments
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <level>" << std::endl;
		std::cerr << "Levels: DEBUG, INFO, WARNING, ERROR" << std::endl;
		std::cerr << "Example: " << argv[0] << " WARNING" << std::endl;
		return 1;
	}
	
	// Création d'une instance de Harl
	Harl harl;
	
	// Appel de la fonction de filtrage avec le niveau spécifié
	std::string level = argv[1];
	harl.complainFilter(level);
	
	return 0;
}
