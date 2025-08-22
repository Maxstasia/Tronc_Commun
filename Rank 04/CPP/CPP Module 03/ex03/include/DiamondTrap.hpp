/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:06:24 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/22 10:00:06 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "ClapTrap.hpp"
# include "ScavTrap.hpp"
# include "FragTrap.hpp"
# include <iostream>
# include <string>

class DiamondTrap : public ScavTrap, public FragTrap {
private:
	std::string	_name;

public:
	// Constructeurs
	DiamondTrap(void);
	DiamondTrap(const std::string& name);
	DiamondTrap(const DiamondTrap& src);
	
	// Destructeur
	~DiamondTrap(void);

	// Opérateur d'affectation
	DiamondTrap&	operator=(const DiamondTrap& rhs);
	
	// Méthodes héritées redéfinies
	using ScavTrap::attack;  // Utilise la méthode attack de ScavTrap
	
	// Méthode spéciale à DiamondTrap
	void			whoAmI(void);
	
	// Getters
	std::string		getName(void) const;
};

// Surcharge d'opérateur chevron pour l'affichage
std::ostream& operator<<(std::ostream& os, const DiamondTrap& diamondTrap);

#endif
