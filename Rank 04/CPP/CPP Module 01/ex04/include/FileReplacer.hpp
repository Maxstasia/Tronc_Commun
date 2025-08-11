/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReplacer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:25:27 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEREPLACER_HPP
# define FILEREPLACER_HPP

# include <string>
# include <iostream>
# include <fstream>

class FileReplacer
{
private:
	std::string filename;
	std::string s1;
	std::string s2;
	
	// Fonction privée pour remplacer toutes les occurrences
	std::string replaceAll(const std::string& content) const;
	
	// Fonction privée pour lire tout le fichier
	std::string readFile(const std::string& filename) const;
	
	// Fonction privée pour écrire dans le fichier
	bool writeFile(const std::string& filename, const std::string& content) const;

public:
	// Constructeur
	FileReplacer(const std::string& filename, const std::string& s1, const std::string& s2);
	
	// Fonction principale pour effectuer le remplacement
	bool processFile() const;
};

#endif
