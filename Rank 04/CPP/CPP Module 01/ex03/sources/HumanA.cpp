/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:06:04 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

// Constructeur - initialise la référence dans la liste d'initialisation
HumanA::HumanA(const std::string& name, Weapon& weapon) : name(name), weapon(weapon)
{
}

// Attaque - la référence est toujours valide
void HumanA::attack() const
{
	std::cout << this->name << " attacks with their " << this->weapon.getType() << std::endl;
}
