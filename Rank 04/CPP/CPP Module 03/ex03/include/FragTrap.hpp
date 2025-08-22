/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:55:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/22 10:00:06 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"
# include <iostream>
# include <string>

class FragTrap : virtual public ClapTrap {
public:
	// Constructeurs
	FragTrap(void);
	FragTrap(std::string name);
	FragTrap(const FragTrap& src);
	
	// Destructeur
	~FragTrap(void);

	// Opérateur d'affectation
	FragTrap&		operator=(const FragTrap& rhs);
	
	// Méthodes redéfinies
	void			attack(const std::string& target);
	
	// Méthode spéciale à FragTrap
	void			highFivesGuys(void);
};

// Surcharge d'opérateur chevron pour l'affichage
std::ostream& operator<<(std::ostream& os, const FragTrap& fragTrap);

#endif