/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 16:24:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef HUMANA_HPP
# define HUMANA_HPP

# include <string>
# include <iostream>
# include "Weapon.hpp"

class HumanA
{
private:
	std::string name;
	Weapon& weapon;  // RÉFÉRENCE - toujours valide, ne peut pas changer

public:
	// Constructeur - DOIT prendre une arme (référence obligatoire)
	HumanA(const std::string& name, Weapon& weapon);
	
	// Fonction d'attaque
	void attack() const;
};

#endif
