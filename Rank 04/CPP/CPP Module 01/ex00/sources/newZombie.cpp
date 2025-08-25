/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/25 10:57:37 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

// Cette fonction alloue un zombie sur le heap avec 'new'
// Le zombie peut être utilisé en dehors de cette fonction
Zombie* newZombie(std::string name)
{
	Zombie* zombie = new Zombie(name);
	return zombie;
}
