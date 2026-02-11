/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeTypeRegistry.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:20:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 15:20:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "FileUtils.hpp"

class MimeTypeRegistry
{
  private:
	vector_pair_string _mimeTypes;

	void handleMimeLine(const string &line);
	void loadTypesFile(const string &fileName);

  public:
	MimeTypeRegistry();
	~MimeTypeRegistry();

	void load();
	const vector_pair_string &getMimeTypes() const;
};
