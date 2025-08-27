/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:41:23 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/27 13:41:24 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/AMateria.hpp"
#include "include/ICharacter.hpp"
#include "include/IMateriaSource.hpp"
#include "include/Ice.hpp"
#include "include/Cure.hpp"
#include "include/Character.hpp"
#include "include/MateriaSource.hpp"

int main()
{
	std::cout << "=== Test principal ===" << std::endl;
	{
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());

		ICharacter* me = new Character("me");

		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);

		ICharacter* bob = new Character("bob");

		me->use(0, *bob);
		me->use(1, *bob);

		delete bob;
		delete me;
		delete src;
	}

	std::cout << "\n=== Tests supplémentaires ===" << std::endl;
	
	std::cout << "\n--- Test d'inventaire plein ---" << std::endl;
	{
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());

		ICharacter* hero = new Character("hero");
		ICharacter* enemy = new Character("enemy");

		// Équiper 4 materias (inventaire plein)
		for (int i = 0; i < 4; i++)
		{
			AMateria* ice = src->createMateria("ice");
			hero->equip(ice);
		}

		// Essayer d'équiper une 5ème materia (doit échouer silencieusement)
		AMateria* cure = src->createMateria("cure");
		hero->equip(cure);
		
		// Si l'inventaire est plein, cure n'a pas été équipée et doit être supprimée
		// pour éviter les fuites. Dans un vrai jeu, on pourrait avoir un système
		// de gestion des objets au sol plus sophistiqué.
		delete cure;

		// Utiliser toutes les materias équipées
		for (int i = 0; i < 4; i++)
		{
			hero->use(i, *enemy);
		}

		delete enemy;
		delete hero;
		delete src;
	}

	std::cout << "\n--- Test d'unequip et gestion mémoire ---" << std::endl;
	{
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());

		Character* mage = new Character("mage");
		Character* target = new Character("target");

		AMateria* ice = src->createMateria("ice");
		AMateria* cure = src->createMateria("cure");
		
		mage->equip(ice);
		mage->equip(cure);

		std::cout << "Avant unequip:" << std::endl;
		mage->use(0, *target);
		mage->use(1, *target);

		// Sauvegarder l'adresse avant unequip pour éviter les fuites
		AMateria* saved_ice = ice;
		mage->unequip(0);

		std::cout << "Après unequip de l'ice:" << std::endl;
		mage->use(0, *target); // Ne devrait rien faire
		mage->use(1, *target); // Devrait fonctionner

		// Supprimer la materia unequipped pour éviter les fuites
		delete saved_ice;

		delete target;
		delete mage;
		delete src;
	}

	std::cout << "\n--- Test de copie profonde ---" << std::endl;
	{
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());

		Character original("original");
		Character target("target");

		AMateria* ice = src->createMateria("ice");
		AMateria* cure = src->createMateria("cure");
		
		original.equip(ice);
		original.equip(cure);

		std::cout << "Original utilise ses materias:" << std::endl;
		original.use(0, target);
		original.use(1, target);

		// Test de copie
		Character copy = original;
		copy = Character("copy"); // Test d'assignation

		// Équiper des materias au copy
		AMateria* ice2 = src->createMateria("ice");
		copy.equip(ice2);

		std::cout << "Copy utilise sa materia:" << std::endl;
		copy.use(0, target);

		delete src;
	}

	std::cout << "\n--- Test de création de materia inconnue ---" << std::endl;
	{
		MateriaSource src;
		src.learnMateria(new Ice());

		AMateria* unknown = src.createMateria("fire");
		if (unknown == NULL)
			std::cout << "Création de materia 'fire' a échoué (comportement attendu)" << std::endl;
		else
		{
			std::cout << "Erreur: materia inconnue créée!" << std::endl;
			delete unknown;
		}

		AMateria* known = src.createMateria("ice");
		if (known)
		{
			std::cout << "Création de materia 'ice' réussie" << std::endl;
			delete known;
		}
	}

	return 0;
}
