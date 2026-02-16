/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoaderAccessor.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 10:19:56 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/13 19:10:08 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Loader.hpp"

/**
 * @brief Retourne la liste des tokens lexicaux
 *
 * @return Référence constante vers la liste des paires <string, int> représentant les tokens
 */
const list_pair_str_int &Loader::getListLexer() const {return _tokenizer.getTokens();}

/**
 * @brief Récupère le type MIME correspondant à une extension de fichier
 *
 * Recherche dans le registre des types MIME l'extension spécifiée et retourne
 * le type MIME correspondant. Si l'extension n'est pas trouvée, retourne le
 * type par défaut "application/octet-stream".
 *
 * @param extension L'extension de fichier (sans le point)
 * @return Le type MIME correspondant ou "application/octet-stream" par défaut
 */
string Loader::getMimeType(const string &extension) const
{
	const vector_pair_string &mimes = _mimeRegistry.getMimeTypes();
	for (size_t i = 0; i < mimes.size(); ++i)
	{
		if (mimes[i].first == extension)
			return mimes[i].second;
	}
	return "application/octet-stream";
}
