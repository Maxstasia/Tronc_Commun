/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:42:03 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 13:42:04 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AMateria.hpp"
#include "../include/ICharacter.hpp"

AMateria::AMateria(std::string const & type) : _type(type)
{
}

AMateria::AMateria(const AMateria& other) : _type(other._type)
{
}

AMateria::~AMateria()
{
}

AMateria& AMateria::operator=(const AMateria& other)
{
	if (this != &other)
	{
		// On ne copie pas le type selon la consigne
		// "copier son type n'a pas grand intérêt"
	}
	return *this;
}

std::string const & AMateria::getType() const
{
	return _type;
}

void AMateria::use(ICharacter& target)
{
	(void)target;
	// Fonction de base, ne fait rien
}
