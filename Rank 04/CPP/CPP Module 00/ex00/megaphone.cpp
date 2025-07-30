/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:18:08 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/30 13:30:58 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>
#include <cstring>

// Version 1
int	main(int argc, char **argv)
{
	int	i = 1;
	int	j;

	// Si aucun argument n'est fourni
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (1);
	}
	// Parcourir tous les arguments à partir de argv[1]
	while (argv[i])
	{
		j = 0;
		// Parcourir chaque caractère de l'argument
		while (argv[i][j])
		{
			// Convertir chaque caractère en majuscule et l'afficher
			if (argv[i][j] >= 'a' && argv[i][j] <= 'z')
			{
				argv[i][j] -= 32;
				std::cout << argv[i][j];
			}			
			else
				std::cout << argv[i][j];
			j ++;
		}
		i ++;
	}
	std::cout << std::endl;
	return (0);
}

// Version 2
/*
int	main(int argc, char *argv[])
{
	// Si aucun argument n'est fourni (seul le nom du programme est dans argv)
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 1;
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
*/
