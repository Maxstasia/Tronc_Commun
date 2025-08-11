/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:06:04 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"

class HumanB
{
private:
	std::string name;
	Weapon* weapon;  // POINTEUR - peut être NULL, peut changer

public:
	// Constructeur - ne prend PAS d'arme
	HumanB(const std::string& name);
	
	// Setter pour l'arme
	void setWeapon(Weapon& weapon);
	
	// Fonction d'attaque
	void attack() const;
};

#endif
