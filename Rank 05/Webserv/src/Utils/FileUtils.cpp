/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:37:20 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/17 16:34:34 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileUtils.hpp"

//Canonique
FileUtils::FileUtils(void){}
FileUtils::FileUtils(const FileUtils&other){*this = other;}
FileUtils::~FileUtils(void){}
FileUtils&FileUtils::operator=(const FileUtils&other)
{
	if (this != &other){}
	return (*this);
}

//Methode
void FileUtils::openFileOrThrow(ifstream &stream, const string &path)
{
	if (path.empty())
		throw std::invalid_argument("Empty path");
	stream.close();
	stream.clear();
	stream.open(path.c_str());
	if (!stream.is_open())
		throw std::runtime_error("Impossible to open " + path);
}

bool FileUtils::fileExists(const string &path)
{
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

bool FileUtils::isDirectory(const string &path)
{
	struct stat buffer;
	if (stat(path.c_str(), &buffer) != 0)
		return false;
	return S_ISDIR(buffer.st_mode);
}

string FileUtils::ensureTrailingSlash(const string &path)
{
	if (path.empty() || path[path.size() - 1] == '/')
		return path;
	return path + "/";
}
