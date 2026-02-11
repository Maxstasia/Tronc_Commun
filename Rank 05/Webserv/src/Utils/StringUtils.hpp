/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:30:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/04 14:30:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "FileUtils.hpp"

class StringUtils
{
  public:
	static string trim(const string &s);
	static string toLower(const string &s);
	static vector_string split(const string &s, char delim);
	static string escapeHtml(const string &s);
	static string urlEncode(const string &s);
	static string urlDecode(const string &s);

  private:
	StringUtils();
	StringUtils(const StringUtils &other);
	StringUtils &operator=(const StringUtils &other);
	~StringUtils();
};
