/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:37:20 by rcini-ha          #+#    #+#             */
/*   Updated: 2025/12/09 14:01:51 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Constants.hpp"

class FileUtils
{
  private:

  public:
	FileUtils(void);
	FileUtils(const FileUtils &other);
	FileUtils &operator=(const FileUtils &other);
	~FileUtils(void);

	static void openFileOrThrow(ifstream &stream, const string &path);
	static bool fileExists(const string &path);
	static bool isDirectory(const string &path);
	static string ensureTrailingSlash(const string &path);
	static bool isPathSafe(const string &filePath, const string &root);
	template <typename T> string toString(const T &v)
	{
		stringstream oss;
		oss << v;
		return (oss.str());
	}
};
