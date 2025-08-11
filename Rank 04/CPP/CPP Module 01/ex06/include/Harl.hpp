/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:36:21 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <string>
# include <iostream>

class Harl
{
private:
	// Fonctions membres privées pour chaque niveau
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);

public:
	// Constructeur
	Harl();
	
	// Fonction publique pour une plainte simple
	void complain(std::string level);
	
	// Nouvelle fonction pour filtrer les plaintes
	void complainFilter(std::string level);
};

#endif
