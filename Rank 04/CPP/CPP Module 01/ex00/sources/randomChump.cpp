/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/25 10:58:07 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

// Cette fonction alloue un zombie sur la stack
// Le zombie est détruit automatiquement à la fin de cette fonction
void randomChump(std::string name)
{
	Zombie zombie(name);
	zombie.announce();
}
