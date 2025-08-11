/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:46:44 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/FileReplacer.hpp"

int main(int argc, char** argv)
{
	// Vérification du nombre d'arguments
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		std::cerr << "  filename: file to process" << std::endl;
		std::cerr << "  s1: string to find" << std::endl;
		std::cerr << "  s2: string to replace with" << std::endl;
		return 1;
	}
	
	// Récupération des arguments
	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	
	// Affichage des paramètres pour debug
	std::cout << "=== File Replacer ===" << std::endl;
	std::cout << "File: " << filename << std::endl;
	std::cout << "Replace: '" << s1 << "' -> '" << s2 << "'" << std::endl;
	std::cout << "=====================" << std::endl;
	
	// Création de l'objet et traitement
	FileReplacer replacer(filename, s1, s2);
	
	if (!replacer.processFile())
	{
		std::cerr << "Error: Failed to process file" << std::endl;
		return 1;
	}
	
	return 0;
}
