/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_error.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 13:05:40 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Animal.hpp"

int main()
{
	Animal animal1;                        // ERROR: Cannot instantiate abstract class
	Animal animal2("Type");                // ERROR: Cannot instantiate abstract class
	Animal* animal3 = new Animal();        // ERROR: Cannot instantiate abstract class
	
	std::cout << "Ce fichier ne peut pas être compilé car Animal est abstraite !" << std::endl;
	delete animal3;
	return 0;
}
