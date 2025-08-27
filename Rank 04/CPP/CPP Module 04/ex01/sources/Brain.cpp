/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:00:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 11:50:33 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Brain.hpp"

// Constructeur par défaut
Brain::Brain()
{
	std::cout << "Brain: Constructeur par défaut appelé" << std::endl;
	// Initialiser quelques idées par défaut
	for (int i = 0; i < 100; i++)
	{
		ideas[i] = "";
	}
}

// Constructeur de copie (copie profonde)
Brain::Brain(const Brain& other)
{
	std::cout << "Brain: Constructeur de copie appelé" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		this->ideas[i] = other.ideas[i];
	}
}

// Opérateur d'assignation (copie profonde)
Brain& Brain::operator=(const Brain& other)
{
	std::cout << "Brain: Opérateur d'assignation appelé" << std::endl;
	if (this != &other)
	{
		for (int i = 0; i < 100; i++)
		{
			this->ideas[i] = other.ideas[i];
		}
	}
	return *this;
}

// Destructeur
Brain::~Brain()
{
	std::cout << "Brain: Destructeur appelé" << std::endl;
}

// Setter pour une idée
void Brain::setIdea(int index, const std::string& idea)
{
	if (index >= 0 && index < 100)
	{
		this->ideas[index] = idea;
	}
}

// Getter pour une idée
std::string Brain::getIdea(int index) const
{
	if (index >= 0 && index < 100)
	{
		return this->ideas[index];
	}
	return "";
}

// Afficher quelques idées pour les tests
void Brain::printIdeas() const
{
	std::cout << "Brain ideas: ";
	bool hasIdeas = false;
	for (int i = 0; i < 10; i++) // Afficher seulement les 10 premières
	{
		if (!ideas[i].empty())
		{
			std::cout << "[" << i << "]=" << ideas[i] << " ";
			hasIdeas = true;
		}
	}
	if (!hasIdeas)
		std::cout << "(aucune idée définie)";
	std::cout << std::endl;
}
