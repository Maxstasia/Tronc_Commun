/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/25 12:19:11 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef HARL_HPP
# define HARL_HPP

# include <string>
# include <iostream>

class Harl
{
private:
	// Fonctions pour chaque niveau
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);

public:
	// Constructeur
	Harl();
	
	// Nouvelle pour filtrer les plaintes
	void complainFilter(std::string level);
};

#endif
