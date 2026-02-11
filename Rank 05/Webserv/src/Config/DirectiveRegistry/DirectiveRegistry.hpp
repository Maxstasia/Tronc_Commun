/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectiveRegistry.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:25:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 15:25:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "FileUtils.hpp"

class DirectiveRegistry
{
  private:
	vector_string _directiveTypes;

	void handleDirectiveLine(const string &line);
	void loadTypesFile(const string &fileName);

  public:
	DirectiveRegistry();
	~DirectiveRegistry();

	void load();
	const vector_string &getDirectiveTypes() const;
};
