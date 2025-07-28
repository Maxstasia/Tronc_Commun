/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:56:03 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/17 14:16:46 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>
#include <cstring>

int	main(int argc, char *argv[])
{
	// Si aucun argument n'est fourni (seul le nom du programme est dans argv)
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 0;
	}

	// Parcourir tous les arguments à partir de argv[1]
	for (int i = 1; i < argc; ++i)
	{
		// Parcourir chaque caractère de l'argument
		for (size_t j = 0; j < std::strlen(argv[i]); ++j)
		{
			// Convertir chaque caractère en majuscule et l'afficher
			std::cout << (char)std::toupper(argv[i][j]);
		}
	}
	std::cout << std::endl;

	return 0;
}
