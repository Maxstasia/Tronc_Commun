/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/18 11:36:01 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>

class Zombie
{
private:
	std::string name;

public:
	// Constructeur
	Zombie(std::string name);
	
	// Destructeur
	~Zombie();
	
	// Fonction membre pour s'annoncer
	void announce(void);
};

// Fonctions requises
Zombie* newZombie(std::string name);
void randomChump(std::string name);

#endif
