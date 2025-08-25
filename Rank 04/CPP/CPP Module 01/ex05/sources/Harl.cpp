/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/25 12:01:46 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"

// Constructeur
Harl::Harl() {}

// Fonction DEBUG
void Harl::debug(void)
{
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
	std::cout << std::endl;
}

// Fonction INFO
void Harl::info(void)
{
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" << std::endl;
	std::cout << std::endl;
}

// Fonction WARNING
void Harl::warning(void)
{
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month." << std::endl;
	std::cout << std::endl;
}

// Fonction ERROR
void Harl::error(void)
{
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
	std::cout << std::endl;
}

// Fonction principale qui utilise les pointeurs vers les fonctions membres
void Harl::complain(std::string level)
{
	// Tableau des noms de niveaux
	std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	
	// Tableau de pointeurs vers les fonctions membres
	void (Harl::*functions[4])(void) = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};
	
	// Chercher le niveau correspondant
	for (int i = 0; i < 4; i++)
	{
		if (levels[i] == level)
		{
			// Appeler la fonction correspondante
			(this->*functions[i])();
			return;
		}
	}
	
	// Si aucun niveau trouvé
	std::cout << "[ UNKNOWN ]" << std::endl;
	std::cout << "Harl doesn't know how to complain about '" << level << "'." << std::endl;
	std::cout << std::endl;
}
