/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 15:51:20 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// Cette fonction alloue un zombie sur la PILE (stack)
// Le zombie est détruit automatiquement à la fin de cette fonction
// Parfait pour une utilisation temporaire !
void randomChump(std::string name)
{
	Zombie zombie(name);
	zombie.announce();
	// Le zombie est détruit automatiquement ici (fin de scope)
}
