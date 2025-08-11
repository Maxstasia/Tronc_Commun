/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 16:49:37 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main()
{
	// Variable string
	std::string string = "HI THIS IS BRAIN";
	
	// Pointeur vers la string
	std::string* stringPTR = &string;
	
	// Référence vers la string
	std::string& stringREF = string;
	
	std::cout << "=== ADRESSES MÉMOIRE ===" << std::endl;
	std::cout << "Adresse de la variable string: " << &string << std::endl;
	std::cout << "Adresse stockée dans stringPTR: " << stringPTR << std::endl;
	std::cout << "Adresse stockée dans stringREF: " << &stringREF << std::endl;
	
	std::cout << "\n=== VALEURS ===" << std::endl;
	std::cout << "Valeur de la variable string: " << string << std::endl;
	std::cout << "Valeur pointée par stringPTR: " << *stringPTR << std::endl;
	std::cout << "Valeur pointée par stringREF: " << stringREF << std::endl;
	
	return 0;
}
