/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:45:49 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Weapon.hpp"

// Constructeur
Weapon::Weapon(const std::string& type) : type(type)
{
}

// Getter - retourne une référence constante pour éviter la copie
const std::string& Weapon::getType() const
{
	return this->type;
}

// Setter
void Weapon::setType(const std::string& type)
{
	this->type = type;
}
