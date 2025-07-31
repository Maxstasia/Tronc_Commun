/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:19:51 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/31 13:19:54 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/phonebook.hpp"

int	main()
{
	PhoneBook	phoneBook;
	std::string	command;

	std::cout << "=== Welcome to Your PhoneBook ===" << std::endl;
	while (1)
	{
		std::cout << "Enter command (ADD, SEARCH, EXIT): ";
		// Lecture sécurisée
		if (!std::getline(std::cin, command)) {
			// EOF atteint (Ctrl+D) ou erreur de lecture
			std::cout << "\nGoodbye!" << std::endl;
			break;
		}
		if (command == "ADD")
			phoneBook.addContact();
		else if (command == "SEARCH")
			phoneBook.searchContact();
		else if (command == "EXIT")
			break;
		else if (!command.empty())
			std::cout << "Invalid command! Please enter ADD, SEARCH, or EXIT." << std::endl;
	}

	return 0;
}
