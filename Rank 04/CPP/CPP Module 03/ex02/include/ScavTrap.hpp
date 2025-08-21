/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:51:50 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 18:52:49 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"
# include <iostream>
# include <string>

class ScavTrap : public ClapTrap {
public:
	// Constructeurs
	ScavTrap(void);
	ScavTrap(std::string name);
	ScavTrap(const ScavTrap& src);
	
	// Destructeur
	~ScavTrap(void);

	// Opérateur d'affectation
	ScavTrap&		operator=(const ScavTrap& rhs);
	
	// Méthodes redéfinies
	void			attack(const std::string& target);
	
	// Méthode spéciale à ScavTrap
	void			guardGate(void);
};

// Surcharge d'opérateur chevron pour l'affichage
std::ostream& operator<<(std::ostream& os, const ScavTrap& scavTrap);

#endif