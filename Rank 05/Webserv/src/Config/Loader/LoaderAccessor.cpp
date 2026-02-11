/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoaderAccessor.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 10:19:56 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/25 10:20:42 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Loader.hpp"

const list_pair_str_int &Loader::getListLexer() const {return listLexer;}

string Loader::getMimeType(const string &extension) const
{
	for (size_t i = 0; i < mime_type.size(); ++i)
	{
		if (mime_type[i].first == extension)
			return mime_type[i].second;
	}
	return "application/octet-stream";
}
