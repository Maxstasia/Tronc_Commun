/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 16:59:57 by mstasiak         ###   ########.fr       */
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
	// Constructeur par défaut (nécessaire pour les tableaux)
	Zombie();
	
	// Constructeur avec nom
	Zombie(std::string name);
	
	// Destructeur
	~Zombie();
	
	// Setter pour le nom (nécessaire après création du tableau)
	void setName(std::string name);
	
	// Fonction membre pour s'annoncer
	void announce(void);
};

// Fonction pour créer une horde de zombies
Zombie* zombieHorde(int N, std::string name);

#endif
