/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReplacer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:30:00 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/11 17:46:38 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FileReplacer.hpp"

// Constructeur
FileReplacer::FileReplacer(const std::string& filename, const std::string& s1, const std::string& s2)
	: filename(filename), s1(s1), s2(s2)
{
}

// Lire tout le contenu du fichier
std::string FileReplacer::readFile(const std::string& filename) const
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: Cannot open file '" << filename << "'" << std::endl;
		return "";
	}
	
	std::string content;
	std::string line;
	
	// Lire ligne par ligne pour préserver les retours à la ligne
	while (std::getline(file, line))
	{
		content += line;
		// Ajouter le retour à la ligne sauf pour la dernière ligne
		if (!file.eof())
			content += "\n";
	}
	
	file.close();
	return content;
}

// Écrire le contenu dans un fichier
bool FileReplacer::writeFile(const std::string& filename, const std::string& content) const
{
	std::ofstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: Cannot create file '" << filename << "'" << std::endl;
		return false;
	}
	
	file << content;
	file.close();
	return true;
}

// Remplacer toutes les occurrences de s1 par s2
std::string FileReplacer::replaceAll(const std::string& content) const
{
	// Cas spécial : si s1 est vide, on ne peut pas remplacer
	if (s1.empty())
		return content;
	
	std::string result = content;
	size_t pos = 0;
	
	// Chercher et remplacer toutes les occurrences
	while ((pos = result.find(s1, pos)) != std::string::npos)
	{
		// Construire manuellement le remplacement (sans std::string::replace)
		std::string before = result.substr(0, pos);
		std::string after = result.substr(pos + s1.length());
		result = before + s2 + after;
		
		// Avancer la position pour éviter les boucles infinies
		pos += s2.length();
	}
	
	return result;
}

// Fonction principale qui orchestre tout
bool FileReplacer::processFile() const
{
	// Validation des paramètres
	if (filename.empty())
	{
		std::cerr << "Error: Empty filename" << std::endl;
		return false;
	}
	
	if (s1.empty())
	{
		std::cerr << "Error: Empty search string (s1)" << std::endl;
		return false;
	}
	
	// Lire le fichier original
	std::string content = readFile(filename);
	if (content.empty() && !std::ifstream(filename.c_str()).is_open())
		return false;
	
	// Effectuer les remplacements
	std::string newContent = replaceAll(content);
	
	// Créer le nom du fichier de sortie
	std::string outputFilename = filename + ".replace";
	
	// Écrire dans le nouveau fichier
	if (!writeFile(outputFilename, newContent))
		return false;
	
	std::cout << "File processed successfully!" << std::endl;
	std::cout << "Output written to: " << outputFilename << std::endl;
	
	return true;
}
